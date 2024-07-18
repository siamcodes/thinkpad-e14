#include <POP32.h>
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
float thetaRad, vx, vy, spd1, spd2, spd3;
int L,C,R;

void ReadADC(){
  L= analog(1);
  C= analog(2);
  R= analog(3);
}
 
 void ShowADC(){
  ReadADC();
  oled.text(0, 0, "L=%d", L);
  oled.text(1, 0, "C=%d", C);
  oled.text(2, 0, "R=%d", R);
  oled.show();
 }

void setup() { 
  ShowADC();
  beep();
}

void loop() {
  waitSW_OK();
  motor(1,-30);
  motor(2,-30);
  motor(3,-30);
  //holonomic(30, 0, 0);
  delay(3000);
  ao();
}

