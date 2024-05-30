void stdPID(int BaseSpeed, float Kp, float Kd, int maxsp, int minsp) {
  huskylens.request(ID1);
  result = huskylens.read();
  err = map(result.xCenter, 0, 320, -160, 160);   //250
  //Serial.print(String()+("\n err=")+err);       //getting and maping err
  //Position = err;
  //err = Position - 100;  //1500
  p = Kp * err;
  i = Ki * (i + err);
  d = Kd * (err - lastErr);
  pid = p + i + d;
  lastErr = err;
  leftmotor = BaseSpeed + pid;
  rightmotor = BaseSpeed - pid;
  if (leftmotor > 100) leftmotor = maxsp;
  if (leftmotor < -100) leftmotor = -100;  //-10
  //if (leftmotor < 0) leftmotor = minsp;
  if (rightmotor > 100) rightmotor = maxsp;
  if (rightmotor < -100) rightmotor = -100;  //-100
  //if (rightmotor < 0) rightmotor = minsp;
  Move(leftmotor, rightmotor,  0);
  err = 0;
}

void FFtimer(int baseSpeed, float Kp, float Kd, int totalTime, int maxsp, int minsp) {
  unsigned long startTime = millis();
  unsigned long endTime = startTime + totalTime;
  while (millis() <= endTime) {
    stdPID(baseSpeed, Kp, Kd, maxsp, minsp);
  }
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

void stop(int a) {
  Move(0, 0, a);
}
