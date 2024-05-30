int TracBalance() //เดินตามช่องเจอแยกแล้วปรับให้ตรงแล้วหยุด
{
  int Status=0,TimeBalance=400;
    CalError();
    if(C==0)  //เจอดำตรงกลาง
    {
      delay(5);
      CalError();
      if(C==0) Status = 2; //เจอดำตรงกลาง 
      //else ForwardSpeedTime(Speed,1000);
    }
    else if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      delay(5);
      CalError();
      if(C==0) Status = 2;  //เจอดำตรงกลาง 
      else if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
      {
        Status = 2;
        AO(); 
        motor(1,-SlowSpeed); motor(2,-SlowSpeed);
        motor(3,SlowSpeed); motor(4,SlowSpeed);
        StartTimer0();
        while(R1==1) 
        {
          Convert7Analog(); 
          if(ReadTimer0()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
          {
            MotorStop();
            R1=0;
            Status = 4;
            motor(1,SlowSpeed); motor(2,SlowSpeed);
            motor(3,-SlowSpeed); motor(4,-SlowSpeed);
            delay(TimeBalance/2);
            MotorStop();
          }
        }
        delay(50);
      }
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      delay(5);
      CalError();
      if(C==0) Status = 2;  //เจอดำตรงกลาง 
      else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
      {
        Status = 2;
        AO(); 
        motor(1,SlowSpeed); motor(2,SlowSpeed);
        motor(3,-SlowSpeed); motor(4,-SlowSpeed);
        StartTimer0(); 
        while(L1==1) 
        {
          Convert7Analog(); 
          if(ReadTimer0()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
          {
            MotorStop();
            L1=0;
            Status = 4;
            motor(1,-SlowSpeed); motor(2,-SlowSpeed);
            motor(3,SlowSpeed); motor(4,SlowSpeed);
            delay(TimeBalance/2);
            MotorStop();
          }
        }
        delay(50); 
      } 
    }
    else TrackPID(RobotSpeed);
    return(Status);
}
int BackwardBalance(int Time)  //ถอยหลังปรับสมดุลในเวลาที่กำหนด
{
  int Status=0,TimeBalance=400;
  StartTimer0();
  Backward(SlowSpeed,1);
  
  while(Status==0)
  {
    Convert2AnalogBack();
    if((BL==0)&&(BR==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      motor(1,SlowSpeed); motor(2,SlowSpeed);
      motor(3,-SlowSpeed); motor(4,-SlowSpeed);
      StartTimer1();
      while(BR==1) 
      {
        Convert2AnalogBack(); 
        if(ReadTimer1()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
        {
          MotorStop();
          BR=0;
          Status = 4;
          motor(1,-SlowSpeed); motor(2,-SlowSpeed);
          motor(3,SlowSpeed); motor(4,SlowSpeed);
          delay(TimeBalance/2);
          MotorStop();
        }
      }
      delay(30);
    }
    else if((BL==1)&&(BR==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      motor(1,-SlowSpeed); motor(2,-SlowSpeed);
      motor(3,SlowSpeed/2); motor(4,SlowSpeed/2);
      StartTimer1();
      while(BL==1) 
      {
        Convert2AnalogBack(); 
        if(ReadTimer1()>TimeBalance) //อีกข้างไม่เจอเส้นดำ
        {
          MotorStop();
          BL=0;
          Status = 4;
          motor(1,SlowSpeed); motor(2,SlowSpeed);
          motor(3,-SlowSpeed); motor(4,-SlowSpeed);
          delay(TimeBalance/2);
          MotorStop();
        }
      }
      delay(30);
    }
    else if((BL==0)&&(BR==0)) Status=3; //เจอดำทั้งสองข้าง
    if(ReadTimer0()>Time) Status=4;  //หมดเวลาถอยหลัง
  }
  MotorStop();
  return(Status);
}
