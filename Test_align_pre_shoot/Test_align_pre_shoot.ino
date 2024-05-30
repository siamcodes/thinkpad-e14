#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// align controller
#define ali_Kp 2.75
#define ali_Kd 0.0
#define alignErrorGap 4
float ali_error, ali_pError, ali_d, ali_vec, lastYaw, vecCurve, radCurve;
float spFli = 130;
// overall
int  ballPosY, discoveState;

float thetaRad, vx, vy, spd1, spd2, spd3;
void zeroYaw() {
  Serial1.begin(115200); delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5); Serial1.write(0X54); delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5); Serial1.write(0X55); delay(100);
  // zero degree heading
  Serial1.write(0XA5); Serial1.write(0X52); delay(100);
  // automatic mode
}
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) { // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) { // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}
void Auto_zero(){
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.02) {
    if(getIMU()){
      oled.text(3, 6,"Yaw: %f  " ,pvYaw);
      oled.show();
      beep();
      if (millis() - timer > 5000) {
        zeroYaw();
        timer = millis();
      }
   }
  }
  oled.clear();
  oled.show();
}
void wheel(int s1, int s2, int s3) {
  motor(1, s1);
  motor(2, s2);
  motor(3, s3);
}
void holonomic(float spd, float theta, float omega) {
  thetaRad = theta * degToRad;
  vx = spd * cos(thetaRad);
  vy = spd * sin(thetaRad);
  spd1 =   vy * cos30 - vx * sin30 + omega;
  spd2 = - vy * cos30 - vx * sin30 + omega;
  spd3 =   vx + omega;
  wheel(spd1, spd2, spd3);
}
void setup() {
  pixy.init();
  Auto_zero();
  waitSW_A_bmp();
}

void loop() {
  // holonomic(40,45,15);
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    int timeOut = millis();
    while (!getIMU()) {
      if (millis() - timeOut > 3000) break;
    }
    ballPosY = pixy.sigInfo[1][0].y;
    ali_error = ballPosY - spFli;
    ali_d = ali_error - ali_pError;
    ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
    ali_pError = ali_error;
     // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
    if (pvYaw < 0) {
      vecCurve = -ali_vec;
      radCurve = 15; //15
    }
    else {
      vecCurve = 180 + ali_vec;
      radCurve = -15;  //15
    }
     holonomic(40,vecCurve,radCurve);
    if (abs(pvYaw) < alignErrorGap){
      holonomic(0,0,0);
      beep();
    }
  }
  
}
