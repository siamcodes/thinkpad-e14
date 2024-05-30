void MotorStop() {
  motor(1, 0);
  motor(2, 0);
  motor(3, 0);
  delay(10);
}

void CL() {
  motor(1, 30);
  motor(2, 30);
  motor(3, 30);
}

void CR() {
  motor(1, -30);
  motor(2, -30);
  motor(3, -30);
}

void Right50() {
  motor(1, -25);
  motor(2, -25);
  motor(3, 50);
}

void Left50() {
  motor(1, 25);
  motor(2, 25);
  motor(3, -50);
}

void F50() {
  motor(1, 43.30);
  motor(2, -43.30);
  motor(3, 0);
}

void F80() {
  motor(1, 69.28);
  motor(2, -69.28);
  motor(3, 0);
}

void F100() {
  motor(1, 86.60);
  motor(2, -86.60);
  motor(3, 0);
}

void B50() {
  motor(1, -43.30);
  motor(2, 43.30);
  motor(3, 0);
}

void FL() {
  motor(1, 68.30);
  motor(2, -18.30);
  motor(3, -50);
}

void BL() {
  motor(1, -18.30);
  motor(2, 68.30);
  motor(3, -50);
}

void FR() {
  motor(1, 18.30);
  motor(2, -68.30);
  motor(3, 50);
}
 
void BR(){
  motor(1, -68.30);
  motor(2, 18.30);
  motor(3, 50);
}