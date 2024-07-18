void Checkline(){
    while (1) {
    //ConvertADC();
    mission1();
    if (C == 1) {
      holonomic(0, 0, 0);
      delay(1000);
      loopTimer = millis();
      while (1) {
        getIMU();
        heading(50, 270, 0);
        if (millis() - loopTimer >= 2000) break;
      }
    }
    if (L == 1) {
      holonomic(0, 0, 0);
      delay(1000);
      holonomic(50, 0, 0);
      delay(1000);
      break;
    }
    if (R == 1) {
      holonomic(0, 0, 0);
      delay(1000);
      holonomic(50, 180, 0);
      delay(1000);
      break;
    }
  }
}