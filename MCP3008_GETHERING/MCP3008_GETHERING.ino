#include <Adafruit_MCP3008.h>
Adafruit_MCP3008 adc;  //
#define FRONTSENSOR 999
#define BACKSENSOR 998
#define numsensor 8
int MaxF[numsensor] = { 877, 873, 843, 857, 862, 879, 873, 630 };  //MexF-100
int MinF[numsensor] = { 372, 404, 305, 256, 276, 230, 266, 219 };  //MinF+100
int MaxB[numsensor] = { 872, 867, 793, 795, 870, 725, 807, 746 };  //MexB-100
int MinB[numsensor] = { 302, 321, 283, 245, 308, 218, 248, 237 };  //MinB-100
unsigned long F[numsensor];
unsigned long B[numsensor];

void setup() {
  Serial.begin(9600);
}

void loop() {
  view(BACKSENSOR);
}

void view(int Sensor) {
  while (true) {
    if (Sensor == FRONTSENSOR) {
      adc.begin(A0, A2, A1, 8); 
      adc.begin(A0, A2, A1, A3);
    } else if (Sensor == BACKSENSOR) {
      adc.begin(A0, A2, A1, A3);
      adc.begin(A0, A2, A1, 8);
    }
    for (int i = 0; i < 8; i++) {
      Serial.print(adc.readADC(i));
      Serial.print(",\t");
    }
    Serial.println("");
  }
}

void Read(int Sensor) {
  int x = 0;
  if (Sensor == FRONTSENSOR) {
    adc.begin(A0, A2, A1, 8);
    adc.begin(A0, A2, A1, A3);
    for (int i = 0; i < numsensor; i++) {
      x = map(adc.readADC(i), MinF[i], MaxF[i], 800, 0);
      if (x >= 800) x = 800;
      if (x <= 0) x = 0;
      F[i] = x;
    }
  } else if (Sensor == BACKSENSOR) {
    adc.begin(A0, A2, A1, A3);
    adc.begin(A0, A2, A1, 8);
    for (int i = 0; i < numsensor; i++) {
      x = map(adc.readADC(i), MinB[i], MaxB[i], 800, 0);
      if (x >= 800) x = 800;
      if (x <= 0) x = 0;
      B[i] = x;
    }
  }
}