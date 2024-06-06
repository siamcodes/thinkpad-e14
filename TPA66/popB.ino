void popB() {
  //if (SW_A()) {  //เมื่อกดปุ่ม SW_A
  Auto_zero();
  // }
  while (1) {
    getIMU();
    TrackNormal(20, 0.50, 0.05);
    if (in(4) == 0 && in(5) == 0) {
      ao();
      bk(50);
      delay(400);
      ao();
      delay(200);
      sr(50);
      delay(700);
      ao();
      delay(200);
      while (1) {
        bk(50);
        delay(1);
        if (in(6) == 0 && in(7) == 0) {
          sv2();
          break;
        }
      }
    }
  }

  while (1) MotorStop();
}