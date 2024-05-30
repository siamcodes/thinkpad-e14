void down() {
  i = 1;
  z = 90;
  for (pos = 90; pos >= 0; pos -= i) {
    servo1.write(pos);  // สั่งให้ Servo หมุนไปองศาที่ z 
    servo2.write(z+=i);
    delay(30);
  }
}

void up() {
  i = 1;
  z = 180;
  for (pos = 0; pos <= 70; pos += i) {
    servo1.write(pos);  // สั่งให้ Servo หมุนไปองศาที่ degree
    servo2.write(z=z-i);
    delay(30);
  }
}







