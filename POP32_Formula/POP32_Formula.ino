#include <POP32.h>
//#include "SoftwareSerial.h"
#include <MCP3XXX.h>
MCP3008 adc;  //SPI
#define CS_PIN  PB11  //ss 8
#define MOSI_PIN  PC14  //di 7
#define MISO_PIN   PA15  //do 6
#define CLOCK_PIN  PC15  //clk 5

#define numsensor 8
#define L 111
#define R 112
#define ALL 113
#define N 114
int Max[numsensor] = {775,	753,	796,	778,	730,	819,	729,	739};
int Min[numsensor] = {36,	34,	33,	32,	31,	34,	33,	34};
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;

void setup() {
  Serial.begin(9600);
  adc.begin(CS_PIN, MOSI_PIN, MISO_PIN, CLOCK_PIN);  // adc.begin(SS, MOSI, MISO, SCK);  //CS, DI,DO,CLK
  beep();
  oled.text(2,0,"SW_OK --> RUN");
  oled.text(3,0,"MARK Robotic");
  oled.show();
  sw_OK_press();  //รอจนกว่าจพกดปุ่ม ok
  sound(1500, 100);
  sound(3000, 100);
  //Grip();
  //Put();
  //Grip();
  //Move(20,20,1000);
  //END();
  //view();
  //TrackTime(100, 0.01, 0.13,500);   //เส้นประ
//TrackTime(100, 0.04, 0.15,1000);    //โค้งเยอะ
//TrackTime(50, 0.029, 0.23,2000);    //เส้นโค้งมีความเร็วถ50
 //TrackTime(60, 0.032, 0.28,2000);   //เส้นโค้งมีความเร็วถ60
 //    TrackTime(70, 0.035, 0.28,1500); //เส้นโค้งมีความเร็วถ70

}

void loop() {
m1();


  END();
}

void END() {
  while (1) MotorStop(10);
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
    MotorStop(50);
    Left();
  } else if (spin == R) {
    Move(35, 35, 200);
    MotorStop(50);
    Right();
  } else if (spin == N) {
    MotorStop(0);
  }
}

//หยุด-------------------------
void stop(int a) {
  Move(0, 0, a);
}

void MotorStop(int dl) {
  Move(0, 0, dl);
}

void Left() {  // เลี้ยวซ้าย จนกว่าจะเจอเส้น
  Move(-45, 45, 150);
  ReadLine();
  while (s[7] < 500) {
    ReadLine();
    Move(-35, 35, 0);
  }
}

void Right() {
  Move(45, -45, 150);
  ReadLine();
  while (s[0] < 500) {
    ReadLine();
    Move(35, -35, 0);
  }
}

void TrackPID(int BaseSpeed, float Kp, float Kd) {  //  แท็กเส้นดำ
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
    TrackPID(BaseSpeed, Kp, Kd);
  }
  MotorStop(10);
}

void Track(int BaseSpeed, float Kp, float Kd, int dl) {  // อยู่ในแท็กเค้า  แท็กจนจะเจอเส้นตัด
  while (1) {
    ReadLine();
    if(s[1] < 500 && s[6] < 500){
      break;
    }
    TrackPID(BaseSpeed, Kp, Kd);
  }
  MotorStop(dl);
}
void t(float BaseSpeed, float Kp, float Kd) {
  while (1) {
    ReadLine();
    if (s[1] < 400 && s[6] < 400) {
      break;
    } else {
      TrackPID(BaseSpeed, Kp, Kd);
    }
  }
  while (1) {
    ReadLine();
    if (s[1] > 450 and s[6] > 450) {
      break;
    } else {
      TrackPID(BaseSpeed, Kp, Kd);
    }
  }
}

void TrackL(int BaseSpeed, float Kp, float Kd) {  //  จนเจอดำด้านซ้าย
  ReadLine();
  while (s[0] < 500 || s[1] < 500) {
    TrackPID(BaseSpeed, Kp, Kd);
  }
}

void TrackR(int BaseSpeed, float Kp, float Kd) {  //  จนเจอดำด้านขวา
  ReadLine();
  while (s[6] < 500 || s[7] < 500) {
    TrackPID(BaseSpeed, Kp, Kd);
  }
}

//วนอ่านค่าเซนเซอร์ 10 bit---------------
void Read() {
  for (int i = 0; i < numsensor; i++) {
    //int x = map(adc.analogRead(i), Min[i], Max[i], 1000, 0);  // อ่านค่าเซ้นเซอร์ ถ้าไม่เกาะเส้นให้เปลี่ยน  1000, 0
    int x = map(adc.analogRead(i), Min[i], Max[i], 0, 1000);  // อ่านค่าเซ้นเซอร์ ถ้าไม่เกาะเส้นให้เปลี่ยน  1000, 0
    if (x > 1000) x = 1000;
    if (x < 0) x = 0;
    s[i] = x;
  }

}

// เอาค่าเซนเซอร์มาระบุตำแหน่ง-------------
int ReadLine() {
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

//แสดงเซนเซอร์ค่าหน้าจอและ Serial Monitor--------
void view() {
  while (1) {
    for (int i = 0; i < numsensor; i++) {
      s[i] = adc.analogRead(i);  // read Channel 0 from MCP3008 ADC (pin 1)
      Serial.print(s[i]);
      Serial.print(",\t");
    }
    Serial.println("");
    delay(200);
  }
}

//มอเตอร์วิ่ง ---------------------
void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

//เดินหน้า เจอแยกแล้วหยุด ---------
void FF(int spd, float Kp, float Kd, char select, int dl) {
  while (1) {
    ReadLine();
    if ((s[0] <= 400 && s[7] <= 400)) {
      break;
    }
    TrackPID(spd, Kp, Kd);
  }
  MotorStop(10);
  if (select == 's') {
    Move(-spd, -spd, dl);
    while (1) {
      ReadLine();
      if (s[0] >= 400 && s[7] >= 400) break;
      Move(-20, -20, 0);
    }
    MotorStop(10);
  } else if (select == 'p') {
    Move(spd, spd, dl);
    while (1) {
      ReadLine();
      if (s[0] >= 400 && s[7] >= 400) break;
      Move(20, 20, 0);
    }
    MotorStop(10);

  } else if (select == 'l') {
    Move(spd, spd, dl);
    SpinL();
  } else if (select == 'r') {
    Move(spd, spd, dl);
    SpinR();
  }
}


//เลี้ยวซ้าย-------------------
void SpinL() {
  Move(-60, 60, 100);
  MotorStop(10);
  while (1) {
    ReadLine();
    if (s[7] <= 500) {
      MotorStop(10);
      Move(-60, 60, 20);
      break;
    }
    Move(20, -20, 0);
  }
  MotorStop(10);
}

//เลี้ยวขวา ------------------
void SpinR() {
  Move(60, -60, 100);
  MotorStop(10);
  while (1) {
    ReadLine();
    if (s[0] <= 500) {
      MotorStop(10);
      Move(60, -60, 20);
      break;
    }
    Move(-20, 20, 0);
  }
  MotorStop(10);
}

//หมุนตัวกลับ ---------------
void Uturn() {  //ยูเทิร์นทางขวา
  Move(-65, 65, 275);
  MotorStop(10);
  while (1) {
    ReadLine();
    if (s[7] <= 400) {
      MotorStop(10);
      Move(50, -50, 20);
      break;
    }
    Move(-20, 20, 0);
  }
  MotorStop(10);
}