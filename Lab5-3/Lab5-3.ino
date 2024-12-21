int led[]={17,2,15,12};  //bt, wifi, ntp, iot
int adc = 36;

void setup() {
  Serial.begin(9600);
  tone(13,3000);
  delay(100);
  tone(13,1000);
  delay(100);
  noTone(13);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  
}

void loop() {
   int ldr = analogRead(adc);
   int val = map(ldr, 0, 1023, 0, 5);
   Serial.println(val);

   if(val==0){
      digitalWrite(led[0], HIGH);
      digitalWrite(led[1], HIGH);
      digitalWrite(led[2], HIGH);
      digitalWrite(led[3], HIGH);
   }else if(val==1){
      digitalWrite(led[0], LOW);
      digitalWrite(led[1], HIGH);
      digitalWrite(led[2], HIGH);
      digitalWrite(led[3], HIGH);
   }else if(val==2){
      digitalWrite(led[0], LOW);
      digitalWrite(led[1], LOW);
      digitalWrite(led[2], HIGH);
      digitalWrite(led[3], HIGH);
   }else if(val==3){
      digitalWrite(led[0], LOW);
      digitalWrite(led[1], LOW);
      digitalWrite(led[2], LOW);
      digitalWrite(led[3], HIGH);
   }else if(val==4){
      digitalWrite(led[0], LOW);
      digitalWrite(led[1], LOW);
      digitalWrite(led[2], LOW);
      digitalWrite(led[3], LOW);
   }
   delay(10);
}
