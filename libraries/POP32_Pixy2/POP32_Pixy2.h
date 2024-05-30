
#ifndef _POP32_PIXY2_H
#define _POP32_PIXY2_H

#include "Pixy2I2C.h"
#define sigNum 7 + 1  // set fisrt signature as 1
#define sigBuf 10     // size per signature

struct signature
{
  int x;
  int y;
  int width;
  int height;
};

class POP32_Pixy2 : public Pixy2I2C 
{
  private:
  
  public:
    POP32_Pixy2();
    ~POP32_Pixy2();
    bool updateBlocks();
    struct signature sigInfo[sigNum][sigBuf];
    int sigSize[sigNum];
    int getNumBlocks();
    
};

POP32_Pixy2::POP32_Pixy2() : Pixy2I2C()
{
  
}

POP32_Pixy2::~POP32_Pixy2()
{
  
}

bool POP32_Pixy2::updateBlocks()
{
  int sigCnt[sigNum] = {0}; 
  int sigIndex;
  ccc.getBlocks();
  
  if (ccc.numBlocks)
  {
    for (int i=0; i<ccc.numBlocks; i++)
    {
      if (i >= sigBuf)  break;  // limit the blocks by the size of buffer
      sigIndex = ccc.blocks[i].m_signature; 
      sigInfo[sigIndex][sigCnt[sigIndex]].x = ccc.blocks[i].m_x;
      sigInfo[sigIndex][sigCnt[sigIndex]].y = ccc.blocks[i].m_y;
      sigInfo[sigIndex][sigCnt[sigIndex]].width = ccc.blocks[i].m_width;
      sigInfo[sigIndex][sigCnt[sigIndex]].height = ccc.blocks[i].m_height;
      sigCnt[sigIndex]++;
    }
    for (int j=1; j<sigNum; j++)
    {
      sigSize[j] = sigCnt[j]; // fill buffer size
    }
    return true;
  } 
  return false;
} 

int POP32_Pixy2::getNumBlocks()
{
  //return sigSize[1] + sigSize[2] + sigSize[3] + sigSize[4] + sigSize[5] + sigSize[6] + sigSize[7] + sigSize[8];
 return ccc.numBlocks;
 //
}

#endif  // _POP32_PIXY2_H
