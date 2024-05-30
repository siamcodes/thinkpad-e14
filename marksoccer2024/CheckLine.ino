void CheckLine() {
  while (1) {
    ConvertADC();
    mission1();  //ทำภารกิจ
    if (C == 1) {
      holonomic(0, 0, 0);  // หยุด
      delay(500);
      Backward();
      break;
    } 
    if (L == 1 || R == 1) {
      while (1) {
        getIMU();
        heading(0, 0, 0);
        if (millis()  - loopTimer >= 2000) break;
      }
    }
  }
}



void Backward() {
  holonomic(50, 270, 0);
  delay(1000);
}
