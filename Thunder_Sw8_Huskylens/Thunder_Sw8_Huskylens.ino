//#include <SPI.h>
#include <popx2.h>
#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#define NUM_SENSORS 8
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS],REFmax[NUM_SENSORS];
int  last_value = 0, LastError , SumError;

HUSKYLENS huskylens;
int ID1 = 1;             // HuskyLens objet
HUSKYLENSResult result;  // HuskyLens values

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {-161,-161,-161,-161,-161,-161,-161,-161};
int MaxValue[NUM_SENSORS] = {120,120,120,112,112,112,112,112};
int REF[NUM_SENSORS] = {-20,-20,-20,-24,-24,-24,-24,-24};
///////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  Wire.begin();          // I2C initialization
  while (!huskylens.begin(Wire)) {
    Serial.print("\n Check I2C");
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch to line tracking.
  //AutoRef();
  beep();
  sw_OK_press(); // Wait For Press SW
  delay(500);
  //ShowCalibrate(); //Calibrate Light of Sensor
  //SerialF(); //Serial Sensor
  //Program1();
  
  
}

void loop() {
stdPID(20, 0.11, 0.05, 100, -100) ;
//Motor(20,20);delay(1000);
// while(1){MotorStop();}

}
