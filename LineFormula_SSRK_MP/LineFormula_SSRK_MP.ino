#include <Adafruit_MCP3008.h>
Adafruit_MCP3008 adc;  //

#define dir1A 2  //
#define dir2A 3  //
#define pwmA 5   //
#define dir1B 4  //
#define dir2B 7  //
#define pwmB 6   //
#define numsensor 8
int last_value = 0;
int Max[numsensor] = { 970,	971,	876,	929,	907,	832,	968,	671};
int Min[numsensor] = { 256,	267,	151,	149,	175,	130,	168,	112 };
unsigned long F[numsensor];
float leftmotor, rightmotor, powermotor, error, lasterror;
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
  //adc.begin(A0, A1, A2, A3);
  //adc.begin(A0, A2, A1, 8);
  //adc.begin(A0, A2, A1, A3);

  //view();
  // viewRead();
  // viewReadLine();
  // t(50,0.007,0.1);  //YR kd 0.1
  // t(80,0.01,0.18);   //_/-/
  // t(45,0.009,0.078);  //U
  // SENSOR 0.8 c.m.

  // t(50,0.007,0.1);
  // t(45,0.012,0.05);   //s_cycle
  // tt(50,0.007,0.07,550);

  // t(50,0.007,0.07);
  // t(70,0.015,0.15);   //m_cycle
  // tt(50,0.007,0.07,550);

  // t(50,0.009,0.09,250);
  // tt(90,0.018,0.2,550);  //B_cycle
  // t(50,0.007,0.07);

  // t(50,0.007,0.1);  //YR kd 0.1
  // l();
  //while (digitalRead(8) == 1);
  //delay(500);
  //mission();
  //motor(0, 0);
}

void loop() {
  //Serial.println(digitalRead(8));
  tn(20,0.02,0.00);
}
void Move(int spl, int spr, int Timer) {
  motor(spl, spr);
  delay(Timer);
}
void motor(int motorl, int motorr) {
  motorl = (motorl * 255) / 100;
  motorr = (motorr * 255) / 100;
  if (motorl == 0) {
    digitalWrite(dir1A, HIGH);
    digitalWrite(dir2A, HIGH);
    analogWrite(pwmA, 0);
  } else if (motorl > 0) {
    digitalWrite(dir1A, HIGH);
    digitalWrite(dir2A, LOW);
    analogWrite(pwmA, motorl);
  } else if (motorl < 0) {
    digitalWrite(dir1A, LOW);
    digitalWrite(dir2A, HIGH);
    analogWrite(pwmA, -motorl);
  }
  if (motorr == 0) {
    digitalWrite(dir1B, HIGH);
    digitalWrite(dir2B, HIGH);
    analogWrite(pwmB, 0);
  } else if (motorr > 0) {
    digitalWrite(dir1B, HIGH);
    digitalWrite(dir2B, LOW);
    analogWrite(pwmB, motorr);
  } else if (motorr < 0) {
    digitalWrite(dir1B, LOW);
    digitalWrite(dir2B, HIGH);
    analogWrite(pwmB, -motorr);
  }
}

void view() {
  while (true) {
    for (int i = 0; i < 8; i++) {
      Serial.print(adc.readADC(i));
      Serial.print(",\t");
    }
    Serial.println("");
  }
}

void Read() {
  int x = 0;
  for (int i = 0; i < numsensor; i++) {
    adc.begin(A0, A2, A1, 8);
    adc.begin(A0, A2, A1, A3);
    x = map(adc.readADC(i), Min[i], Max[i], 1000, 0);
    if (x >= 1000) x = 1000;
    if (x <= 0) x = 0;
    F[i] = x;
  }
}

void viewRead() {
  while (true) {
    Read();
    for (int i = 0; i < 8; i++) {
      Serial.print(F[i]);
      Serial.print(",\t");
    }
    Serial.println("");
  }
}

int ReadLine() {
  unsigned long avg = 0;
  unsigned long sum = 0;
  int on_line = 0;
  Read();
  for (int i = 0; i < numsensor; i++) {
    if (F[i] > 200) on_line = 1;
    if (F[i] > 50) {
      avg = avg + (F[i] * (i * 1000));
      sum = sum + F[i];
    }
  }
  if (on_line == 0) {
    if (last_value > 3500) return 7000;
    else return 0;
  } else {
    last_value = avg / sum;
  }
  return last_value;
}

void viewReadLine() {
  while (true) {
    for (int i = 0; i < 8; i++) {
      Serial.print(F[i]);
      Serial.print(",\t");
    }
    Serial.println(ReadLine());
  }
}
