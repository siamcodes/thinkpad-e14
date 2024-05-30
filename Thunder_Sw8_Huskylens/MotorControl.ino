void Motor(int leftsp, int rightsp) {
  motor(1, leftsp);
  motor(2, rightsp);
}

void MotorStop() {
//  Motor(0, 0); delay(10);
ao(); delay(10);
}
