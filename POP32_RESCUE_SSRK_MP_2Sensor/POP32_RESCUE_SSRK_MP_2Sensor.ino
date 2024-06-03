#include <POP32.h>
#include "SoftwareSerial.h"
#define numsensor 2
#define L 111
#define R 112
#define ALL 113
#define N 114
int Max[numsensor] = { 3759	,3763	 };
int Min[numsensor] = { 757	,760 };
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;
//-----------------------------------------------
int tag_S0 = 1500;  //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1500;  //อ่านค่าพื้นสีเขียว ด้านขวา
int T0 = 0;
int T3 = 0;
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)
#define Dist (analog(A8) / 41)
//-----------------------------------------------

void setup() {
  Serial.begin(9600);
  beep();
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  //beep();
  delay(400);
  //Move(20,20,1000); while(1) stop(0);
  //view();
}

void loop() {
  //TrackNormal(20, 0.03, 0.05);
  //readTag();
  //m1();
  m2();
  //while (1) stop(0);
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
  Move(-35, 35, 90);
  ReadLine();
  while (s[0] < 500) {
    ReadLine();
    Move(-35, 35, 0);
  }
}

void Right() {
  Move(35, -35, 90);
  ReadLine();
  while (s[1] < 500) {
    ReadLine();
    Move(35, -35, 0);
  }
}

void TrackNormal(int BaseSpeed, float Kp, float Kd) {  //  แท็กเส้นดำ
  Position = ReadLine();
  error = Position - 500;  //1500 เซนเซอร์ 4 ตัว, 3000 เซนเซอร์ 7 ตัว
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
  while (s[0] < 400 || s[1] < 400) {
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
  while (s[2] < 500 || s[3] < 500) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void Read() {
  for (int i = 0; i < numsensor; i++) {
    int x = map(analog(i), Min[i], Max[i], 1000, 0);  // อ่านค่าเซ้นเซอร์
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
    oled.text(0, 0, "%d  ", analog(0));
    oled.text(1, 0, "%d  ", analog(1));
    oled.show();
    Serial.print(analog(0));
    Serial.print("\t,");
    Serial.println(analog(1));
  }
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

////////////////////////////////////////////////////////////////
void FF(int spd, float Kp, float Kd, char select, int dl) {
  while (1) {
    ReadLine();
    if ((s[0] <= 400 && s[1] <= 400)) {
      break;
    }
    TrackNormal(spd, Kp, Kd);
  }
  MotorStop();
  if (select == 's') {
    Motor(-spd, -spd);
    delay(dl);
    while (1) {
      ReadLine();
      if (s[0] >= 400 && s[1] >= 400) break;
      Motor(-20, -20);
    }
    MotorStop();
  } else if (select == 'p') {
    Motor(spd, spd);
    delay(dl);
    while (1) {
      ReadLine();
      if (s[0] >= 400 && s[1] >= 400) break;
      Motor(20, 20);
    }
    MotorStop();

  } else if (select == 'l') {
    Motor(spd, spd);
    delay(dl);
    SpinL();
  } else if (select == 'r') {
    Motor(spd, spd);
    delay(dl);
    SpinR();
  }
}

void Motor(int leftsp, int rightsp) {
  motor(1, leftsp);
  motor(2, rightsp);
}

void MotorStop() {
  Motor(0, 0);
  delay(10);
  //ao(); delay(10);
}

void SpinL() {
  //Motor(100, 100); delay(100); MotorStop();
  Motor(-60, 60);
  delay(200);
  while (1) {
    ReadLine();
    if (s[0] <= 500) {
      MotorStop();
      Motor(-40, 40);
      delay(20);
      break;
    }
    Motor(20, -20);
  }
  MotorStop();
}

void SpinR() {
  //Motor(100, 100); delay(100); MotorStop();
  Motor(60, -60);
  delay(200);
  while (1) {
    ReadLine();
    if (s[1] <= 500) {
      MotorStop();
      Motor(40, -40);
      delay(20);
      break;
    }
    Motor(-20, 20);
  }
  MotorStop();
}

void Uturn() {
  //Motor(100, 100); delay(100); MotorStop();
  Motor(60, -60);
  delay(500);
  while (1) {
    ReadLine();
    if (s[1] <= 500) {
      MotorStop();
      Motor(50, -50);
      delay(20);
      break;
    }
    Motor(-20, 20);
  }
  MotorStop();
}