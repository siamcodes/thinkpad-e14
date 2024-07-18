#include <MCP3008.h>
#define numsensor 8
unsigned long F[numsensor];
#define CS_PIN 8
#define CLOCK_PIN 5
#define MOSI_PIN 7
#define MISO_PIN 6
MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
void setup() {
  Serial.begin(9600);
  adc.begin();
}
void loop() {
  
  for (int i = 0; i < numsensor; i++) {
    F[i] = adc.readADC(i);  // read Channel 0 from MCP3008 ADC (pin 1)
    Serial.print(F[i]);
    Serial.print(",\t");
  }
  Serial.println("");
  delay(500);
}