#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;

int L, C, R;
int RefL = 2400, RefC = 2400, RefR = 2400;
unsigned long loopTimer = millis();

#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// ค่าที่ใช้ปรับหุ่นให้เข้าด้านหน้าตรงลูกบอล
#define rot_Kp 0.7  //0.35
#define rot_Ki 0.0
#define rot_Kd 0.0       //0
#define sp_rot 160       // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
float rotErrorGap = 15;  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
#define idleSpd 35       // ค่าความเร็วการหมุนเมื่อไม่เจอลูกบอล
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// ค่าที่ใช้ปรับหุ่นให้เข้าใกล้ลูกบอล
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
float flingErrorGap = 15;  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 170;         //170    // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// ค่าที่ใช้ปรับหุ่นให้ตรงทิศอ้างอิง
#define ali_Kp 2.75
#define ali_Kd 0.0
#define alignErrorGap 4
float ali_error, ali_pError, ali_d, ali_vec, vecCurve, radCurve;
int discoveState = 1;
// ค่าที่ใช้รักษาทิศหุ่นยนต์
#define head_Kp 2.3f
#define head_Ki 0.0f
#define head_Kd 0.5f
float head_error, head_pError, head_w, head_d, head_i;
/* >> ball shooting <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
#define limPin A0
#define reloadSpd 70
float thetaRad, vx, vy, spd1, spd2, spd3;

void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X54);
  delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X55);
  delay(100);
  // zero degree heading
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X52);
  delay(100);
  // automatic mode
}

float pvYaw, lastYaw;
uint8_t rxCnt = 0, rxBuf[8];

bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) {  // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {  // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}

void Auto_zero() {
  zeroYaw();
  getIMU();
  int timerOut = millis();
  oled.mode(2);
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.02) {
    if (getIMU()) {
      oled.text(3, 6, "Yaw: %f  ", pvYaw);
      oled.show();
      //beep();
      if (millis() - timerOut > 5000) {
        zeroYaw();
        timerOut = millis();
      }
    }
  }
  oled.clear();
}

void updateIMU() {
  for (int i = 0; i < 16; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
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
  spd1 = vy * cos30 - vx * sin30 + omega;
  spd2 = -vy * cos30 - vx * sin30 + omega;
  spd3 = vx + omega;
  wheel(spd1, spd2, spd3);
}

void heading(float spd, float theta, float spYaw) {
  head_error = spYaw - pvYaw;
  head_i = head_i + head_error;
  head_i = constrain(head_i, -180, 180);
  head_d = head_error - head_pError;
  head_w = (head_error * head_Kp) + (head_i * head_Ki) + (head_d * head_Kd);
  head_w = constrain(head_w, -100, 100);
  holonomic(spd, theta, head_w);
  head_pError = head_error;
}

void shoot() {
  motor(4, reloadSpd);
  delay(150);
  motor(4, 0);
  delay(50);
}

int timer = 0;

void reload() {
  motor(4, reloadSpd);
  timer = 0;
  for (int i = 0; i < 2000; i++) {
    timer++;
    if (in(limPin)) break;
    delay(1);
  }
  if (timer == 2000) {     // ถ้าก้านยิงติด
    motor(4, -reloadSpd);  // เลื่อนก้านยิงไปข้างหน้า
    delay(500);            //ก่อน 0.5 วินาที
    motor(4, reloadSpd);
    timer = 0;
    for (int i = 0; i < 2000; i++) {
      timer++;
      if (in(limPin)) break;
      delay(1);
    }
  }
  motor(4, 0);
}

void setup() {
  //ShowADC();
  reload();
  pixy.iero();  // รีเซต zero อัตโนมัติ
  oled.text(4, 0, "SW_B => RUN");
  oled.textnit();
  Auto_z(5, 0, "SW_A => Test Shoot");
  while (!SW_B()) {
    getIMU();
    oled.text(0, 0, "Yaw=%f   ", pvYaw);
    oled.show();
    if (SW_A()) {
      reload();
      shoot();
      reload();
    }
  }
}

void loop() {
  //mission1();
  CheckLine();

}
