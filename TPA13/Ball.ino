void Ball() {    //ตามเก็บบอล
  fd(30);

  while ((pixy.updateBlocks() && pixy.sigSize[1]) || (pixy.updateBlocks() && pixy.sigSize[2]) || (pixy.updateBlocks() && pixy.sigSize[3])) {
    ao(); delay(1);
    Find();
  }

  if (in(4) == 0 && in(5) == 0) { //4|5
    bk(50); delay(400);
    sr(50); delay(600);
  }
  else if (in(4) == 0) {
    bk(50); delay(400);
    sl(40);  delay(500);
  }
  else if (in(5) == 0) {
    bk(50); delay(400);
    sr(40);  delay(500);
  }

}


void Ball2() {    //ตรวจหาพื้นที่อพยพ
  fd(30); delay(100);

  while (pixy.updateBlocks() && pixy.sigSize[3]) {
    Find_Ball();

    if (in(4) == 0 && in(5) == 0) {
      bk(50); delay(400);
      ao(); delay(200);
      sr(50); delay(800);
      ao(); delay(200);
      while (1) {
        bk(50); delay(1);
        if (in(6) == 0 && in(7) == 0) {
          sv2();
          break;
        }
      }
    }
  }


  if (in(4) == 0 && in(5) == 0) { //4|5
    bk(50); delay(400);
    sr(50); delay(600);
  }
  else if (in(4) == 0) {
    bk(50); delay(400);
    sl(50);  delay(500);
  }
  else if (in(5) == 0) {
    bk(50); delay(400);
    sr(50);  delay(500);
  }
}



//  else if(in(6)==0 && in(7)==0) {  //6|7
//   bk(50); delay(500);
//   sl(50); delay(400);
//  }
