// TurnSpeed ที่ความเร็ว 40-50 ok แล้ว

void R90() {
  fd(Speed);
  sound(1500, 140);
  while (val_S2 < 10) { sr(TurnSpeed); }
  while (val_S2 > 10) { sr(TurnSpeed); }
  while (val_S1 > 20) { sr(TurnSpeed); }
}

void L90() {
  fd(Speed);
  sound(1500, 140);
  while (val_S1 < 10) { sl(TurnSpeed); }
  while (val_S1 > 10) { sl(TurnSpeed); }
  while (val_S2 > 20) { sl(TurnSpeed); }
}

void UTurn() {           //ยูเทิร์นช้าไปนิด แต่โอเคสุดแล้ว
  bk(Speed);
  sound(1500, 450);
  while (val_S2 < 10) { sr(TurnSpeed); }
  while (val_S2 > 10) { sr(TurnSpeed); }
  while (val_S1 > 20) { sr(TurnSpeed); }
}

void Motor(int leftsp, int rightsp) {
  motor(1, leftsp);
  motor(2, rightsp);
}
