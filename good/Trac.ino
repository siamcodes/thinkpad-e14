void Trac() {
  while (1) {
    if (val_S1 < 10 && val_S2 < 10) {
      getTag();
      T0 = 0;
      T3 = 0;
    }else {
      //Check();
      if (val_S0 < 100) T0++;
      if (val_S3 < 100) T3++;
      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
      motor(1, SP_M1);
      motor(2, SP_M2);
    }
  }
}
