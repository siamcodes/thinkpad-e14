void Mission1(){
  
    if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;
    for (int i = 0; i < 8; i++) {
      getIMU();
    }
    if (discoveState) {
      rot_error = 150 - ballPosX;
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
        lastYaw = pvYaw;
        discoveState = 0;
      }
    } else {
      ali_error = ballPosY - spFli;
      ali_d = ali_error - ali_pError;
      ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
      ali_pError = ali_error;
      // select dir
      if (lastYaw < 0) {
        vecCurve = -ali_vec;
        radCurve = 15;
      } else {
        vecCurve = 270 + ali_vec;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      if (abs(pvYaw) < alignErrorGap) {
        holonomic(0, 0, 0);
        discoveState = 1;
        if ((abs(150 - ballPosX) < rotErrorGap) && (abs(spFli - ballPosY) < flingErrorGap)) {
          beep();
          unsigned long loopTimer = millis();
          while (1) {
            getIMU();
            heading(100, 90, 0);
            if (millis() - loopTimer >= 300) break;   //250
          }
          //shoot();
         // reload();
        }
      }
    }
  } else {
    int sideRot = rot_error;
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
   // reload();
  //holonomic(70,0,0);
  //delay(700);
  //holonomic(70,180,0);
  //delay(700);
  //sound(2000,200);
    
  }

}