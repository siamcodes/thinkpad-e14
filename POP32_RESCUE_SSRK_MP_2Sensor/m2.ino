void m2() {
  //int Gain = 1600;
  //Track(20, 0.09, 0.17);
  FF(50, 0.11, 0.09, 'p', 50);
  //readTag();
  ReadLine();
  if (s[0] < 500 && s[1] < 500 ) {  //เจอดำหมด
    /*
    if (T0 < Gain && T3 > Gain) {  //เจอเขียวซ้าย
      SpinL();  //เลี้ยวซ้าย
    }
    if (T0 > Gain && T3 < Gain) {  //เจอเขียวขวา
      sound(2000, 200);
      SpinR();  //เลี้ยวขวา
    }
    if (T0 < Gain && T3 < Gain) {  //เจอเขียวซ้ายและเจอเขียวขวา
      sound(3000, 300);
      Uturn();  //หมุนตัวกลับ
    }
    if (T0 > Gain && T3 > Gain) {    //ไม่เจอเขียวซ้ายและไม่เจอเขียวขวา
      fd2(40,40); delay(200);
    }
    */
    while (1) MotorStop();
  }
}