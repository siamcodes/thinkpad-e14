void ao() {
  analogWrite(A, 0);
  analogWrite(B, 0);
  delay(10);
}

void down(int speed, int Time) {
  while (1) {
    if (digitalRead(LimitF) == 0) {
      break;
    } else {
      analogWrite(A, speed);
      analogWrite(B, 0);
      delay(Time);
    }
  }
  ao();
}

void up(int speed, int Time) {
  while (1) {
    if (digitalRead(LimitB) == 0) {
      break;
    } else {
      analogWrite(A, 0);
      analogWrite(B, speed);
      delay(Time);
    }
  }
  ao();
}