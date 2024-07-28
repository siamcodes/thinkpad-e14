#include <Wire.h>
#include <dummy.h>  // for ESP32
#define SW1 16
#define SW2 14
int BZ = 13;
int led[4] = { 17, 2, 15, 12 };
#define SDA1 4                  //sda1 in ESP32
#define SCL1 5                  //scl1 in ESP32
#define MOTOR_I2C_ADDRESS 0x50  //จากการตั้งค่า dip_switch
TwoWire I2Ctwo = TwoWire(1);    //ประกาศใช้ I2C ชุดที่ 2 (ESP32 มี I2C 2ชุด)

#define numsensor 3
int Max[numsensor] = { 826, 792, 768 };
int Min[numsensor] = { 171, 62, 60 };
int P[3] = { 32, 33, 34 };
unsigned long s[numsensor];
int error, Last_Error, Integral, leftmotor, rightmotor, PowerMotor, Position;
int last_value = 0;

void setup() {
  Serial.begin(9600);                //Set Serial Monitor
  analogReadResolution(10);          //Set ADC 10 bit 0-1023
  I2Ctwo.begin(SDA1, SCL1, 100000);  //ใช้ I2C ชุดที่ 2 ด้วยความถี่ Clock = 100Khz
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  for (int i = 0; i <= 3; i++) {
    pinMode(led[i], OUTPUT);
  }
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led[i], HIGH);
  }

  motor1(0);
  motor2(0);
  waitSW1(200);
  //view();
}

void loop() {
  m1();
}

void motor1(int tSpeed) {
  int tPWM;
  int tDir;
  if (tSpeed > 0) {
    tPWM = tSpeed;
    tDir = 1;
  } else if (tSpeed < 0) {
    tPWM = -tSpeed;
    tDir = 2;
  } else {
    tPWM = 0;
    tDir = 3;
  }
  if (tPWM > 255) tPWM = 255;

  I2Ctwo.beginTransmission(MOTOR_I2C_ADDRESS);
  I2Ctwo.write(0x85);
  I2Ctwo.write(tDir);
  I2Ctwo.write(tPWM);
  I2Ctwo.endTransmission();
}

void motor2(int tSpeed) {
  int tPWM;
  int tDir;
  if (tSpeed > 0) {
    tPWM = tSpeed;
    tDir = 1;
  } else if (tSpeed < 0) {
    tPWM = -tSpeed;
    tDir = 2;
  } else {
    tPWM = 0;
    tDir = 3;
  }
  if (tPWM > 255) tPWM = 255;

  I2Ctwo.beginTransmission(MOTOR_I2C_ADDRESS);
  I2Ctwo.write(0x86);
  I2Ctwo.write(tDir);
  I2Ctwo.write(tPWM);
  I2Ctwo.endTransmission();
}

void Move(int a, int b, int c) {
  motor1(a);
  motor2(b);
  delay(c);
}

void MotorStop(int dl) {
  motor1(0);
  motor2(0);
  delay(dl);
}

void waitSW1(int dl) {
  while (digitalRead(SW1) == HIGH) { delay(dl); }  //รอกดปุ่ม SW1
}

void waitSW2(int dl) {
  while (digitalRead(SW2) == HIGH) { delay(dl); }  //รอกดปุ่ม SW1
}

void END() {
  while (1) { MotorStop(10); }
}

void view() {
  while (1) {
    for (int i = 0; i < numsensor; i++) {
      s[i] = analogRead(P[i]);
      Serial.print(s[i]);
      Serial.print(",\t");
    }
    Serial.println("");
    delay(200);
  }
}


//วนอ่านค่าเซนเซอร์ 10 bit---------------
void Read() {
  for (int i = 0; i < numsensor; i++) {
    int x = map(analogRead(P[i]), Min[i], Max[i], 0, 1000);  // อ่านค่าเซ้นเซอร์ ถ้าไม่เกาะเส้นให้เปลี่ยน  1000, 0
    if (x > 1000) x = 1000;
    if (x < 0) x = 0;
    s[i] = x;
  }
}

// เอาค่าเซนเซอร์มาระบุตำแหน่ง-------------
int ReadLine() {
  int k;
  int on_line = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  on_line = 0;
  Read();
  avg = 0;
  sum = 0;
  for (int i = 0; i < numsensor; i++) {
    if (s[i] > 200) on_line = 1;
    if (s[i] > 50) {
      avg += s[i] * (i * 1000);
      sum += s[i];
    }
  }

  if (on_line == 0) {
    if (last_value < ((numsensor - 1) * 1000) / 2) {
      return 0;
    } else {
      return (numsensor - 1) * 1000;
    }
  }
  last_value = avg / sum;
  return last_value;
}

void stdPID(int BaseSpeed, float Kp, float Kd) {  //  แท็กเส้นดำ
  Position = ReadLine();
  error = Position - 1000;  //1000 เซนเซอร์ 3 ตัว, 3500 เซนเซอร์ 8 ตัว
  PowerMotor = (Kp * error) + (Kd * (error - Last_Error));
  Last_Error = error;
  leftmotor = BaseSpeed + PowerMotor;
  rightmotor = BaseSpeed - PowerMotor;
  if (leftmotor > 255) leftmotor = 255;
  if (leftmotor < -255) leftmotor = -255;
  if (rightmotor > 255) rightmotor = 255;
  if (rightmotor < -255) rightmotor = -255;
  Move(leftmotor, rightmotor, 0);
}

void TrackTime(int BaseSpeed, float Kp, float Kd, int Timer) {
  unsigned long Last_Time = millis();
  while ((millis() - Last_Time) <= Timer) {
    stdPID(BaseSpeed, Kp, Kd);
  }
  MotorStop(10);
}

void Track(int BaseSpeed, float Kp, float Kd) {  // อยู่ในแท็กเค้า  แท็กจนจะเจอเส้นตัด
  ReadLine();
  while (s[1] < 400) {  //ไม่เจอ
    //stdPID(BaseSpeed, Kp, Kd);
  }
  MotorStop(10);
  stdPID(BaseSpeed, Kp, Kd);
}
