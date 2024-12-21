/* Simple Arduino LED blink example sketch for built-in 
   RGB 5050 LED on the AI Thinker NodeMCU-ESP-S3-12K-Kit
    
    This example is in the Public Domain
    Cosismo IoT | Github: cosismo
*/

#define led_r_pin 5
#define led_g_pin 6
#define led_b_pin 7

void setup() {
  Serial.begin(115200);
  pinMode(led_r_pin, OUTPUT);
  pinMode(led_g_pin, OUTPUT);
  pinMode(led_b_pin, OUTPUT);
}

void loop() {
  for (uint8_t i = 1; i < 8; i++) {
    /* Get the rgb bits shifting the counter variable
         to the right and then masking with AND 0x1 */
    bool r = (i  >> 2) & 1;  
    bool g = (i  >> 1) & 1;
    bool b = (i  >> 0) & 1; //shift 0, I know. Aesthetics and symmetry ;)
    Serial.printf("i= %d | rgb bits = r:%d, g:%d, b:%d,\n", i, r, g, b);

    digitalWrite(led_r_pin, r);
    digitalWrite(led_g_pin, g);
    digitalWrite(led_b_pin, b);
    delay(1000);
    digitalWrite(led_r_pin, LOW);
    digitalWrite(led_g_pin, LOW);
    digitalWrite(led_b_pin, LOW);
    delay(1000);

  }
}
