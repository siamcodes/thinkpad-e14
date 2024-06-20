//#include <SPI.h>
#include <POP32.h>
//#include "SoftwareSerial.h"
#define NUM_SENSORS 8
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS], REFmax[NUM_SENSORS];
int last_value = 0, LastError, SumError;

///////////////////////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {90,43,63,80,74,73,54,53};
int MaxValue[NUM_SENSORS] = {746,429,660,765,725,729,732,732};
int REF[NUM_SENSORS] = {418,236,361,422,399,401,393,392};
///////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //AutoRef();
  beep();
  oled.text(4, 0, "SW_OK => RUN");
  oled.text(5, 0, "SW_A => Test Servo");
  while (!SW_OK()) {
    oled.show();
    if (SW_A()) {
      GripDown();
      Grip();
      GripUp();
      GripDown();
      Put();
      GripUp();
    }
  }

  //sw_OK_press(); // Wait For Press SW
  beep();
  delay(500);
  //ShowCalibrate(); //Calibrate Light of Sensor
  //SerialF(); //Serial Sensor
  //Program1();
}

void loop() {
  //Motor(20,20);delay(1000);          //เอาใว้ทดสอบการต่อมอเตอร์
  //stdPID(0, 0.03, 0.03, 100, -10) ;  //เอาใว้ทดสอบ PID
  m1();
  while (1) { MotorStop(); }           //หยุดวิ่งตลอดไป
}
