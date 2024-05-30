void MotorStop()  //มอเตอร์หยุดทั้ง 4 ล้อ
{
  AO();
  delay(100);
}
void TuneMotor(int MotorSpeed)  //ปรับจูนมอเตอร์
{
  if(MotorSpeed<=60)
  {
    LeftSpeed = MotorSpeed-0; //เอียงขวา
    RightSpeed = MotorSpeed-0; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-0; //เอียงซ้าย
  }
  else  //ความเร็วมากกว่า 60
  {
    LeftSpeed = MotorSpeed-0; //เอียงขวา
    RightSpeed = MotorSpeed-3; //เอียงซ้าย
    LeftSpeedBack = MotorSpeed-0; //เอียงขวา
    RightSpeedBack = MotorSpeed-8; //เอียงซ้าย
  } 
}
void Forward(int MotorSpeed,int Time) //เดินหน้า
{
  TuneMotor(MotorSpeed);
  FD2(LeftSpeed,RightSpeed);
  delay(Time);
}
void Backward(int MotorSpeed,int Time) //ถอยหลัง
{
  TuneMotor(MotorSpeed);
  BK2(LeftSpeedBack,RightSpeedBack);
  delay(Time);
}
void TurnLeft()   //เลี้ยวซ้าย
{
  MotorStop();
  SL(TurnSpeed);
  delay(175);
  MotorStop();
}
void TurnRight()   //เลี้ยวขวา
{
  MotorStop();
  SR(TurnSpeed);
  delay(175);
  MotorStop();
}
void UTurn()   //กลับตัวด้านขวา
{
  MotorStop();
  SR(TurnSpeed);
  delay(285);
  MotorStop();
}
