#include "SoftwareSerial.h"
#define numsensor 8
#define L 111
#define R 112
#define ALL 113
#define N 114
int Max[numsensor] = { 900, 900, 900, 900, 900, 900, 900, 900 };
int Min[numsensor] = { 250, 250, 250, 250, 250, 250, 250, 250 };
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;

int STBY = 8;
int MA1 = 6;
int MA2 = 5;
int PWMA = 3;
int MB1 = 9;
int MB2 = 10;
int PWMB = 11;

void setup() {
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(12, INPUT);        // start/stop button attachment
  digitalWrite(STBY, HIGH);  //disable standby(8)
  digitalWrite(PWMA, HIGH);  //Enable PWMA(3)
  digitalWrite(PWMB, HIGH);  //Enable PWMB(11)
  Serial.begin(9600);
  Serial.println("\n\t To start, click on the Start button");
  while (digitalRead(12))
    ;
  delay(400);
  Serial.println("\n\t Started!!");
  //Move(-100, -100, 500);
  //motor(1, 100);
  //motor(2, 100);
  //view();
}

void loop() {
  //TrackNormal(20, 0.09, 0.05);
  //TrackNormal(30,0.09,0.11);
  //TrackNormal(40,0.15,0.11);
  //TrackNormal(50, 0.25, 0.11);
  //TrackNormal(60, 0.27, 0.11);
  //TrackNormal(70, 0.35, 0.11);
  //TrackNormal(80, 0.45, 0.20);
  //TrackNormal(90, 0.46, 0.43);
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
  while (s[3] < 500) {
    ReadLine();
    Move(35, -35, 0);
  }
}

void TrackNormal(int BaseSpeed, float Kp, float Kd) {  //  แท็กเส้นดำ
  Position = ReadLine();
  error = Position - 3500;  //1500 เซนเซอร์ 4 ตัว, 3000 เซนเซอร์ 7 ตัว
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
  while (s[0] < 400 || s[3] < 400) {
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
    int x = map(analogRead(i), Min[i], Max[i], 1000, 0);  // อ่านค่าเซ้นเซอร์
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
    Serial.print(analogRead(0));
    Serial.print("\t,");
    Serial.print(analogRead(1));
    Serial.print("\t,");
    Serial.print(analogRead(2));
    Serial.print("\t,");
    Serial.print(analogRead(3));
    Serial.print("\t,");
    Serial.print(analogRead(4));
    Serial.print("\t,");
    Serial.print(analogRead(5));
    Serial.print("\t,");
    Serial.print(analogRead(6));
    Serial.print("\t,");
    Serial.println(analogRead(7));
  }
  delay(100);
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

void motor(int x, int speed) {
  switch (x) {
    case 1:
      if (speed >= 0) {
        speed += 150;
        analogWrite(MA1, speed);
        analogWrite(MA2, 0);
      } else {
        speed -= 150;
        analogWrite(MA1, 0);
        analogWrite(MA2, abs(speed));
      }
      break;
    case 2:
      if (speed >= 0) {
        speed += 150;
        analogWrite(MB1, speed);
        analogWrite(MB2, 0);
      } else {
        speed -= 150;
        analogWrite(MB1, 0);
        analogWrite(MB2, abs(speed));
      }
      break;
  }
}