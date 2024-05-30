int led0 = 13;
int led1 = 33;
int led[5] = { 32, 33, 34, 35, 36 };
void setup() {
  for (int i = 0; i <= 4; i++) {
    pinMode(led[i], OUTPUT);
  }
}

void loop() {

  for (int x = 0; x <= 3; x++) {
    digitalWrite(led[x], HIGH);
    delay(200);
    digitalWrite(led[x], LOW);
    delay(200);
  }

  for (int x = 3; x >= 0; x--) {
    digitalWrite(led[x], HIGH);
    delay(200);
    digitalWrite(led[x], LOW);
    delay(200);
  }
  
}
