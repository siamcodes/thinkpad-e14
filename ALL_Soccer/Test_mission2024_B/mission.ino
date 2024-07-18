void mission1(){
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;
    
    if (discoveState) {  //วิ่งปรับหุ่นยนต์ให้ใกล้ลูกบอลมากที่สุด discoveState=1
      rot_error = sp_rot - ballPosX;
      rot_i = rot_i + rot_error;
      rot_i = constrain(rot_i, -100, 100);
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
      updateIMU(); //อัพเดทค่า IMU ก่อนทุกครั้ง
      if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
        holonomic(0, 0, 0);
        discoveState = 0;  
        lastYaw = pvYaw;
      }

    } else {  //จะทำงานเมื่อเจอลูกบอลแต่ทิศไม่ตรงที่จะยิ่ง
      ali_error = ballPosY - spFli;
      ali_d = ali_error - ali_pError;
      ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
      ali_pError = ali_error;
      
      // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
      if (lastYaw < 0) {
        vecCurve = -ali_vec;
        radCurve = 15;
      } else {
        vecCurve = 180 + ali_vec;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      updateIMU(); //อัพเดทค่า IMU ก่อนทุกครั้ง
      if (abs(pvYaw) < alignErrorGap) {  //เมื่อทิศอยู่ในค่าที่รับได้
        rot_error = sp_rot - ballPosX;       //คำนวนหาค่า Error ว่าลูกบอลอยู่ตรงกลางหรือไม่
        discoveState = 1;
        if (abs(rot_error) < rotErrorGap) {  //ถ้าลูกบอลอยู่ตรงกลางให้ทำการยิง
          unsigned long loopTimer = millis();
          while (1) {  //เดินหน้าตรงความเร็ว 100%
            getIMU();
            heading(0,0, 0);
            if (millis() - loopTimer >= 1500) break;  //250
          }
          //shoot();   //ยิง
          sound(2000,200);
         // heading(0,0,0);
          //reload();  //เก็บก้านยิง
          discoveState = 1;
        }
      }
    }
  } else {                            //หมุนตัวหาลูกบอล
    int sideRot = sp_rot - ballPosX;  //คำนวนทิศการหมุนหาลูกบอลเมื่อเจอล่าสุด
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
    discoveState = 1;  //เตรียมพร้อมไปหาลูกบอลเมื่อเจอบอลอีกครั้ง
  }

}
