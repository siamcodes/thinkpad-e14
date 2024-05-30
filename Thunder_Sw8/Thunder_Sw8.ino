//#include <SPI.h>
#include <POP32.h>
#define NUM_SENSORS 8
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS],REFmax[NUM_SENSORS];
int  last_value = 0, LastError , SumError;

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {158,138,152,136,138,140,180,126};
int MaxValue[NUM_SENSORS] = {527,535,606,621,610,613,699,473};
int REF[NUM_SENSORS] = {342,336,379,378,374,376,439,299};
///////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  //AutoRef();
  beep();
  sw_OK_press(); // Wait For Press SW
  delay(500);
//ShowCalibrate(); //Calibrate Light of Sensor
  //SerialF(); //Serial Sensor
  //Program1();
  
  
}

void loop() {
m1();
//Motor(20,20);delay(1000);
//m2();

 while(1){MotorStop();}

}
