void CheckFloorColor()  //เช็คสีพื้น
{
  FloorColor = 0;
  if((Huskylens_ReadOneID(1)==1)&&(width>Refwidth)&&(yCenter<YrefCenter)) //เจอสีแดง
  {
    FloorColor = 1;
  }
  else if((Huskylens_ReadOneID(2)==2)&&(width>Refwidth)&&(yCenter<YrefCenter)) //เจอสีเหลือง
  {
    FloorColor = 2;
  }
  else if((Huskylens_ReadOneID(3)==3)&&(width>Refwidth)&&(yCenter<YrefCenter)) //เจอสีน้ำเงิน
  {
    FloorColor = 3;
  }
  else if((Huskylens_ReadOneID(4)==4)&&(width>Refwidth)&&(yCenter<YrefCenter)) //เจอเขียว
  {
    FloorColor = 4;
  }
}
void TrackColorHuskylens()  //เดินตามช่อง 1 ช่องพร้อมเช็คสีพื้น
{
  if((Huskylens_ReadOneID(7)==7)&&(width>Refwidth)) //เจอสีตะเกียบ
  {
    Forward(RobotSpeed,1300);
    TurnRight();
  }
  CheckFloorColor(); 
  if(FloorColor>0)  //เจอสีพื้น 4 สี
  {
     Forward(RobotSpeed,500); 
     MotorStop();
     switch(FloorColor)
     {
        case 1: KickRed(); RedNumber++; break;
        case 2: KickYellow(); YellowNumber++; break;
        case 3: KickBlue(); BlueNumber++; break;
        case 4: KickGreen(); GreenNumber++; break;
     }
     if((RedNumber+YellowNumber+BlueNumber+GreenNumber)>=4)  
     {
       FlagUp(); MotorStop(); while(1) {}
     }
     Backward(RobotSpeed,500);
     TurnLeft();
  }
  else  //ไม่เจอสีพื้นทั้ง 4 สี
  {
    Track1BlockHuskylens(RobotSpeed,600);
  }
}

void Track1BlockHuskylens(int TracSpeed,int Time) //เดินตามช่อง 1 ช่อง 
{
  int Status=0;
  
  StartTimer0();
  Forward(TracSpeed,1);
  while(Status==0)
  {
    Status=TracBalance();
    if((ReadTimer0()>Time)&&(Status==0))    //เดินตามช่องไปจนหมดเวลาครบ 1 ช่อง
    {
      Status = 1;
      TurnRight();
    }
    if(Status>=2) //เจอเส้นดำ
    {
      MotorStop();
      Backward(RobotSpeed,200);
      TurnLeft();      
    }
  }
}
