#include <POP32.h>	// POP-X2 Board
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
HUSKYLENS huskylens;      //HUSKYLENS green line >> SDA; blue line >> SCL
int ID1 = 1;
void printResult(HUSKYLENSResult result);
int ReadHuskylens();
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;
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
   error = 0;
 } else {
   //huskylens.request();
   //HUSKYLENSResult result = huskylens.read();
   //printResult(result);
   TrackNormal(20, 0.15 , 0.10);
 }

    //TrackNormal(20, 0.11 , 0.05);
    //TrackNormal(30, 0.11 , 0.05);
    //TrackTime(30, 0.11, 0.07,1500);
    //TrackTime(50, 0.11, 0.07,1000);
    //TrackTime(20, 0.07 , 0.05,1000);
    //TrackTime(70, 0.15, 0.09,1000);
    //while (1) { stop(0); }
}

int ReadHuskylens() {
  huskylens.request(ID1);
  HUSKYLENSResult result = huskylens.read();
  error = map(result.xTarget, 40, 272, -100, 100);
  return error;
}

void TrackNormal(int BaseSpeed, float Kp , float Kd) {    //  แท็กเส้นดำ
  ReadHuskylens();  //อ่านค่าจากกล้อง
  //Position = ReadLine();
  //error = Position - 1500;
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
