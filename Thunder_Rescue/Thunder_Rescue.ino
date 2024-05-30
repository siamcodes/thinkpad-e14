//#include <SPI.h>
#include <POP32.h>
#define NUM_SENSORS 4
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3 };
int F[NUM_SENSORS];
int REFmin[NUM_SENSORS], REFmax[NUM_SENSORS];
int last_value = 0, LastError, SumError;

////////////////////////////////////////////////////////
int MinValue[NUM_SENSORS] = {359,428,414,430};
int MaxValue[NUM_SENSORS] = {762,802,802,802};
int REF[NUM_SENSORS] = {560,615,608,616};
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
  //stdPID(0, 0.05, 0.03, 100, -10);  //เอาใว้เทส
  //m1();
  //while(1){MotorStop();}
 
    stdPID(60, 0.20, 0.15, 100, -100);
    //FF(60, 0.20, 0.17, 'p', 50, 100, -100);
    readCalibrate();
    ReadSensor();
    if ((F[0] <= REF[0] && F[1] <= REF[1] && F[2] <= REF[2] && F[3] <= REF[3])) {
      if (F[0] < 300) {
        //sound(1000, 100);
        SpinL();
      } 
      
      if (F[3] < 300) {
        //sound(2000, 200);
        SpinR();
      } 
     /* 
     if (F[0] < 500 && F[3] < 600) {
        sound(3000, 200);
        Uturn();
      } 
      if (F[0] > 500 && F[3] > 500) {
        beep();
        fd2(40,40);
        delay(200);
      }
      */
    }
 
}



