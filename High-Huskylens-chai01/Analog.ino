void Read7Analog()  //อ่านค่าเซ็นเซอร์หน้า 7 ตัว
{
  L3 = analog(0); 
  L2 = analog(1);
  L1 = analog(2);
  C = analog(3);
  R1 = analog(4);
  R2 = analog(5);
  R3 = analog(6);
}
void Read2AnalogBack()  //อ่านค่าเซ็นเซอร์หลัง 2 ตัว
{
  BL = analog(8);
  BR = analog(9);
}
void Convert7Analog() //แปลงค่า analog หน้า เป็น digital 0:ดำ,1:ขาว
{
  Read7Analog();
  if(L3<RefL3) L3=0; else L3=1;
  if(L2<RefL2) L2=0; else L2=1; 
  if(L1<RefL1) L1=0; else L1=1; 
  if(C<RefC) C=0; else C=1; 
  if(R1<RefR1) R1=0; else R1=1; 
  if(R2<RefR2) R2=0; else R2=1; 
  if(R3<RefR3) R3=0; else R3=1;  
}
void Convert2AnalogBack() //แปลงค่า analog หลัง เป็น digital 0:ดำ,1:ขาว
{
  Read2AnalogBack();
  if(BL<RefBL) BL=0; else BL=1; 
  if(BR<RefBR) BR=0; else BR=1; 
}
