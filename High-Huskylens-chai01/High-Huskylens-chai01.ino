#include <ATX2.h> //เพิ่มไลบราลี
#include "Adafruit_TCS34725.h"
/**************************RGB*****************/
// our RGB -> eye-recognized gamma color
  byte gammatable[256];

static uint16_t color16(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t _color;
  _color = (uint16_t)(r & 0xF8) << 8;
  _color |= (uint16_t)(g & 0xFC) << 3;
  _color |= (uint16_t)(b & 0xF8) >> 3;
  return _color;
}
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
 
  int RedNumber=0,YellowNumber=0,BlueNumber=0,GreenNumber=0;
  int FloorColor,ColorCheck=0;
  
  long RefBlue = 21295;
  long RefGreen = 25496;
  long RefBlack = 30362;
  long RefWhite = 33382;
  long RefYellow = 37508;
  long RefRed = 55588;
  #define Blue 0
  #define Green 1
  #define Black 2
  #define White 3
  #define Yellow 4
  #define Red 5
/*************** กล้อง *******************/
  #define XrefCenter  160  
  #define YrefCenter  120//80
  #define RefHeight   60
  #define Refwidth  20
  int xCenter,yCenter,width,height;
  int xOrigin,yOrigin,xTarget,yTarget;
/***************************************/

int L3,L2,L1,C,R1,R2,R3;  //ประกาศตัวแปรเซ็นเซอร์หน้า 7 ตัว
int BL,BR;  //ประกาศตัวแปรเซ็นเซอร์หลัง 2 ตัว
int RefL3=594,RefL2=705,RefL1=622,RefC=445,RefR1=708,RefR2=596,RefR3=586;
int RefBL=469,RefBR=555;
int RobotSpeed=45,SlowSpeed=40,AccSpeed=100,TurnSpeed=100;
int LeftSpeed,RightSpeed,LeftSpeedBack,RightSpeedBack;
int Kp=15,Ki=0,Kd=30,Error,PreError,Integral;
long BaseTimer0,Timer0,BaseTimer1,Timer1,BaseTimer2,Timer2;
void setup() {
  // put your setup code here, to run once:
  XIO();  //ประกาศ IO
  //SetupTCS34725();  //ทำการ Setup RGB และตรวจสอบ RGB  
  InitialHuskyslens(); 
  Color_Recognition_mode();                                                                                                                                                                                                                       
  beep(0);  //เสียงบี๊บ
  KickRed();
  KickYellow();
  KickBlue();
  KickGreen();
  FlagUp();
  ShowAnalog(); //แสดงค่าเซ็นเซอร์
  CloseServo();
  FlagDown();
  sw_ok_press();  //รอจนกว่าจะมีการกดปุ่ม sw ok
  beep(0);
  delay(100);
  //Forward(RobotSpeed,2000);   //เดินหน้า
  //Backward(RobotSpeed,2000);  //ถอยหลัง
  //TurnLeft();                 //เลี้ยวซ้าย
  //TurnRight();                //เลี้ยวขวา
  //UTurn();                    //กลับตัว
  //BackwardBalance(400);          //ถอยหลังปรับจูนเซ็นเซอร์หลัง
  //Track1BlockRGB(RobotSpeed,600); //เดินหน้า 1 ช่อง ถ้าเจอเส้นปรับจูนให้ตรง
  TrackColorHuskylens();
  MotorStop();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Track1BlockRGB(RobotSpeed,600);
}
