#include <Wire.h>
#include <dummy.h>  // for ESP32
#define SW1 16
#define SW2 14
#define SDA1 4                  //sda1 in ESP32
#define SCL1 5                  //scl1 in ESP32
#define MOTOR_I2C_ADDRESS 0x50  //จากการตั้งค่า dip_switch
TwoWire I2Ctwo = TwoWire(1);    //ประกาศใช้ I2C ชุดที่ 2 (ESP32 มี I2C 2ชุด)

void setup() {
  I2Ctwo.begin(SDA1, SCL1, 100000);  //ใช้ I2C ชุดที่ 2 ด้วยความถี่ Clock = 100Khz
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  motor1(0);
  motor2(0);
}

void loop() {
  if (digitalRead(SW1) == LOW && digitalRead(SW2) == HIGH) {
    motor1(255);
    motor2(127);
  } else if (digitalRead(SW1) == HIGH && digitalRead(SW2) == LOW) {
    motor1(-127);
    motor2(255);
  } else {
    motor1(0);
    motor2(0);
  }
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
