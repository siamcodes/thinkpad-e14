void Ball() {    //ตามเก็บบอล
  Move(30,30,100);

  while ((pixy.updateBlocks() && pixy.sigSize[1]) || (pixy.updateBlocks() && pixy.sigSize[2]) || (pixy.updateBlocks() && pixy.sigSize[3])) {
    MotorStop();
    Find();
  }
  //checkSW();  //ภายในจะเช็คสวิตช์และเดินวน
}
