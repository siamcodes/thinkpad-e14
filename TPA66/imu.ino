void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  Serial1.write(0XA5);
  Serial1.write(0X54);
  delay(100);
  Serial1.write(0XA5);
  Serial1.write(0X55);
  delay(100);
  Serial1.write(0XA5);
  Serial1.write(0X52);
  delay(100);
}

bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}

void Auto_zero() {
  zeroYaw();
  getIMU();
  int timerOut = millis();
  oled.mode(2);
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.02) {
    if (getIMU()) {
      oled.text(3, 6, "Yaw: %f  ", pvYaw);
      oled.show();
      //beep();
      if (millis() - timerOut > 5000) {
        zeroYaw();
        timerOut = millis();
      }
    }
  }
  oled.clear();
}

void updateIMU() {
  for (int i = 0; i < 16; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
}

