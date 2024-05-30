#include <POP32.h>
#include <HUSKYLENS.h>
void (*resetFunc)(void) = 0;  // soft reset function
int Speed, ACCSpeed, SlowSpeed, TurnSpeed, LeftSpeed, RightSpeed; //ตัวแแปรความเร็วมอเตอร์
long Timer0, StartTimer0, Timer1, StartTimer1;   //ตัวแปรจับเวลา Timer0=จับเวลาการแทรคเส้น Timer1=ใช้เวลาของภาระกิจ
float Kp, Ki, Kd, Error, PreError, Integral, MaxSpeed; //ตัวแปรแกี่ยวกับ PID

HUSKYLENS huskylens;
int ID1 = 1;                                         // HuskyLens objet
HUSKYLENSResult result;                              // HuskyLens values

void setup() {
  Speed = 100;  //ความเร็วปกติ 70
  ACCSpeed = 100;  //ความเร็วตอนเร่ง 100
  SlowSpeed = 40; //ความเร็วตอนช้า 50

  Serial.begin(9600);  // Serial initialization
  Wire.begin();        // I2C initialization
  while (!huskylens.begin(Wire)) {
    Serial.print("\n Check I2C");
    delay(100);
  }
  
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch to line tracking.
  Serial.print("\n\t To start, click on the Start button");
  sw_ok_press();  //รอจนกว่าจพกดปุ่ม ok
  beep(1);        //เสียงบัซเซอร์ 0-3
  //InitialSpeed(50);  //ทดสอบวิ่งที่ 50
  ResetTimer1();  //เปิดใช้งานคู่กับ Finish()
}

void loop() {
  m1();
  //Finish();
}
