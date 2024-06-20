int AIN1=5;
int AIN2=6;
int BIN1=9;
int BIN2=10;
long Speed, TurnSpeed;

void setup() {
  Serial.begin(9600);
  Speed = 200;
  TurnSpeed = 100;
  //Forward(Speed, 2000);
  //MotorStop();
}

void loop() {
  Forward(Speed);
  delay(1000);
  MotorStop();
  Backward(Speed);
  delay(1000);
  MotorStop();
}
