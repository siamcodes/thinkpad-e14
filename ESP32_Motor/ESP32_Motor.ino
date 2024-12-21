int PWMA = 32, DIR1A = 33, DIR2A = 25, LA = 34, LB = 35;
int PWMB = 13, DIR1B = 12, DIR2B = 14, RA = 26, RB = 27;
int led = 2;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(DIR2B, OUTPUT);
}

void loop() {
  int val = map(analogRead(39), 0, 4095, 255, 0);
  Serial.println(val);
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR1B, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWMA, val);  
  analogWrite(PWMB, val);
  digitalWrite(led,HIGH);
  delay(1000);

  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWMA, val);  
  analogWrite(PWMB, val);
  digitalWrite(led,LOW);
  delay(1000);
  
}
