void KickRed() 
{
  AO();
  servo(1,160);
  delay(300); 
}
void KickYellow() 
{
  AO();
  servo(2,160);
  delay(300); 
}
void KickBlue() 
{
  AO();
  servo(3,160);
  delay(300);
}
void KickGreen() 
{
  AO();
  servo(4,160);
  delay(300);
}
void CloseServo()
{
  servo(1,70); 
  servo(2,70); 
  servo(3,70); 
  servo(4,70); 
}
void FlagUp() 
{
  MotorStop();
  servo(5,170);
}
void FlagDown() 
{
  MotorStop();
  servo(5,70);
}
