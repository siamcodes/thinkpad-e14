void getTag() {                   //ค่าซ้าย 62  ค่าขวา 75 ตอนเจอคู่ 99-99
  int Gain = 25;
  if (T0 < Gain && T3 < Gain) {
    //fd(SlowSpeed);                //ปรับค่าให้น้อย เวลาเจอเส้นตัดจะได้ไม่พุ่งตรงเร็วไป
    TrackNormal(50, 0.3, 0.5);
    sound(1500, 150);
  } else if (T0 > Gain && T3 < Gain) {
    //L90();
    SpinL();
  } else if (T0 < Gain && T3 > Gain) {
    SpinR();//R90();

  } else if (T0 > Gain && T3 > Gain) {
    Uturn();
  }

}

void readTag(){
  T0 = abs(analog(4));
  T3 = abs(analog(5));
  //oled.text(0,0,"T0= %d",T0);
  //oled.text(1,0,"T3= %d",T3);
  //oled.show();
}