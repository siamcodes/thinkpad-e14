#include <POP32.h>
#include "SoftwareSerial.h"
#define numsensor 8
#define L 111
#define R 112
#define ALL 113
#define N 114
int Max[numsensor] = { 939	,904	,932	,945	,919	,933	,935	,936 };
int Min[numsensor] = { 449	,245	,244	,401	,295	,390	,413	,430};
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;

void setup() {
  Serial.begin(9600);
  beep();
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  beep();
  delay(400);
  //Move(50,50,1000); while(1) stop(0);
  //view();
}

void loop() {
  //TrackCount(20,0.05,0.05);
  //TrackNormal(40,0.09,2.17);
  //TrackNormal(0,0.13,1.05);
  m1();

  while(1) stop(0);
}

void TrackCount(int line, int direc, int spin) {
  if (direc == L) {
    for (int i = 0; i < line; i++) {  // line จำนวนเส้น     direc ทิศทางจะใช้เซนด้านไหน    spin เลี้ยวซ้าย ขวา
      TrackTime(35, 0.02, 0.25, 120);
      TrackL(35, 0.02, 0.25);
    }
  } else if (direc == R) {
    for (int i = 0; i < line; i++) {
      TrackTime(35, 0.02, 0.25, 120);
      TrackR(35, 0.02, 0.25);
    }
  } else if (direc == ALL) {
    for (int i = 0; i < line; i++) {
      TrackTime(35, 0.02, 0.25, 120);
      TrackL(35, 0.02, 0.25);
    }
  }
  if (spin == L) {
    Move(35, 35, 200);
    stop(50);
    Left();
  } else if (spin == R) {
    Move(35, 35, 200);
    stop(50);
    Right();
  } else if (spin == N) {
    stop(0);
  }
}

void stop(int a) {
  Move(0, 0, a);
}

void Left() {  // เลี้ยวซ้าย จนกว่าจะเจอเส้น
  Move(-35, 35, 90);  //90
  ReadLine();
  while (s[0] < 500) {  //<
    ReadLine();
    Move(-35, 35, 0);
  }
}

void Right() {
  Move(35, -35, 90);
  ReadLine();
  while (s[7] < 500) {
    ReadLine();
    Move(35, -35, 0);
  }
}

void TrackNormal(int BaseSpeed, float Kp, float Kd) {  //  แท็กเส้นดำ
  Position = ReadLine();
  error = Position - 3500;  //1500 เซนเซอร์ 4 ตัว, 3500 เซนเซอร์ 8 ตัว
  PowerMotor = (Kp * error) + (Kd * (error - Last_Error));
  Last_Error = error;
  leftmotor = BaseSpeed + PowerMotor;
  rightmotor = BaseSpeed - PowerMotor;
  if (leftmotor > 100) leftmotor = 100;
  if (leftmotor < -100) leftmotor = -100;
  if (rightmotor > 100) rightmotor = 100;
  if (rightmotor < -100) rightmotor = -100;
  Move(leftmotor, rightmotor, 0);
}

void TrackTime(int BaseSpeed, float Kp, float Kd, int Timer) {
  unsigned long Last_Time = millis();
  while ((millis() - Last_Time) <= Timer) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void Track(int BaseSpeed, float Kp, float Kd) {  // อยู่ในแท็กเค้า  แท็กจนจะเจอเส้นตัด
  ReadLine();
  while (s[0] < 500 || s[7] < 500) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void TrackL(int BaseSpeed, float Kp, float Kd) {  //  จนเจอดำด้านซ้าย
  ReadLine();
  while (s[0] < 500 || s[1] < 500) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void TrackR(int BaseSpeed, float Kp, float Kd) {
  ReadLine();
  while (s[6] < 500 || s[7] < 500) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void Read() {
  for (int i = 0; i < numsensor; i++) {
    int x = map(analog10(i), Min[i], Max[i], 0, 1000);  // อ่านค่าเซ้นเซอร์
    if (x > 1000) x = 1000;
    if (x < 0) x = 0;
    s[i] = x;
  }
}

int ReadLine() {  // เอาค่าเซนเซอร์มาทำ ตำแหน่ง
  int k;
  int on_line = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  on_line = 0;
  Read();
  avg = 0;
  sum = 0;
  for (int i = 0; i < numsensor; i++) {
    if (s[i] > 200) on_line = 1;
    if (s[i] > 50) {
      avg += s[i] * (i * 1000);
      sum += s[i];
    }
  }
  if (on_line == 0) {
    if (last_value < ((numsensor - 1) * 1000) / 2) {
      return 0;
    } else {
      return (numsensor - 1) * 1000;
    }
  }
  last_value = avg / sum;
  return last_value;
}

void view() {  // แสดงค่าหน้าจอ
  while (1) {
    oled.text(0, 0, "%d  ", analog10(0));
    oled.text(1, 0, "%d  ", analog10(1));
    oled.text(2, 0, "%d  ", analog10(2));
    oled.text(3, 0, "%d  ", analog10(3));
    oled.text(4, 0, "%d  ", analog10(4));
    oled.text(5, 0, "%d  ", analog10(5));
    oled.text(6, 0, "%d  ", analog10(6));
    oled.text(7, 0, "%d  ", analog10(7));
    oled.show();
    Serial.print(analog10(0));
    Serial.print("\t,");
    Serial.print(analog10(1));
    Serial.print("\t,");
    Serial.print(analog10(2));
    Serial.print("\t,");
    Serial.print(analog10(3));
    Serial.print("\t,");
    Serial.print(analog10(4));
    Serial.print("\t,");
    Serial.print(analog10(5));
    Serial.print("\t,");
    Serial.print(analog10(6));
    Serial.print("\t,");
    Serial.println(analog10(7));
  }
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);                    //มอเตอร์ซ้าย
  motor(2, b);                    //มอเตอร์ขวา
  delay(c);
}
