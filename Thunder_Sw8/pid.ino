int readPosition(int keepTrack, int noise) {
  unsigned char i, online = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  static int  last_value = 0;
  readCalibrate();
  for (i = 0 ; i < NUM_SENSORS; i++) {
    int values = F[i];
    if (values > keepTrack) {
      online = 1;
    }
    if (values > noise) {
      avg += (long)(values) * (i * 1000);
      sum += values;
    }
  }
  if (!online) {
    if (last_value < (NUM_SENSORS - 1) * 1000 / 2) {
      return 0;
    } else {
      return (NUM_SENSORS - 1) * 1000;
    }
  }
  last_value = avg / sum ;
  return last_value;
}

void stdPID(int baseSpeed, float  Kp, float Kd, int maxsp, int minsp) {
  int Pos = readPosition(250, 50);
  int Error = Pos - 3500;
  int PID_Value = (Kp * Error) + (Kd * (Error - LastError));
  LastError = Error;
  int LeftPower = baseSpeed - PID_Value;
  int RightPower = baseSpeed + PID_Value;
  if (LeftPower > 100) LeftPower = maxsp;
  if (LeftPower < 0) LeftPower =  minsp;
  if (RightPower > 100) RightPower = maxsp;
  if (RightPower < 0) RightPower =  minsp;
  Motor(LeftPower, RightPower);
}

void FFtimer(int baseSpeed, float Kp, float Kd, int totalTime, int maxsp, int minsp) {
  unsigned long startTime  = millis();
  unsigned long endTime = startTime + totalTime;
  while (millis() <= endTime) {
    stdPID(baseSpeed, Kp , Kd , maxsp, minsp);
  }
}

void FF(int spd, float kp , float kd, char select, int dl, int maxsp, int minsp) {
  while (1) {
    readCalibrate();
    if ((F[0] <= REF[0] && F[1] <= REF[1] && F[2] <= REF[2] && F[3] <= REF[3] && F[4] <= REF[4] && F[5] <= REF[5] && F[6] <= REF[6] &&  F[7] <= REF[7]))
    {
      break;
    }
    stdPID(spd, kp, kd , maxsp, minsp);
  }
  MotorStop();
  if (select == 's') {
    Motor(-spd, -spd); delay(dl);
    while (1)
    {
      readCalibrate();
      if (F[0] >= REF[0] && F[7] >= REF[7]) break;
      Motor(-20, -20);
    }
    MotorStop();
  } else if (select == 'p') {
    Motor(spd, spd); delay(dl);
    while (1)
    {
      readCalibrate();
      if (F[0] >= REF[0] && F[7] >= REF[7]) break;
      Motor(20, 20);
    }
    MotorStop();

  } else if (select == 'l') {
    Motor(spd, spd); delay(dl);
    SpinL();
  } else if (select == 'r') {
    Motor(spd, spd); delay(dl);
    SpinR();
  }
}

void FFL(int spd, float kp , float kd, char select, int dl, int maxsp, int minsp) {
  while (1) {
    readCalibrate();
    if (((F[0] <= REF[0]  && F[4] <= REF[4]) && (F[6] >= REF[6] &&   F[7] >= REF[7]))) 
    {
      break;
    }
    stdPID(spd, kp, kd , maxsp, minsp);
  }
  MotorStop();
}

void FFR(int spd, float kp , float kd, char select, int dl, int maxsp, int minsp) {
  while (1) {
    readCalibrate();
    if (((F[7] <= REF[7] && F[3] <= REF[3]) &&(F[0] >= REF[0] && F[4] >= REF[4] )))
    {
      break;
    }
    stdPID(spd, kp, kd , maxsp, minsp);
  }
  MotorStop();
}

void FFC(int spd, float kp , float kd) {
  while (1) {
    readCalibrate();
    if ((F[3] <= REF[3] || F[4] <= REF[4] || F[5] <= REF[5]))
    {
      break;
    }
    Motor(spd, spd); delay(50);
  }
  MotorStop();
}

void SpinL() {
  //Motor(100, 100); delay(100); MotorStop();
  Motor(-40, 40); delay(50);
  while (1) {
    readCalibrate();
    if (F[2] <= REF[2]) {
      MotorStop();
      Motor(-40, 40); delay(10);
      break;
    }
    Motor(40, -40);
  }
  MotorStop();
}

void SpinR() {
  //Motor(100, 100); delay(100); MotorStop();
  Motor(40, -40); delay(20); MotorStop();
  while (1) {
    readCalibrate();
    if (F[5] <= REF[5]) {
      MotorStop();
      Motor(40, -40); delay(10);
      break;
    }
    Motor(-40, 40);
  }
  MotorStop();
}


void SerialPos() {
  while (1) {
    int Pos = readPosition(250, 50);
    int Error_F = Pos - 3500;
    Serial.print("Pos = ");
    Serial.print(Pos);
    Serial.print("                  Error = ");
    Serial.println(Error_F);
  }
}
