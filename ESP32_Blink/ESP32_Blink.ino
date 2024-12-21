int led=2;
int a=0;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
   a= analogRead(39);
   Serial.println(a);
   digitalWrite(led,HIGH);
   delay(1000);
   digitalWrite(led,LOW);
   delay(1000);
   
}
