//void Tarck() {
//  while (1) {
//    if (val_S1 < 10 && val_S2 < 10) {
//      getTag();
//      T0 = 0;
//      T3 = 0;
//    }
//    else {
//      Check();
//      if (val_S0 < 100) T0++;
//      if (val_S3 < 100) T3++;
//      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
//      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
//      motor(1, SP_M1);
//      motor(2, SP_M2);
//    }
//  }
//}

void Tarck() {
  EndTime = millis() + TotalTime;
  while (millis() <= EndTime) {
    if (val_S1 < 10 && val_S2 < 10) {
      getTag();
      T0 = 0;
      T3 = 0;
      EndTime = millis() + TotalTime;
    } else {
      if (val_S0 < 100) T0++;
      if (val_S3 < 100) T3++;
      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
      motor(1, SP_M1);
      motor(2, SP_M2);
    }
  }
}

void TarckW() {
  fd(30);

  while ((pixy.updateBlocks() && pixy.sigSize[1]) || (pixy.updateBlocks() && pixy.sigSize[2]) || (pixy.updateBlocks() && pixy.sigSize[3])) {
    ao();
    delay(1);
    Find();
  }

  if (in(4) == 0 && in(5) == 0) {
    bk(50); delay(400);
    ao();   delay(200);
    sr(50); delay(800);
    ao();   delay(200);
    while (1) {
      bk(50); delay(1);
      if (in(6) == 0 && in(7) == 0) {
        sv2();
        break;
      }
    }
  } 
  
  else if (in(4) == 0) {
    bk(40);  delay(100);
    ao();    delay(100);
    while (1) {
      fd2(80,30);
      if (in(4) == 0 && in(5) == 0){ ao(); break; } 
    }
    ao();
  } 
  
   else if (in(5) == 0) {
     bk(40); delay(100);
     ao();   delay(100);
    while (1) {
      fd2(30,80);  
      if (in(4) == 0 && in(5) == 0){ ao(); break; } 
    }
    ao();
  }
}
