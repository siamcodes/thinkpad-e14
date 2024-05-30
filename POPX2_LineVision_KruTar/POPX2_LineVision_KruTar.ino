#include <popx2.h>
#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#define numsensor 8
int Max[numsensor] = { 200, 200, 200, 200,200,200,200,200 };
int Min[numsensor] = { 50, 50, 50, 50, 50, 50, 50, 50 };
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;
long Timer0, StartTimer0, Timer1, StartTimer1;  //ตัวแปรจับเวลา Timer0=จับเวลาการแทรคเส้น Timer1=ใช้เวลาของภาระกิจ

HUSKYLENS huskylens;
int ID1 = 1;             // HuskyLens objet
HUSKYLENSResult result;  // HuskyLens values

void setup() {
  Serial.begin(115200);  // Serial initialization
  Wire.begin();          // I2C initialization
  while (!huskylens.begin(Wire)) {
    Serial.print("\n Check I2C");
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch to line tracking.
  beep();
  sw_ok_press();
  beep(1);
  //ResetTimer1();  //เปิดใช้งานคู่กับ Finish()
}

void loop() {
  //ReadHuskylens();
  TrackNormal(10, 0.11, 0.04);
  //Finish();
}
