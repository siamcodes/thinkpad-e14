void CalError() //คำนวณ error
{
  Convert7Analog();
  if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==0)) Error=-1;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==0)) Error=-2;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==0)&&(R3==1)) Error=-3;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==0)&&(R3==1)) Error=-4;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==0)&&(R2==1)&&(R3==1)) Error=-5;
  else if((L3==1)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=0;
  else if((L3==0)&&(L2==1)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=1;
  else if((L3==0)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=2;
  else if((L3==1)&&(L2==0)&&(L1==1)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=3;
  else if((L3==1)&&(L2==0)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=4;
  else if((L3==1)&&(L2==1)&&(L1==0)&&(C==1)&&(R1==1)&&(R2==1)&&(R3==1)) Error=5;
  else if(C==0) Error=100;
}

void TrackPID(int MotorSpeed) //เคลื่อนที่ตามช่องแบบ PID
{
  int Output,LeftOutput,RightOutput,MaxSpeed=100;
  
  TuneMotor(MotorSpeed);
  Output = (Kp*Error)+(Ki*Integral)+Kd*(Error-PreError);
  LeftOutput = LeftSpeed+Output;
  RightOutput = RightSpeed-Output;
  if(LeftOutput>MaxSpeed) LeftOutput = MaxSpeed;
  if(LeftOutput<-MaxSpeed) LeftOutput = -MaxSpeed; 
  if(RightOutput>MaxSpeed) RightOutput = MaxSpeed;
  if(RightOutput<-MaxSpeed) RightOutput = -MaxSpeed; 
  motor(1,LeftOutput);
  motor(2,LeftOutput);
  motor(3,RightOutput);
  motor(4,RightOutput);
  PreError = Error;
  Integral += Error;
}
