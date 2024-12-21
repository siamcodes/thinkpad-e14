//โปรแกรมวนรอบไฟวิ่ง 4 ดวง โดยใช้ while
int led[]={17,2,15,12};  //bt, wifi, ntp, iot
void setup() {
    for(int i=0; i<=3; i++){
      pinMode(led[i], OUTPUT);
    }
}

void loop() {
   int i=0;
   while(i <= 3){
     digitalWrite(led[i], LOW);
     delay(100);
     digitalWrite(led[i], HIGH);
     delay(100);
   }
}
