#define LED_PIN 13  // เปลี่ยนตามขาที่เชื่อม LED

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(LED_PIN, HIGH);  // เปิด LED
      Serial.println("LED ON");
    } else if (command == '0') {
      digitalWrite(LED_PIN, LOW);   // ปิด LED
      Serial.println("LED OFF");
    }
  }
}