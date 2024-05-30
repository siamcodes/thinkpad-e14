#include <popx2.h>	// POP-X2 Board
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

#define numsensor 4
int Max[numsensor] = { 3580, 3598, 3543, 3508 };
int Min[numsensor] = { 1800, 1380, 348, 407 };
unsigned long s[numsensor];

HUSKYLENS huskylens;      //HUSKYLENS green line >> SDA; blue line >> SCL
int ID1 = 1;
void printResult(HUSKYLENSResult result);
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position, Pos;
int last_value = 0;
int Speed = 0;
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
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch to line tracking.
  beep();
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  beep();
  delay(400);
  //Move(20, 20, 1000); //เอาใว้ทดสอบมอเตอร์
}

void loop() {
  
      if (!huskylens.request(ID1)) {
        Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
      } else if (!huskylens.isLearned()) {
        Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
      } else if (!huskylens.available()) {
        Serial.println(F("No block or arrow appears on the screen!"));
      } else {
        huskylens.request();
        HUSKYLENSResult result = huskylens.read();
        //printResult(result);  //เอาไว้ดูค่า x,y ถ้าจะให้วิ่งให้ใส่คอมเมนต์

        int y = result.yTarget;
        //int x = result.xTarget;
        
        if (y == 0 )TrackTime(50, 0.18, 0.09, 1);
        else if (y > 0 && y < 69) TrackTime(40, 0.19, 0.18, 1); 
        else if (y >= 70 )TrackTime(30, 0.18, 0.19, 1 );
        

        //TrackNormal(30, 0.17 , 0.09);
        //TrackNormal(40, 0.13 , 0.07);
        //TrackNormal(50, 0.14 , 0.07);
        //TrackNormal(60, 0.15 , 0.08);
        //TrackNormal(70, 0.16 , 0.09);
        //TrackNormal(80, 0.17 , 0.10);
      }
 /*

 
  TrackTime(50, 0.18, 0.09, 1000);
  TrackTime(30, 0.19, 0.18, 3000); //โค้ง1
  TrackTime(50, 0.18, 0.17, 500);
  TrackTime(80, 0.18, 0.17, 2000);
  TrackTime(60, 0.18, 0.09, 1000);
  TrackTime(30, 0.18, 0.17, 1000); //โค้ง2
  TrackTime(20, 0.17, 0.17, 1000);
  TrackTime(20, 0.17, 0.17, 1000);
  TrackTime(30, 0.18, 0.19, 2000);
  TrackTime(30, 0.18, 0.17, 1500); //โค้ง3
  TrackTime(30, 0.18, 0.17, 2000);
  TrackTime(30, 0.18, 0.17, 1500); //โค้ง4
  stop(10);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(30, 0.18, 0.19, 1000);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(60, 0.18, 0.17, 1000);
  stop(10);
  TrackTime(20, 0.18, 0.17, 1000);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(20, 0.18, 0.17, 1000);
  TrackTime(40, 0.18, 0.17, 1000);
  TrackTime(70, 0.18, 0.10, 700);
  TrackTime(40, 0.18, 0.17, 700);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(30, 0.19, 0.17, 1000);
  TrackTime(20, 0.18, 0.17, 1000);
  stop(10);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(20, 0.18, 0.17, 1000);
  TrackTime(40, 0.18, 0.17, 1000);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(40, 0.18, 0.17, 1000);
  TrackTime(30, 0.18, 0.17, 1000);
  TrackTime(50, 0.18, 0.9, 1000);
  TrackTime(80, 0.18, 0.9, 1000);
  
  while (1) stop(0);
  
 */
}

void ReadHuskylens() {
  huskylens.request();
  HUSKYLENSResult result = huskylens.read();
  error = map(result.xCenter, 40, 280, -100, 100);
}

void TrackNormal(int BaseSpeed, float Kp , float Kd) {    //  แท็กเส้นดำ
  //Position = ReadHuskylens(); //อ่านค่าจากกล้อง
  ReadHuskylens();
  //Position = ReadLine();
  //error = Pos -z;
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

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

void stop(int a) {
  Move(0, 0, a);
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
  //Read();

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
