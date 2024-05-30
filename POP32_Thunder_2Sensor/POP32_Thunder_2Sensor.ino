//#include <SPI.h>
#include <POP32.h>
#include "SoftwareSerial.h"
#define NUM_SENSORS 2
uint8_t F_PIN[NUM_SENSORS] = { 0, 1};
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS],REFmax[NUM_SENSORS];
int  last_value = 0, LastError , SumError;

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {83,92};
int MaxValue[NUM_SENSORS] = {951,953};
int REF[NUM_SENSORS] = {517,522};
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
  
//stdPID(0, 0.07, 0.03, 100, -10) ;
//m1();
//Motor(20,20);delay(1000);
//while(1){MotorStop();}

}


