//#include <SPI.h>
#include <POP32.h>
#define NUM_SENSORS 4
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS], REFmax[NUM_SENSORS];
int last_value = 0, LastError, SumError;

////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {155,144,116,178};
int MaxValue[NUM_SENSORS] = {963,885,821,958};
int REF[NUM_SENSORS] = {559,514,468,568};
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
  stdPID(40, 0.07, 0.05, 100, -40);  //เอาใว้เทส
  //m1();
  //while(1){MotorStop();}

/*
  FF(60, 0.20, 0.17, 'p', 50, 100, -100);
  ReadSensor();
  if ((F[0] <= REF[0] && F[1] <= REF[1] && F[2] <= REF[2] && F[3] <= REF[3])) {
    if (F[0] < 600) {
      SpinL();
      sound(1000, 100);
    }

    if (F[3] < 600) {
      SpinR();
      sound(2000, 200);
    }
    
     if (F[0] < 500 && F[3] < 600) {  
        Uturn(); sound(3000, 200);
      } 
      if (F[0] > 500 && F[3] > 500) {
        fd2(40,40);
        delay(100);
      }
      
  }
  */
}
