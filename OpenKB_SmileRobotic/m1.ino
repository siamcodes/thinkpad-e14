void m1(){
    if (digitalRead(SW1) == LOW && digitalRead(SW2) == HIGH) {
    analogWrite(BZ, 200);
    Move(200, 0, 10);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(led[i], LOW);
      delay(50);
      digitalWrite(led[i], HIGH);
      delay(50);
    }
  } else if (digitalRead(SW1) == HIGH && digitalRead(SW2) == LOW) {
    analogWrite(BZ, 100);
    Move(0, 200, 10);
    for (int i = 3; i >= 0; i--) {
      digitalWrite(led[i], LOW);
      delay(100);
      digitalWrite(led[i], HIGH);
      delay(100);
    }
  } else {
    analogWrite(BZ, 0);
    MotorStop(0);
  }
}