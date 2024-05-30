#include <POP32.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
HUSKYLENS huskylens;
//----
#define numsensor 7
int Max[numsensor] = { 200, 200, 200, 200, 200, 200, 200 };
int Min[numsensor] = { 140, 140, 140, 140, 100, 140, 140 };
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0, LastError, SumError;
//HUSKYLENS huskylens;
int ID1 = 1;  // HuskyLens objet
//HUSKYLENSResult result;                              // HuskyLens values
//----
void printResult(HUSKYLENSResult result);

void setup() {
  Serial.begin(115200);
  Wire.begin();  // I2C initialization

  while (!huskylens.begin(Wire)) {
    Serial.println("Begin failed!");
    Serial.println("1.Please recheck the  Protocol Type  in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)");
    Serial.println("2.Please recheck the connection.");
    delay(100);
  }
  beep();
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  beep(1);        //เสียงบัซเซอร์ 0-3
}

void loop() {
  TrackNormal(30, 0.5, 0.5);
}
