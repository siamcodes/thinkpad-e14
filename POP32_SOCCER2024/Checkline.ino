void Checkline() {  //
  while (1) {
    ConvertADC();
    mission1();  //ครองบอล
    if (C == 1) {
      holonomic(0, 0, 0);
      delay(500);
      loopTimer = millis();
      while (1) {
        getIMU();
        heading(50, 270, 0);
        if (millis() - loopTimer >= 2000) break;
      }
    }
    if (L == 1) {
      holonomic(0, 0, 0);
      delay(500);
      loopTimer = millis();

      while (1) {
        getIMU();
        heading(50, 0, 0);
        if (millis() - loopTimer >= 800) break;
      }
    }
    if (R == 1) {
      holonomic(0, 0, 0);
      delay(500);
      loopTimer = millis();

      while (1) {
        getIMU();
        heading(50, 180, 0);
        if (millis() - loopTimer >= 800) break;
      }
    }
  }
}