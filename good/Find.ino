void Find() {
  while(1) {
    if (pixy.updateBlocks() && pixy.sigSize[1]) {
      int x = pixy.sigInfo[1][0].x;
      int y = pixy.sigInfo[1][0].y;  //
      head_error = head_sp - x;
      dis_error = dis_sp - y;  //
      hI = hI + head_error;
      dI = dI + dis_error;    //
      hI = constrain(hI, -MAX_Spd, MAX_Spd);
      dI = constrain(dI, -MAX_Spd, MAX_Spd);  //
      hD = head_error - hPrevError;
      dD = dis_error - dPrevError;  //
      head_spd = (head_Kp * head_error) + (hI * head_Ki) + (hD * head_Kd);
      dis_spd = (dis_Kp * dis_error) + (dI * dis_Ki) + (dD * dis_Kd);  //
      //int leftSpeed = constrain(-head_spd, -MAX_Spd, MAX_Spd);
      //int rightSpeed = constrain(head_spd, -MAX_Spd, MAX_Spd);
      //int leftSpeed = constrain(dis_spd, -MAX_Spd, MAX_Spd); //
      //int rightSpeed = constrain(dis_spd, -MAX_Spd, MAX_Spd); //

      int leftSpeed = constrain(dis_spd - head_spd, -MAX_Spd, MAX_Spd);
      int rightSpeed = constrain(dis_spd + head_spd, -MAX_Spd, MAX_Spd);

      motor(1, leftSpeed);
      motor(2, rightSpeed);
      hPrevError = head_error;
      dPrevError = dis_error;  //

      if ((abs(head_error) < h_gap) && (abs(dis_error) < d_gap)) {
        motor(1, 0);
        motor(2, 0);
        beep(); delay(1000);
      }
    } else {
      sr(10);
      delay(500);
      fd(20);
      delay(500);
    }
  }
}



// if (knob(100) > 50) {
//   Tarck();
//   ao();
//   Find_ball();
// } else {
//   Find_ball();
// }
