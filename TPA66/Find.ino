void Find() {
  while (1) {
    if (pixy.updateBlocks() && pixy.sigSize[1]) {
      int x = pixy.sigInfo[1][0].x;
      head_error = head_sp - x;
      hI = hI + head_error;
      hI = constrain(hI, -MAX_Spd, MAX_Spd);
      hD = head_error - hPrevError;
      head_spd = (head_Kp * head_error) + (hI * head_Ki) + (hD * head_Kd) ;

      int y = pixy.sigInfo[1][0].y;
      dis_error = dis_sp - y;
      dI = dI + dis_error;
      dI = constrain(dI, -MAX_Spd, MAX_Spd);
      dD = dis_error - dPrevError;
      dis_spd = (dis_Kp * dis_error) + (dI * dis_Ki) + (dD * dis_Kd);

      const int h_gap = 30;
      const int d_gap = 15;
      if ((abs(head_error) < h_gap) && (abs(dis_error) < d_gap)) {
        motor(1, 0);
        motor(2, 0);
        beep();
        SV();
        //count += 1;
      } else {
        int leftSpeed = constrain(dis_spd - head_spd, -MAX_Spd, MAX_Spd);
        int rightSpeed = constrain(dis_spd + head_spd, -MAX_Spd, MAX_Spd);
        motor(1, leftSpeed);
        motor(2, rightSpeed);
      }
      hPrevError = head_error;
      dPrevError = dis_error;
    } else if (pixy.updateBlocks() && pixy.sigSize[2]) {
      int x = pixy.sigInfo[2][0].x;
      head_error = head_sp - x;
      hI = hI + head_error;
      hI = constrain(hI, -MAX_Spd, MAX_Spd);
      hD = head_error - hPrevError;
      head_spd = (head_Kp * head_error) + (hI * head_Ki) + (hD * head_Kd) ;

      int y = pixy.sigInfo[2][0].y;
      dis_error = dis_sp - y;
      dI = dI + dis_error;
      dI = constrain(dI, -MAX_Spd, MAX_Spd);
      dD = dis_error - dPrevError;
      dis_spd = (dis_Kp * dis_error) + (dI * dis_Ki) + (dD * dis_Kd);

      const int h_gap = 30;
      const int d_gap = 15;
      if ((abs(head_error) < h_gap) && (abs(dis_error) < d_gap)) {
        motor(1, 0);
        motor(2, 0);
        beep();
        SV();
        //count += 1;
      } else {
        int leftSpeed = constrain(dis_spd - head_spd, -MAX_Spd, MAX_Spd);
        int rightSpeed = constrain(dis_spd + head_spd, -MAX_Spd, MAX_Spd);
        motor(1, leftSpeed);
        motor(2, rightSpeed);
      }

      hPrevError = head_error;
      dPrevError = dis_error;
    } else if (pixy.updateBlocks() && pixy.sigSize[3]) {
      int x = pixy.sigInfo[3][0].x;
      head_error = head_sp - x;
      hI = hI + head_error;
      hI = constrain(hI, -MAX_Spd, MAX_Spd);
      hD = head_error - hPrevError;
      head_spd = (head_Kp * head_error) + (hI * head_Ki) + (hD * head_Kd) ;

      int y = pixy.sigInfo[3][0].y;
      dis_error = dis_sp - y;
      dI = dI + dis_error;
      dI = constrain(dI, -MAX_Spd, MAX_Spd);
      dD = dis_error - dPrevError;
      dis_spd = (dis_Kp * dis_error) + (dI * dis_Ki) + (dD * dis_Kd);

      const int h_gap = 30;
      const int d_gap = 15;
      if ((abs(head_error) < h_gap) && (abs(dis_error) < d_gap)) {
        motor(1, 0);
        motor(2, 0);
        beep();
        SV();
        count = 3;
        if (count == 3) { //เมื่อครบ 3 ลูก
          break;
        }
      } else {
        int leftSpeed = constrain(dis_spd - head_spd, -MAX_Spd, MAX_Spd);
        int rightSpeed = constrain(dis_spd + head_spd, -MAX_Spd, MAX_Spd);
        motor(1, leftSpeed);
        motor(2, rightSpeed);
      }

      hPrevError = head_error;
      dPrevError = dis_error;
    } 
    else {
      checkSW();
    }
  }
  popB();
}

//void Find_Ball() {    //เฉพาะกิจ
//  while ((pixy.updateBlocks() && pixy.sigSize[1]) || (pixy.updateBlocks() && pixy.sigSize[2]) || (pixy.updateBlocks() && pixy.sigSize[3])) {
//    ao(); delay(1);
//    Find();
//  }
//}
// if (knob(100) > 50) {
//   Tarck();
//   ao();
//   Find();
// } else {
//   Find();
// }
