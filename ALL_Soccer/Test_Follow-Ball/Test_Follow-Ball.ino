#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// rotate controller
#define rot_Kp 1.35  //0.35
#define rot_Ki 0.0
#define rot_Kd 0.1  //0.0
#define idleSpd 40  // speed when not discovered ball ความเร็วในการหมุนหาลูกบอล
#define rotErrorGap 15
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// fling controller
#define fli_Kp 1.5  //1.5
#define fli_Ki 0.0
#define fli_Kd 0.2  //0.0
#define flingErrorGap 15
float spFli = 160;  //120 หุ่นยนต์จะเข้าใกล้ลูกบอลมากขึ้นถ้าเพิ่มตัวเลข
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
float thetaRad, vx, vy, spd1, spd2, spd3;

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
void setup() {
  pixy.init();
  waitSW_A_bmp();
}

void loop() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    rot_error = 150 - ballPosX;
    rot_d = rot_d + rot_error;
    rot_d = constrain(rot_d, -100, 100);
    rot_d = rot_error - rot_pError;
    rot_pError = rot_error;
    rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
    rot_w = constrain(rot_w, -100, 100);

    ballPosY = pixy.sigInfo[1][0].y;
    fli_error = spFli - ballPosY;
    fli_i = fli_i + fli_error;
    fli_i = constrain(fli_i, -100, 100);
    fli_d = fli_error - fli_pError;
    fli_pError = fli_error;
    fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
    fli_spd = constrain(fli_spd, -100, 100);

    holonomic(fli_spd, 90, rot_w);

    if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
      holonomic(0, 0, 0);
      beep();
    }
    
  }
}
