#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <popx2.h>
HUSKYLENS huskylens;
#define numsensor 4
#define L 111
#define R 112
#define ALL 113
#define N 114
int Max[numsensor] = {480  , 698  , 543  , 508};
int Min[numsensor] = {93  , 129  , 108  , 107};
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;
int Room = 0;
void printResult(HUSKYLENSResult result);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  // view();
  // viewTag();
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
  while (1) {
    while (1) {
      huskylens.request();
      HUSKYLENSResult result = huskylens.read();
      if (result.ID == 1) {
        Room = 1;
        beep();
        break;
      }
      else if (result.ID == 2) {
        Room = 2;
        beep();
        break;
      }
      else if (result.ID == 3) {
        Room = 3;
        beep();
        break;
      }
      else if (result.ID == 4) {
        Room = 4;
        beep();
        break;
      }
      else if (result.ID == 5) {
        Room = 5;
        beep();
        break;
      }
      else if (result.ID == 6) {
        Room = 6;
        beep();
        break;
      }
      else if (result.ID == 7) {
        Room = 7;
        beep();
        break;
      }
      else if (result.ID == 9) {
        Room = 10;
        beep();
        break;
      }
      Serial.println(result.ID);
    }
    delay(1000);
    glcd(0, 0, "%d", Room);

    if (Room == 1) {
      TrackCount(1, L, L);//  1 เส้นตัด  L กลาง  ตัวกำหนดออกด้วยเซนด้านซ้าย   L ลิม กำหนดให้ซ้ายหรือ ขวา
      TrackCount(2, ALL , N);  //  N ไม่ต้องทำอะไร แล้วหยุด
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, L, L);
      TrackCount(2, L, R);
      TrackCount(1, R, R);
      TrackCount(2, L, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150)
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }

    else if (Room == 2) {
      TrackCount(1, L, L);
      TrackCount(1, R, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      stop(100);

      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, R);
      TrackCount(1, R, R);
      TrackCount(2, L, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
    else if (Room == 3) {
      TrackCount(3, L, L);
      TrackCount(2, ALL, N);
      stop(0);
    }
    else if (Room == 4) {
      TrackCount(1, L, L);
      TrackCount(1, R, R);
      TrackCount(2, L, R);
      TrackCount(2, R, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, L, L);
      TrackCount(2, L, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
    else if (Room == 5) {
      TrackCount(1, L, L);
      TrackCount(1, R, R);
      TrackCount(2, L, R);
      TrackCount(1, R, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
    else if (Room == 6) {
      TrackCount(1, L, L);
      TrackCount(1, R, R);
      TrackCount(2, L, R);
      TrackCount(1, R, R);
      TrackCount(2, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, R, N);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
    if (Room == 7) {    //  all
      //1
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      //2
      TrackCount(1, L, L);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      //3
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();

      //4
      TrackCount(3, R, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();

      //5
      TrackCount(1, L, L);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();

      //6

      TrackCount(1, ALL, L);
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();

      TrackCount(1, R, N);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
    else if (Room == 9) {   //  5 3
      TrackCount(1, L, L);
      TrackCount(1, R, R);
      TrackCount(2, L, L);
      TrackCount(1, ALL, N);
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(2, R, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      //5
      stop(100);
      while (1) {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        if (result.ID == 8) {
          beep();
          break;
        }
      }
      Move(35, 35, 200);
      Move(50, -50, 100);
      Right();
      TrackCount(1, ALL, L);
      TrackCount(1, ALL, R);
      TrackCount(1, L, L);
      TrackCount(1, ALL, N);
      Move(35, 35, 150);
      stop(2000);
      beep();
      Right();
      TrackCount(1, ALL, N);
      Move(35, 35, 260);
      stop(50);
      Right();
      stop(100);
      Move(-20, -20, 400);
      stop(100);
    }
  }
}
void loop() {
  motor(1, 0);
  motor(2, 0);
}

void TrackCount(int line, int direc, int spin) {
  if (direc == L) {
    for (int i = 0; i < line; i++) {     // line จำนวนเส้น     direc ทิศทางจะใช้เซนด้านไหน    spin เลี้ยวซ้าย ขวา
      TrackTime(35, 0.02, 0.25, 120);
      TrackL(35, 0.02, 0.25);
    }
  }
  else if (direc == R) {
    for (int i = 0; i < line; i++) {
      TrackTime(35, 0.02, 0.25, 120);
      TrackR(35, 0.02, 0.25);
    }
  }
  else if (direc == ALL) {
    for (int i = 0; i < line; i++) {
      TrackTime(35, 0.02, 0.25, 120);
      TrackL(35, 0.02, 0.25);
    }
  }
  if (spin == L) {
    Move(35, 35, 200);
    stop(50);
    Left();
  }
  else if (spin == R) {
    Move(35, 35, 200);
    stop(50);
    Right();
  }
  else if (spin == N) {
    stop(0);
  }
}

void stop(int a) {
  Move(0, 0, a);
}

void Left() {                // เลี้ยวซ้าย จนกว่าจะเจอเส้น
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

void TrackNormal(int BaseSpeed, float Kp , float Kd) {    //  แท็กเส้นดำ
  Position = ReadLine();
  error = Position - 1500;
  PowerMotor = (Kp * error) + (Kd * (error - Last_Error));
  Last_Error = error;
  leftmotor = BaseSpeed + PowerMotor;
  rightmotor = BaseSpeed - PowerMotor;
  if (leftmotor > 100) leftmotor =  100;
  if (leftmotor < -100) leftmotor = -100;
  if (rightmotor > 100) rightmotor = 100;
  if (rightmotor < -100) rightmotor = -100;
  Move(leftmotor, rightmotor, 0);
}

void TrackTime(int BaseSpeed, float Kp, float Kd, int Timer) {
  unsigned long Last_Time =  millis();
  while ((millis() - Last_Time) <= Timer) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void Track(int BaseSpeed, float Kp, float Kd) {   // อยู่ในแท็กเค้า  แท็กจนจะเจอเส้นตัด
  ReadLine();
  while (s[0] < 400 || s[3] < 400) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}
void TrackL(int BaseSpeed, float Kp, float Kd) { //  จนเจอดำด้านซ้าย
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
    int x = map(analog(i), Min[i], Max[i], 1000, 0);    // อ่านค่าเซ้นเซอร์
    if (x > 1000)x = 1000;
    if (x < 0)x = 0;
    s[i] = x;
  }
}

int ReadLine() {      // เอาค่าเซนเซอร์มาทำ ตำแหน่ง
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
    }
    else {
      return (numsensor - 1) * 1000;
    }
  }
  last_value = avg / sum;
  return last_value;
}

void viewTag() {
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
  while (1) {
    huskylens.request();
    HUSKYLENSResult result = huskylens.read();
    Serial.println(result.ID);
  }
}

void view() {      // แสดงค่าหน้าจอ
  while (1) {
    glcd(0, 0, "%d  ", analog(0));
    glcd(1, 0, "%d  ", analog(1));
    glcd(2, 0, "%d  ", analog(2));
    glcd(3, 0, "%d  ", analog(3));
    Serial.print(analog(0));
    Serial.print("\t,");
    Serial.print(analog(1));
    Serial.print("\t,");
    Serial.print(analog(2));
    Serial.print("\t,");
    Serial.println(analog(3));
  }
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

void printResult(HUSKYLENSResult result) {              // ปริ้นค่าตำแหน่งเฉยยยย
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  }
  else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  }
  else {
    Serial.println("Object unknown!");
  }
}
