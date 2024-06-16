//#include <SPI.h>
#include <POP32.h>
#include "SoftwareSerial.h"
#define NUM_SENSORS 8
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS],REFmax[NUM_SENSORS];
int  last_value = 0, LastError , SumError;

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {377,120,120,306,147,264,287,317};
int MaxValue[NUM_SENSORS] = {909,811,803,851,807,837,846,891};
int REF[NUM_SENSORS] = {643,465,461,578,477,550,566,604};
///////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //AutoRef();
  beep();
  sw_OK_press(); // Wait For Press SW
  beep();
  delay(500);
  //ShowCalibrate(); //Calibrate Light of Sensor
  //SerialF(); //Serial Sensor
  //Program1();
  
}

void loop() {
//Motor(20,20);delay(1000); 
//stdPID(0, 0.03, 0.03, 100, -10) ;
m1();

while(1){MotorStop();}

}


