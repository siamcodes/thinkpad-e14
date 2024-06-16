void Play() {  //
  while (1) {
    ReadLine();
    mission1();  //ครองบอล
    /*
    if (s[1] < 500) {  //กลาง
      holonomic(0, 0, 0);
      delay(300);
      loopTimer = millis();
      while (1) {
        getIMU();
        heading(50, 270, 0);
        if (millis() - loopTimer >= 2000) break;
      }
    }
    else if (s[0] < 500) {  //ซ้าย
      holonomic(0, 0, 0);
      delay(300);
      loopTimer = millis();
      while (1) {
        getIMU();
        heading(50, 0, 0);
        if (millis() - loopTimer >= 800) break;
      }
    }
    else if (s[2] < 800) {   //ขวา
      holonomic(0, 0, 0);
      delay(300);
      loopTimer = millis();
      while (1) {
        getIMU();
        heading(50, 180, 0);
        if (millis() - loopTimer >= 800) break;
      }
    }
    */
  }
}