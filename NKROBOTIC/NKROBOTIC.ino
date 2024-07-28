# define Trig 5
# define LED_R 17
# define LED_G  16
# define Echo 35

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ISUS!");
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
}
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2 ;
}
void loop() {
  long duration, distance;

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = microsecondsToCentimeters (duration);
  Serial.print("distance : ");
  Serial.println(distance);
  delay(1000);
  if (distance < 10 ) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
 Serial.println("LED ON");

  }
  else {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
     Serial.println("LED OFF");

  }
}
