#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;

// rotate controller
#define rot_Kp 0.08  //0.35
#define rot_Ki 0.0
#define rot_Kd 0.15  //0.0


float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;

float thetaRad, vx, vy, spd1, spd2;

void setup() {
  pixy.init();
  waitSW_A_bmp();
}


void loop() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    rot_error = 170-ballPosX;
    rot_d = rot_d + rot_error;
    rot_d = constrain(rot_d, -100, 100);
    rot_d = rot_error - rot_pError;
    rot_pError = rot_error;
    rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
    [rot_w] = constrain(rot_w, -100, 100);
  
  spd1=20+rot_w ;
  spd2=20-rot_w ;
  motor(1, spd1);
  motor(2, spd2);
  beep();
  
  }
  else{
     motor(1, 0);
  motor(2, 0);
  }
}
