int led = 13;
int swA = 12;
int swAstate = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(swA, INPUT);
  pinMode(led, OUTPUT);
  tone(led, 3000,100);
}

void loop() {
  
  // swAstate = digitalRead(swA);
  // if (swAstate == LOW) {
  //   Serial.println("swA press");
  //   digitalWrite(led, HIGH);
  // } else {
  //   Serial.println("swA not press!!");
  //   digitalWrite(led, LOW);
  // }

  // delay(200);
}
