void tn(float speed, float kp, float kd) {  // tracknormal
  error = ReadLine() - 3500;
  powermotor = (kp * error) + (kd * (error - lasterror));
  lasterror = error;
  leftmotor = speed + powermotor;
  rightmotor = speed - powermotor;
  if (leftmotor > 100) leftmotor = 100;
  if (leftmotor < -100) leftmotor = -100;
  if (rightmotor > 100) rightmotor = 100;
  if (rightmotor < -100) rightmotor = -100;
  motor(leftmotor, rightmotor);
}

void t(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[1] < 200 and F[6] < 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[1] > 250 and F[6] > 250) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}
void ty(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[2] < 400 and F[5] < 400) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[2] > 500 and F[5] > 500) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}

void trr(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[7] < 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[4] > 200 and F[7] > 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}

void tll(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[0] < 200 ) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[0] > 200 and F[3] > 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}


void tr(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[6] < 200 and F[7] < 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[6] > 200 and F[7] > 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}

void tl(float speed, float kp, float kd) {
  while (true) {
    ReadLine();
    if (F[0] < 200 and F[1] < 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
  while (true) {
    ReadLine();
    if (F[0] > 200 and F[1] > 200) {
      break;
    } else {
      tn(speed, kp, kd);
    }
  }
}

void l() {
  Move(40, 40, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[0] < 200 and F[7] < 200) {
      break;
    }
  }
  Move(-20, 60, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[0] < 200) {
      break;
    }
  }
  ReadLine();
  while (true) {
    ReadLine();
    if (F[0] > 200) {
      break;
    }
  }
}

void r() {
  Move(40, 40, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[0] < 200 and F[7] < 200) {
      break;
    }
  }
  Move(60, -20, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[7] < 200) {
      break;
    }
  }
  ReadLine();
  while (true) {
    ReadLine();
    if (F[7] > 200) {
      break;
    }
  }
}

void l45() {
  Move(-20, 60, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[3] < 200) {
      break;
    }
  }
  ReadLine();
  while (true) {
    ReadLine();
    if (F[3] > 200) {
      break;
    }
  }
}

void r45() {
  Move(60, -20, 0);
  ReadLine();
  while (true) {
    ReadLine();
    if (F[4] < 200) {
      break;
    }
  }
  ReadLine();
  while (true) {
    ReadLine();
    if (F[4] > 200) {
      break;
    }
  }
}

void tt(float speed, float kp, float kd, long Timer) {
  unsigned long lasttime = millis();
  while (millis() - lasttime <= Timer) {
    tn(speed, kp, kd);}
}
  