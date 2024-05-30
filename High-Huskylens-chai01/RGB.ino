/////////// RGB Function ////////////////////////////
void SetupTCS34725()  //ทำการ Setup RGB และตรวจสอบ RGB
{
   delay(100);
   Serial.begin(115200);
   glcd(0,0,"Color Sensor Test!");

   if (tcs.begin()) {
    glcd(1,0,"Found sensor!");
    delay(500);
  } else {
    glcd(1,0,"No TCS34725 found!");
    //while (1); // halt!
    delay(1000);
  }
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
  tcs.setGain(TCS34725_GAIN_4X);
}
uint16_t ReadRGB()  //อ่านค่า RGB
{
  uint16_t clear, red, green, blue;

  delay(60);  // takes 50ms to read 
  
    tcs.getRawData(&red, &green, &blue, &clear);
  
  /*Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println();*/

  // Figure out some basic hex code for visualization
 
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;

  uint16_t _color = color16((int)r, (int)g, (int)b);
  return(_color);
}
void ShowRGB()  //แสดงค่า RGB
{
  long RGBColor = ReadRGB();
  glcdClear();
  glcd(0,0,"RGB=%l",RGBColor); 
}
void ShowRGBColor()
{
  glcdClear();
  glcd(0,0,"Color=%d",CheckColorRGB()); 
}
int CheckColorRGB()   //คำนวณค่าสีต่างๆ น้ำเงิน,เขียว,ดำ,ขาว,เหลือง,แดง
{
    long RGBColor = ReadRGB();
    //glcdClear();
    if(RGBColor<(RefBlue+RefGreen)/2)
    {
      FloorColor = Blue; //น้ำเงิน
      //glcd(0,0,"CanColor=Blue");
    }
    else if(RGBColor<(RefGreen+RefBlack)/2) 
    {
      FloorColor = Green; //เขียว
      //glcd(0,0,"CanColor=Green");
    }
    else if(RGBColor<(RefBlack+RefWhite)/2) 
    {
      FloorColor = Black; //ดำ
      //glcd(0,0,"CanColor=Black");
    }
    else if(RGBColor<(RefWhite+RefYellow)/2) 
    {
      FloorColor = White; //ขาว
      //glcd(0,0,"CanColor=White");
    }
    else if(RGBColor<(RefYellow+RefRed)/2) 
    {
      FloorColor = Yellow; //เหลือง
      //glcd(0,0,"CanColor=Yellow");
    }
    else 
    {
      FloorColor = Red; //แดง
      //glcd(0,0,"CanColor=Red");
    }
    return(FloorColor);
}
/////////////////////////////////////////////
