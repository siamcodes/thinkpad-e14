
#include <POP32.h> 
#include <POP32_Pixy2.h>

POP32_Pixy2 pixy;

void setup() 
{
  Serial.begin(115200);
  pixy.init();
  
  while(!Serial);
  Serial.println("Started!");
}

void loop() 
{
  if (pixy.updateBlocks())
  {
    Serial.print("\nDetected: "); Serial.println(pixy.getNumBlocks());
    Serial.println("x\ty\twidth\theight");
    for (int i=1; i<=7; i++)  // for loop signature
    {
      if(pixy.sigSize[i]) // signature not empty
      {
        Serial.print("-> Signature: ");  Serial.println(i);
        for (int j=0; j<pixy.sigSize[i]; j++) // for loop index of signature
        {
          Serial.print(pixy.sigInfo[i][j].x);       Serial.print("\t");
          Serial.print(pixy.sigInfo[i][j].y);       Serial.print("\t");
          Serial.print(pixy.sigInfo[i][j].width);   Serial.print("\t");
          Serial.println(pixy.sigInfo[i][j].height);  
        }
      }
    }
  }
  else
  {
    Serial.println("Not detected");  
  }
}
