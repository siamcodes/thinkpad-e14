#include <POP32.h>

void setup() {
  waitSW_OK();  //COS(30) = 0.866, SIN(30)=0.5
  motor(1, -68.30);
  motor(2, 18.30);
  motor(3, 50);
  delay(1000);
  MotorStop();
}

void loop() {
}
