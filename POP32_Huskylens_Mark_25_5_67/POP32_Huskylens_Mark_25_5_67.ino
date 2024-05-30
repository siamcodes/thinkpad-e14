// 15/03/2022 - Chariot robot with PID
#include <POP32.h>
#include <HUSKYLENS.h>
HUSKYLENS huskylens;
int ID1 = 1;                                         // HuskyLens objet
HUSKYLENSResult result;                              // HuskyLens values
float Kp = 0.00, Ki = 0.000, Kd = 0.00;              // PID constants
int pid, p = 0, i = 0, d = 0, err = 0, lastErr = 0;  // PID variables
//-----------------------
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;
int BaseSpeed = 0;
//----------------------
void setup() {
  delay(400);            // for soft reset consideration
  Serial.begin(115200);  // Serial initialization
  Wire.begin();          // I2C initialization
  while (!huskylens.begin(Wire)) {
    Serial.print("\n Check I2C");
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch to line tracking.
  beep();
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  beep();        
  delay(400);
  //Move(20,20,1000);
}

void loop() {
  //stdPID(40, 0.22, 0.40, 100, 0); //cycle_M
  stdPID(20, 0.22, 0.43, 100, 0);  //TracPID(BaseSpeed, Kp, Kd, maxsp, minsp)  //
  //stdPID(70, 0.3, 0.6, 100, 0);  ทางโค้ง
  //stdPID(60, 0.38, 1.50, 100, 0);
  //FFtimer(70, 0.20, 0.5, 500, 100, 0);
 //FFtimer(100, 0.4, 0.7,2000, 90, -10);
 //FFtimer(60, 0.20, 0.5, 1500, 100, 0);
  //m1();
   //while (1) { stop(0); }
}
