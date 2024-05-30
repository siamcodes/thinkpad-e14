#include <POP32.h>
#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#define numsensor 4
int Max[numsensor] = { 320, 320, 320, 320 };
int Min[numsensor] = { 0, 0, 0, 0 };
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
  beep();beep(1);
  sw_ok_press();
  beep(1);
  //ResetTimer1();  //เปิดใช้งานคู่กับ Finish()
}

void loop() {
  //ReadHuskylens();
  TrackNormal(20, 0.05, 0.04);
  //Finish();
}
