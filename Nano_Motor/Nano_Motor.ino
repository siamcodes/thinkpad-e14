int AIN1=2;
int AIN2=3;
int BIN1=4;
int BIN2=5;
long Speed, TurnSpeed;

void setup() {
  Serial.begin(9600);
  Speed = 255;
  TurnSpeed = 100;
  Forward(Speed, 2000);
  MotorStop();
}

void loop() {
  Forward(Speed, 2000);

}
