void InitialSpeed(int MotorSpeed) { //กำหนดความเร็วให้หุ่นยนต์ หลายๆ สเต็ป
  Error = 0 ; //ให้ Error เป็น 0
  PreError = 0;
  Integral = 0;
  Ki = 0;
  MaxSpeed = MotorSpeed;  //ให้ MaxSpeed เท่ากับค่า MotorSpeed ที่กำหนด

  if (MotorSpeed <= 60)
  {
    Kp = 5.50;            //ทำใให้หุ่นยนต์ไม่หลุดเส้น ทางโค้งอาจหลุดเส้น ก็ให้มาเพิ่ม
    Kd = 08.0;            //ค่าที่ให้หุ่นยนต์ไม่สาย เยอะยิ่งดีไม่ส่าย  เยอะมากๆ อาจให้สบัดแรงเกิน ถ้าน้อยจะเลื้อยเป็นงู ก็เพิ่ม
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
  else if (MotorSpeed <= 80)
  {
    Kp = 2.00;            //ทำใให้หุ่นยนต์ไม่หลุดเส้น ทางโค้งอาจหลุดเส้น ก็ให้มาเพิ่ม
    Kd = 10.00;            //ค่าที่ให้หุ่นยนต์ไม่สาย เยอะยิ่งดีไม่ส่าย  เยอะมากๆ อาจให้สบัดแรงเกิน ถ้าน้อยจะเลื้อยเป็นงู ก็เพิ่ม   
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
  else if (MotorSpeed <= 100)
  {
    Kp = 4.00;                //ทำใให้หุ่นยนต์ไม่หลุดเส้น
    Kd = 25.00;                //ค่าที่ให้หุ่นยนต์ไม่สาย เยอะยิ่งดีไม่ส่าย  เยอะมากๆ อาจให้สบัดแรงเกิน ถ้าน้อยจะเลื้อยเป็นงู ก็เพิ่ม   
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }

}