void getTag() {                   //ค่าซ้าย 62  ค่าขวา 75 ตอนเจอคู่ 99-99
  int Gain = 25;
  if (T0 < Gain && T3 < Gain) {
    fd(SlowSpeed);                //ปรับค่าให้น้อย เวลาเจอเส้นตัดจะได้ไม่พุ่งตรงเร็วไป
    sound(1500, 150);
  } else if (T0 > Gain && T3 < Gain) {
    L90();
  } else if (T0 < Gain && T3 > Gain) {
    R90();
  } else if (T0 > Gain && T3 > Gain) {
    UTurn();
  }

}