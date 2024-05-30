
void setup() {
  pinMode(PC13, OUTPUT); // LED connect to pin PC13
}
void loop() {
  /*
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                 // wait for 100mS
  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                 // wait for 100mS
  */
  for(int i=0;i<255;i++){
    analogWrite(PA8, i);
    analogWrite(PB3, i);
    analogWrite(PB4, i);
    analogWrite(PA15, i);
    analogWrite(PA0, i);
    analogWrite(PB10, i);
    delay(10);
  }
  
  delay(2000);

  for(int i=255;i>0;i--){
    analogWrite(PA8, i);
    analogWrite(PB3, i);
    analogWrite(PB4, i);
    analogWrite(PA15, i);
    analogWrite(PA0, i);
    analogWrite(PB10, i);
    delay(10);
  }

   delay(2000);
  
}