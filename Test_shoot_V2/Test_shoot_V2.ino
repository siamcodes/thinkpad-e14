#include <POP32.h>
#define limPin PA0
#define reloadSpd 65  //ความเร็วมอเตอshoot
int timer = 0;

void shoot() {
  motor(4, reloadSpd);
  delay(150);
  motor(4, 0);
  delay(50);
}

void reload() {
  motor(4, reloadSpd);
  timer = 0;
  for (int i = 0; i < 2000; i++) {
    timer++;
    if (in(limPin)) break;
    delay(1);
  }

  if (timer == 2000) { // ถ้าก้านยิ่งติด
    motor(4, -reloadSpd); // เลื่อนก้านยิ่งไปข้างหน้า
    delay(500);     //ก่อน 0.5 วินาที
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

void setup() {oled.mode(2);}
void loop() {
  if (SW_A()) { reload();}
  if (SW_B()) { shoot(); }
  if (SW_OK()) {shoot();reload();}
}
