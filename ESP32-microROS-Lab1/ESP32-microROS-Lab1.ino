#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if(Serial.available()>0){
    Serial.println("Recieved");
    int x = Serial.readString().toInt();
    if(x == 0){
      digitalWrite(LED_PIN,LOW);
    }else{
      digitalWrite(LED_PIN,HIGH);
    }
  }
}
