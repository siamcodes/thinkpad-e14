void getTag() {
    int Gainl = 80;
    int Gainr = 80;
    if (T0 < Gainl && T3 < Gainr) {
      fd(30);                //ปรับค่าให้น้อย เวลาเจอเส้นตัดจะได้ไม่พุ่งตรงเร็วไป
      sound(1500, 150);
    } else if (T0 > Gainl && T3 < Gainr) {
      L90();
    } else if (T0 < Gainl && T3 > Gainr) {
      R90();
    } else if (T0 > Gainl && T3 > Gainr) {
      UTurn();
    }

}

// ใช้ตรวจสอบค่าเส้น Gain
//  Tarck();
//  ao();
//  oled.clear();
//  while(!SW_OK()){
//    oled.text(0, 0, "T0=%d  ", T0);
//    oled.text(2, 0, "T3=%d  ", T3);
//    oled.show();
//  }
//  beep();
//  T0=0;
//  T3=0;
