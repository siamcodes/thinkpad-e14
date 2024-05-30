void Forward(int MotorSpeed, int Time){  //เดินหน้าหน่วงเวลา
  InitialSpeed(MotorSpeed);  //กำหนดความเร็วมอเตอร์
  fd2(LeftSpeed, RightSpeed);  //เดินไปข้างหน้า
  delay(Time);
}