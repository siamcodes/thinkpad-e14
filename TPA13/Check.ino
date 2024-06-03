void Check() {           //เจอสิ่งกีดขวางให้หลบ
  if (Dist < 18) {
    ao(); delay(100);
    tr(50); delay(500);  
    fd(50); delay(400);
    Motor(20, 60); delay(800);
    while (1) {
      Motor(30, 60); delay(1);
      if (analog(1) <= 2000) {
        R90();
        break;
      }
    }
  }
}
//if (Dist < 20) {
// sr(30);delay(400);fd(20);delay(1500);
// sl(30);delay(300);fd(20);delay(1500);
// while (val_S2 > 10) { fd2(10, 30); }
// while (val_S2 < 10) { fd2(10, 30); }
// R90();
// }
//  if (Dist < 17) {
//    ao(); delay(10);
//    tr(50); delay(700);
//    ao(); delay(10);
//    fd(20); delay(200);
//    ao(); delay(10);
//    while (1) {
//      Motor(20, 50); delay(1);
//      if (analog(1)<=2000) {
//        break;
//      }
//    }
//  }
