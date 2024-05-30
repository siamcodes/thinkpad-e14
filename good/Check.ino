void Check() {   //เจอสิ่งกีดขวางให้หลบ
  if (Dist < 15) {
    Motor(-20,50); delay(3000);
    while (val_S2 > 10) { fd2(10, 30); }
    while (val_S2 < 10) { fd2(10, 30); }
    R90();
  }
}
