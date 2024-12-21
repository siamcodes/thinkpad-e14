int PWMA = 25, DIR1A = 26, DIR2A = 27, LA = 14, LB = 12;
int PWMB = 4, DIR1B = 16, DIR2B = 17, RA = 34, RB = 35;
//int led = 2;
void setup() {
  Serial.begin(9600);
  //pinMode(led, OUTPUT);
  pinMode(36, INPUT);
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR2A, OUTPUT);
  pinMode(DIR1B, OUTPUT);
  pinMode(DIR2B, OUTPUT);
  //pinMode(LA, INPUT);
  //pinMode(LB, INPUT);
  //pinMode(RA, INPUT_PULLUP);
  //pinMode(RB, INPUT_PULLUP);
  //-------------------
  sw_start();
  backward(150, 1000);
  stop(100);
}

void loop() {
  int val = map(analogRead(39), 0, 4095, 255, 0);
  Serial.println(val);
}


void forward(int spd, int dl) {
  digitalWrite(DIR1A, HIGH);
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2B, HIGH);
  analogWrite(PWMA, spd);
  analogWrite(PWMB, spd);
  delay(dl);
}

void backward(int spd, int dl) {
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR2A, HIGH);
  digitalWrite(DIR1B, HIGH);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWMA, spd);
  analogWrite(PWMB, spd);
  delay(dl);
}

void stop(int dl) {
  digitalWrite(DIR1A, LOW);
  digitalWrite(DIR2A, LOW);
  digitalWrite(DIR1B, LOW);
  digitalWrite(DIR2B, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(dl);
}

void sw_start() {
  while (1) {
    if (digitalRead(36) == LOW) break;
  }
}