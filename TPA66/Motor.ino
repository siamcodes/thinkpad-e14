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

void Move(int leftsp, int rightsp, int dl) {
  motor(1, leftsp);
  motor(2, rightsp);
  delay(dl);
}

void MotorStop(){
  motor(1, 0);
  motor(2, 0);
  delay(10);
}

void SV() {
  servo(1, 40); delay(1000);  //จับบอล
  Move(40,20,50);  //เขย่ารถ
  Move(20,40,50);
  MotorStop();
  servo(1, 80); delay(100);
  servo(1, 100); delay(100);
  servo(1, 160); delay(2000);    //เทเข้า
}

void sv2() {
  servo(2, 180); delay(100);  //ปิดทางออก
  servo(2, 100); delay(2000);  //เปิดทางออก
  ao(); delay(5000);
}

void TrackNormal(int BaseSpeed, float Kp, float Kd) {
  Position = pvYaw;
  error = Position;  //1500 เซนเซอร์ 4 ตัว, 3000 เซนเซอร์ 7 ตัว
  PowerMotor = (Kp * error) + (Kd * (error - Last_Error));
  Last_Error = error;
  leftmotor = BaseSpeed + PowerMotor;
  rightmotor = BaseSpeed - PowerMotor;
  if (leftmotor > 100) leftmotor = 100;
  if (leftmotor < -100) leftmotor = -100;
  if (rightmotor > 100) rightmotor = 100;
  if (rightmotor < -100) rightmotor = -100;
  Move(leftmotor, rightmotor, 0);
}

void TrackTime(int BaseSpeed, float Kp, float Kd, int Timer) {
  unsigned long Last_Time = millis();
  while ((millis() - Last_Time) <= Timer) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}

void Track(int BaseSpeed, float Kp, float Kd) {  // อยู่ในแท็กเค้า  แท็กจนจะเจอเส้นตัด
  //ReadLine();
  getIMU();
  while (in(4) != 0 && in(5) != 0) {
    TrackNormal(BaseSpeed, Kp, Kd);
  }
}


