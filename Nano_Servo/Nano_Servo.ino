#include <Servo.h>
Servo servo1;  //ประกาศตัวแปรแทน Servo
Servo servo2;  //ประกาศตัวแปรแทน Servo

int btn = 12;  // the number of the input pin
int led = 13;  // the number of the output pin

int state = HIGH;    // the current state of the output pin
int reading;         // the current reading from the input pin
int previous = LOW;  // the previous reading from the input pin

//int degree = 90;  //องศาการยก 90
int pos = 0;
int z = 0;
int i = 0;

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long time = 0;          // the last time the output pin was toggled
unsigned long debounce = 400UL;  // the debounce time, increase if the output flickers

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  servo1.attach(5);  // กำหนดขา 5 ควบคุม Servo
  servo2.attach(6);  // กำหนดขา 6 ควบคุม Servo
  //servo1.write(z1);  // สั่งให้ Servo หมุนไปองศาที่ z1
  //servo2.write(z2);  // สั่งให้ Servo หมุนไปองศาที่ z2
  delay(2000);       // หน่วงเวลา 2000ms
}

void loop() {
  reading = digitalRead(btn);
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time

  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == LOW) {
      down();
      state = HIGH;
    } else {
      up();
      state = LOW;
    }
    time = millis();
  }
  digitalWrite(led, state);  //แสดงผล led
  previous = reading;
}

