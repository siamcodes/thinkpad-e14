int AIN1 = 25, AIN2 = 26, LA = 36, LB = 39;
int BIN1 = 32, BIN2 = 33, RA = 34, RB = 35;
int led = 2;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  int val = map(analogRead(4), 0, 4095, 0, 255);
  Serial.println(val);
  analogWrite(AIN1, val);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, val);
  analogWrite(BIN2, 0);
  digitalWrite(led, HIGH);
  delay(1000);

  analogWrite(AIN1, 0);
  analogWrite(AIN2, val);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, val);
  digitalWrite(led, LOW);
  delay(1000);
}
