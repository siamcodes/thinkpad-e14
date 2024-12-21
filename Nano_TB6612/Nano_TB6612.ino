#include <Servo.h>
Servo myservo[3];

#define dir1A 2  //
#define dir2A 3  //
#define pwmA 5
#define dir1B 4  //
#define dir2B 7  //
#define pwmB 6

void setup() {
  Serial.begin(9600);
  pinMode(dir1A, OUTPUT);
  pinMode(dir2A, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(dir1B, OUTPUT);
  pinMode(dir2B, OUTPUT);
  pinMode(pwmB, OUTPUT);

  while (analogRead(A6) > 500);
  delay(200);
  tone(13,440,1000);
  delay(100);
  tone(13,3000,1000);
  delay(100);
}

void loop() {
  // servo(1,0);
  // servo(2,0);
  // servo(3,0);
  // delay(500);
  // servo(1,90);
  // servo(2,90);
  // servo(3,90);
  // delay(500);
  // servo(1,180);
  // servo(2,180);
  // servo(3,180);
  // delay(500);
  // Forward();
  // delay(1000);
  //  Backward();
  //  delay(1000); 
  //  Left();
  //  delay(1000);
    Right();
    delay(000);
   
}

void servo(int ch, int degree) {
  if (ch == 1) {
    if (degree == -1) myservo[0].detach();
    else {
      if (!myservo[0].attached()) myservo[0].attach(9);
      myservo[0].write(degree);
    }
  }
  else if (ch == 2) {
    if (degree == -1) myservo[1].detach();
    else {
      if (!myservo[1].attached()) myservo[1].attach(10);
      myservo[1].write(degree);
    }
  }
  else if (ch == 3) {
    if (degree == -1) myservo[2].detach();
    else {
      if (!myservo[2].attached()) myservo[2].attach(11);
      myservo[2].write(degree);
    }
  }
}

void Forward() {
  digitalWrite(dir1A, HIGH);
  digitalWrite(dir2A, LOW);
  analogWrite(pwmA, 150);
  digitalWrite(dir1B, HIGH);
  digitalWrite(dir2B, LOW);
  analogWrite(pwmB, 150);
}

void Backward() {
  digitalWrite(dir1A, LOW);
  digitalWrite(dir2A, HIGH);
  analogWrite(pwmA, 200);
  digitalWrite(dir1B, LOW);
  digitalWrite(dir2B, HIGH);
  analogWrite(pwmB, 200);
}

void Left() {
  digitalWrite(dir1A, LOW);
  digitalWrite(dir2A, HIGH);
  analogWrite(pwmA, 200);
  digitalWrite(dir1B, HIGH);
  digitalWrite(dir2B, LOW);
  analogWrite(pwmB, 200);
}

void Right() {
  digitalWrite(dir1A, HIGH);
  digitalWrite(dir2A, LOW);
  analogWrite(pwmA, 200);
  digitalWrite(dir1B, LOW);
  digitalWrite(dir2B, HIGH);
  analogWrite(pwmB, 200);
}