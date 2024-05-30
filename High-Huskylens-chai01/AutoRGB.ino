void Track1BlockRGB(int TracSpeed,int Time) //เดินตามช่อง 1 ช่อง 
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
      //Forward(SlowSpeed,20);//เดินหน้าก่อนหยุด
      MotorStop();
      delay(100);
      CheckColorRGB();
      switch(FloorColor)
      {
        case Blue: Backward(RobotSpeed,150); 
                    KickBlue();
                    BlueNumber++;
                    break;

        case Green: Backward(RobotSpeed,150); 
                    KickGreen();
                    GreenNumber++;
                    break;

        default: Backward(RobotSpeed,200);
                    MotorStop();
                    CheckColorRGB();
                    switch(FloorColor)
                    {
                      case Red: Backward(RobotSpeed,150); 
                                KickRed();
                                RedNumber++;
                                break;

                      case Yellow: Backward(RobotSpeed,150); 
                                KickYellow();
                                YellowNumber++;
                                break;
                    }
      }
      if((RedNumber+YellowNumber+BlueNumber+GreenNumber)>=4)  
      {
        FlagUp(); MotorStop(); while(1) {}
      }
      if((FloorColor!=White)&&(FloorColor!=Black)) Backward(RobotSpeed,500);
      TurnLeft();
    }
  }
}
