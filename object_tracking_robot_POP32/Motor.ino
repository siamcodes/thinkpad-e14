void driveBot(HUSKYLENSResult result) {
  if (result.xCenter <= 140) {
    left();
  }else if (result.xCenter >= 200) {
    right();
  }else if ((result.xCenter >= 140) && (result.xCenter <= 200)) {
    //if (result.width <= 200) {
      forward();
    //}else if (result.width > 200) {
    //  stop(3);
    //}
  }
}

void stop(int a) {
  Move(0, 0, a);
  //Serial.println("Stop");
}

void Move(int a, int b, int c) {  // int a ความเร็วซ้าน      c คือ ดีเรย์
  motor(1, a);
  motor(2, b);
  delay(c);
}

void right() {
  Move(30,-30,10);
  //Serial.println(" Rotate Right");
}
void left() {
   Move(-30,30,10);
  //Serial.println(" Rotate Left");
}

void forward() {
   Move(30,30,10);
  //Serial.println("Forward");
}

void backward() {
   Move(-30,-30,10);
  //Serial.println("Forward");
}