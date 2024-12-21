void run(int line, int box, int a, int Sensor, int direc) {
  int speed = 90;
  float kp = 0.022;  //0.015
  float kd = 0.22;  //0.18

  int slowspeed = 40;
  float kp_slow = 0.016;
  float kd_slow = 0.13;
  
  int speed1line = 55;
  float kp_1 = 0.01;
  float kd_1 = 0.1;

  if (a == LR) {
    if (box == 1 and line == 1) {
      // tt(speed1line, kp_1, kd_1, Boxtime[1], Sensor);
      tc(speed1line, kp_1, kd_1, 1, Sensor);

    } else if (box > 1 and line == 1) {
      tt(speed, kp, kd, Boxtime[2], Sensor);
      tc(slowspeed, kp_slow, kd_slow, 1, Sensor);
    } else if (line > 1) {
      tc(speed, kp, kd, line - 1, Sensor);
      tt(speed, kp, kd, Boxtime[box], Sensor);
      tc(slowspeed, kp_slow, kd_slow, 1, Sensor);
    }
  } else if (a == L) {
    if (box == 1 and line == 1) {
      tt(speed1line, kp_1, kd_1, Boxtime[1], Sensor);
      tcl(speed1line, kp_1, kd_1, 1, Sensor);
    } else if (box > 1 and line == 1) {
      tt(speed, kp, kd, Boxtime[2], Sensor);
      tcl(slowspeed, kp_slow, kd_slow, 1, Sensor);
    } else if (line > 1) {
      tcl(speed, kp, kd, line - 1, Sensor);
      tt(speed, kp, kd, Boxtime[box], Sensor);
      tcl(slowspeed, kp_slow, kd_slow, 1, Sensor);
    }
  } else if (a == R) {
    if (box == 1 and line == 1) {
      tt(speed1line, kp_1, kd_1, Boxtime[1], Sensor);
      tcr(speed1line, kp_1, kd_1, 1, Sensor);
    } else if (box > 1 and line == 1) {
      tt(speed, kp, kd, Boxtime[2], Sensor);
      tcr(slowspeed, kp_slow, kd_slow, 1, Sensor);
    } else if (line > 1) {
      tcr(speed, kp, kd, line - 1, Sensor);
      tt(speed, kp, kd, Boxtime[box], Sensor);
      tcr(slowspeed, kp_slow, kd_slow, 1, Sensor);
    }
  }
  if (Sensor == FRONTSENSOR) {
    if (direc == L) {
      Move(slowspeed,slowspeed,0);
      l();
    } else if (direc == R) {
      Move(slowspeed,slowspeed,30);
      r();
    }
  } else if (Sensor == BACKSENSOR) {
    if (direc == L) {
      Move(-slowspeed, -slowspeed, 0);
      l();
    } else if (direc == R) {
      Move(-slowspeed, -slowspeed, 0);
      r();
    }
  }
}
