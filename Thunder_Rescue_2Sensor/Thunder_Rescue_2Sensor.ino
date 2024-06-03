//#include <SPI.h>
#include <POP32.h>
#define NUM_SENSORS 2
uint8_t F_PIN[NUM_SENSORS] = { 0, 1 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS], REFmax[NUM_SENSORS];
int last_value = 0, LastError, SumError;
int L = 0, R = 0;
////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = { 157, 180 };
int MaxValue[NUM_SENSORS] = { 964, 951 };
int REF[NUM_SENSORS] = { 560, 565 };
////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //AutoRef();
  beep();
  sw_OK_press();  // Wait For Press SW
  delay(500);
  //ShowCalibrate(); //Calibrate Light of Sensor
  //SerialF();  //Serial Sensor  //ดำค่าน้อย  ขาวค่ามาก
  //Program1();
}

void loop() {
  //stdPID(0, 0.07, 0.05, 100, -40);  //เอาใว้เทส
  //m1();
  //while(1){MotorStop();}


  //FF(40, 0.07, 0.05, 'p', 10, 100, -100);
  stdPID(40, 0.09, 0.09, 100, -100);
  ReadSensor();
  if ((F[0] <= REF[0] && F[1] <= REF[1])) {
    if (analog10(4) < 500) {
      SpinL();
      //sound(1000, 100);
    }
    if (analog10(5) < 500) {
      SpinR();
      //sound(2000, 200);
    }

    //while (1) { MotorStop(); }
    // if (L < 500 && R < 500) {
    //   Uturn();
    //   sound(3000, 200);
    // }
    // if (F[0] > 500 && F[3] > 500) {
    //   fd2(40, 40);
    //   delay(100);
    // }
  }
}
