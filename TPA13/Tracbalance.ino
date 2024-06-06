void Tracbl() {
  fd(30);
  delay(100);

  if (in(4) == 0 && in(5) == 0) {
    bk(50);
    delay(400);
    ao();
    delay(200);
    sr(100);
    delay(800);
    ao();
    delay(200);
    // while (1) {
    //   bk(50); delay(1);
    //   if (in(6) == 0 && in(7) == 0) {
    //     sv2();
    //     break;
  }
}

void Pong() {
  fd(30);

  while ((pixy.updateBlocks() && pixy.sigSize[1]) || (pixy.updateBlocks() && pixy.sigSize[2]) || (pixy.updateBlocks() && pixy.sigSize[3])) {
    ao();
    delay(1);
    Find();
  }

  if (in(4) == 0 && in(5) == 0) {
    bk(50);
    delay(400);
    ao();
    delay(200);
    sr(50);
    delay(800);
    ao();
    delay(200);
    while (1) {
      bk(50);
      delay(1);
      if (in(6) == 0 && in(7) == 0) {
        sv2();
        break;
      }
    }
  } 
  
  else if (in(4) == 0) {
    bk(40);
    delay(100);
    ao(); delay(100);
    //tr(50);
    //delay(200);
    while (1) {
      fd2(80,30);
      if (in(4) == 0 && in(5) == 0){ ao(); break; } 
    }
    ao();
  } 
  
   else if (in(5) == 0) {
     bk(40);
     delay(100);
     ao(); delay(100);
    // tl(50);
    // delay(200);
    while (1) {
      fd2(30,80);  
      if (in(4) == 0 && in(5) == 0){ ao(); break; } 
    }
    ao();
  }
}