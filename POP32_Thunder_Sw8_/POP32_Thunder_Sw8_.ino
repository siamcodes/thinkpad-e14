//#include <SPI.h>
#include <POP32.h>
#include "SoftwareSerial.h"
#define NUM_SENSORS 8
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS],REFmax[NUM_SENSORS];
int  last_value = 0, LastError , SumError;

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {69,66,536,57,47,57,41,62};
int MaxValue[NUM_SENSORS] = {806,777,866,791,704,743,680,799};
int REF[NUM_SENSORS] = {437,421,701,424,375,400,360,430};
///////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //AutoRef();
  beep();
  sw_OK_press(); // Wait For Press SW
  beep();
  delay(500);
  //ShowCalibrate(); //Calibrate Light of Sensor
  SerialF(); //Serial Sensor
  //Program1();
  
}

void loop() {
//stdPID(0, 0.05, 0.03, 100, -10) ;
//m1();
//Motor(20,20);delay(1000);
//while(1){MotorStop();}

}


