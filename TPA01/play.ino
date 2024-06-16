void play() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;

    int timeOut = millis();
    while (!getIMU()) {
      if (millis() - timeOut > 3000) break;
    }

    if (discoveState) {
      rot_error = spRot - ballPosX;
      rot_d = rot_d + rot_error;
      rot_d = constrain(rot_d, -100, 100);
      rot_d = rot_error - rot_pError;
      rot_pError = rot_error;
      rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
      rot_w = constrain(rot_w, -100, 100);

      fli_error = spFli - ballPosY;
      fli_i = fli_i + fli_error;
      fli_i = constrain(fli_i, -100, 100);
      fli_d = fli_error - fli_pError;
      fli_pError = fli_error;
      fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
      fli_spd = constrain(fli_spd, -100, 100);

      holonomic(fli_spd, 90, rot_w);

      if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
        wheel(0, 0, 0);
        discoveState = 0;
      }
    } else {
      ali_error = ballPosY - spFli;
      ali_d = ali_error - ali_pError;
      ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
      ali_pError = ali_error;

      int timeOut = millis();
      while (!getIMU()) {  //ปรับปรุงค่า IMU
        if (millis() - timeOut > 3000) break;
      }
      // select dir
      if (pvYaw < 0) {
        vecCurve = -ali_vec;
        radCurve = 15;
      } else {
        vecCurve = 180 + ali_vec;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      if (abs(pvYaw) < alignErrorGap) {
        //holonomic(0, 0, 0);
        //Goal();   //วิ่งหาประตู เข้าไปยิง
        unsigned long loopTimer = millis();
        while (1) {  //เดินหน้าตรงความเร็ว 100%
          getIMU();
          //Goal();   //วิ่งหาประตู เข้าไปยิง
          heading(100, 90, 0);                         //เดินหน้าเข้าไปยิง
          if (millis() - loopTimer >= 500) { break; }  //250
        }

        shoot();  //ยิง
        beep(1);
        delay(200);
        reload();  //เก็บก้านยิง
        discoveState = 1;
        beep();
      }
    }
  } else {
    int sideRot = 150 - ballPosX;
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
  }
}