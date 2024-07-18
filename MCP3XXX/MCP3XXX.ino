#include <POP32.h>
#include <MCP3XXX.h>
MCP3008 adc;
#define numsensor 8
unsigned long F[numsensor];
#define CS_PIN  PC15  //ss 8
#define CLOCK_PIN PB11 //clk 5
#define MOSI_PIN PC14//di 7
#define MISO_PIN PA15 //do 6

void setup() {
  Serial.begin(9600);
  //adc.begin();
  // Or use custom pins to use a software SPI interface.
  // adc.begin(SS, MOSI, MISO, SCK);  //CS, DI,DO,CLK
  adc.begin(CS_PIN , MOSI_PIN, MISO_PIN, CLOCK_PIN);
}
void loop() {
  for (int i = 0; i < numsensor; i++) {
    F[i] = adc.analogRead(i);  // read Channel 0 from MCP3008 ADC (pin 1)
    Serial.print(F[i]);
    Serial.print(",\t");
  }
  Serial.println("");
  delay(200);
}