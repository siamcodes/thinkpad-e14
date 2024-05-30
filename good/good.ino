#include <POP32.h>
#include <POP32_Pixy2.h>.h>
// ลำดับ sensor  A0 | A1 || A2 | A3
int min_S1 = 1450;                //อ่านค่าเส้นสีดำ ด้านซ้าย
int max_S1 = 3500;                //อ่านค่าพื้นสีขาว ด้านซ้าย
int min_S2 = 1500;                //อ่านค่าส้นสีดำ ด้านขวา
int max_S2 = 3800;                //อ่านค่าพื้นสีขาว ด้านขวา
int maxSP = 50;                   //ความเร็วสูงสุดที่ต้องการ
int Speed, TurnSpeed, SlowSpeed;  //ตัวแปรความเร็ว เพื่อให้ปรับค่าเพิ่ม-ลดความเร็ว สะดวกขึ้น
float k = 1.0;                    //ค่าอัตราการขยายของความไวเซนเซอร์
#define val_S1 map(analog(1), min_S1, max_S1, 0, 100)
#define val_S2 map(analog(2), min_S2, max_S2, 0, 100)
int tag_S0 = 1500;  //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1500;  //อ่านค่าพื้นสีเขียว ด้านขวา
int T0 = 0;
int T3 = 0;
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)
#define Dist (analog(A8) / 41)

POP32_Pixy2 pixy;
#define MAX_Spd 70
#define head_Kp 0.20
#define head_Ki 0.00
#define head_Kd 0.05
float head_sp = 160;
float head_error, hI, hD, hPrevError, head_spd;
#define dis_Kp 0.20
#define dis_Ki 0.0
#define dis_Kd 0.05
float dis_sp = 150;  // distance setpoint y
float dis_error, dI, dD, dPrevError, dis_spd;

const int h_gap = 10;
const int d_gap = 10;
//----------------------------------------------
void setup() {
  Speed = 20;
  SlowSpeed = 10;
  TurnSpeed = 40;  //เหมาะสุดที่ 40-50 (*60 ขึ้นไปเลี้ยวหลุดเส้น*)
  pixy.init();

  while (!SW_OK()) {  //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(1, 0, "L=%d ", analog(1));
    oled.text(2, 0, "R=%d ", analog(2));
    oled.text(3, 0, "VS1=%d ", val_S1);
    oled.text(4, 0, "VS2=%d ", val_S2);
    oled.text(5, 0, "TagL=%d  ", analog(0));
    oled.text(6, 0, "TagR=%d  ", analog(3));
    oled.show();
    //oled.text(0, 0, "TagL = %d ", analog(0));
    //oled.text(2, 0, "TagR = %d ", analog(3));
    //oled.text(4, 0, "VS1 = %d ", val_S0);
    //oled.text(6, 0, "VS3 = %d ", val_S3);
    //oled.show();
  }
  beep();
}
void loop() {
  Trac();
}
