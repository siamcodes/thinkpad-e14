#include <POP32.h>
#include <POP32_Pixy2.h>.h>
// ลำดับ sensor  A0 | A1 || A2 | A3
int min_S1 = 1820;                //อ่านค่าเส้นสีดำ ด้านซ้าย
int max_S1 = 3200;                //อ่านค่าพื้นสีขาว ด้านซ้าย
int min_S2 = 1760;                //อ่านค่าส้นสีดำ ด้านขวา
int max_S2 = 3300;                //อ่านค่าพื้นสีขาว ด้านขวา
int maxSP = 50;                   //ความเร็วสูงสุดที่ต้องการ
int Speed, TurnSpeed;  //ตัวแปรความเร็ว เพื่อให้ปรับค่าเพิ่ม-ลดความเร็ว สะดวกขึ้น
float k = 1.0;                    //ค่าอัตราการขยายของความไวเซนเซอร์
#define val_S1 map(analog(1), min_S1, max_S1, 0, 100)
#define val_S2 map(analog(2), min_S2, max_S2, 0, 100)
int tag_S0 = 1600;  //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1800;  //อ่านค่าพื้นสีเขียว ด้านขวา
int T0 = 0;
int T3 = 0;
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)
#define Dist (analog(A8) / 41)

POP32_Pixy2 pixy;
#define MAX_Spd 40
#define head_Kp 1.10  //เพิ่มค่า Kp เพื่อให้บอลเข้าจุด Set point ลูกบอลอยู่ตรงกลางหุ่นยนต์พอดี
#define head_Ki 0.0
#define head_Kd 0.50
float head_sp = 160;
float head_error, hI, hD, hPrevError, head_spd;
#define dis_Kp 1.10
#define dis_Ki 0.0
#define dis_Kd 0.50
float dis_sp = 140;  // distance setpoint y
float dis_error, dI, dD, dPrevError, dis_spd;

const int h_gap = 30;
const int d_gap = 15;

int TotalTime = 4500; //ระยะเวลำที่หุ่นยนต์ไม่พบเส้น
unsigned long EndTime = 0;
//----------------------------------------------
void setup() {
  Speed = 20;
  TurnSpeed = 30;
  servo(1, 160);     //ตั้งตรง
  servo(2, 180);     //ปิดทางออก
  pixy.init();


  while (!SW_OK()) {  //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(0, 0, "L=%d ", analog(1));
    oled.text(1, 0, "R=%d ", analog(2));
    oled.text(2, 0, "VS1=%d ", val_S1);
    oled.text(3, 0, "VS2=%d ", val_S2);
    oled.text(4, 0, "VS0 = %d ", val_S0);
    oled.text(5, 0, "VS3 = %d ", val_S3);
    oled.text(6, 0, "TagL = %d ", analog(0));
    oled.text(7, 0, "TagR = %d ", analog(3));
    oled.show();
  }
  beep();

}

void loop() {
  Ball2();
  
}


//  Tarck();                       //โค้ดเดินตามเส้น-เก็บบอล
//  ao();
//  oled.clear();
//  oled.text(0, 0, "Finish");
//  oled.show();
//  while (1) {
//    Ball();
//  }
