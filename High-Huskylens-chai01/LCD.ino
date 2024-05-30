void ShowAnalog() //แสดงค่าเซ็นเซอร์
{
  long RGBColor = ReadRGB();
  glcdClear();  //เคลียร์หน้าจอ
  glcdFillScreen(GLCD_BLUE);  //กำหนดสีพื้นหลัง
  setTextColor(GLCD_RED); //กำหนดสีตัวอักษร
  setTextSize(1); //กำหนดขนาดตัวอักษร
  glcdMode(0);  //กำหนดทิศทางของจอ
  Read7Analog();
  Read2AnalogBack();
  glcd(0,0,"L3=%d",L3);
  glcd(1,0,"L2=%d",L2); 
  glcd(2,0,"L1=%d",L1);
  glcd(3,0,"C=%d",C);
  glcd(4,0,"R1=%d",R1);
  glcd(5,0,"R2=%d",R2);
  glcd(6,0,"R3=%d",R3);

  glcd(8,0,"BL=%d",BL); 
  glcd(9,0,"BR=%d",BR);

  glcd(11,0,"RGB = %l",RGBColor);

}
