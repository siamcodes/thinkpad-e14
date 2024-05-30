void ReadHuskylens() {
  huskylens.request();
  HUSKYLENSResult result = huskylens.read();
  //result = huskylens.read();
  //int x = map(result.xCenter, 0, 320, -160, 160);
  //oled.text(0,0,"%d", x);
  //oled.show();
  
  for (int i = 0; i < numsensor; i++) {
    int x = map(result.xTarget, 140, 200, 1000, 0);  //Serial.print(String()+("\n err=")+err);  // getting and maping err
    if (x > 1000) x = 1000;     //1000
    if (x < 0) x = 0;           //0
    s[i] = x;
  }
  
}

void Read() {
  for (int i = 0; i < numsensor; i++) {
    int x = map(analog(i), Min[i], Max[i], 1000, 0);  // อ่านค่าเซ้นเซอร์
    if (x > 1000) x = 1000;
    if (x < 0) x = 0;
    s[i] = x;
  }
}

int ReadLine() {  // เอาค่าเซนเซอร์มาทำ ตำแหน่ง
  int k;
  int on_line = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  on_line = 0;
  //Read();
  ReadHuskylens();
  avg = 0;
  sum = 0;
  for (int i = 0; i < numsensor; i++) {
    if (s[i] > 200) on_line = 1;
    if (s[i] > 50) {
      avg += s[i] * (i * 1000);
      sum += s[i];
    }
  }
  if (on_line == 0) {
    if (last_value < ((numsensor - 1) * 1000) / 2) {
      return 0;
    } else {
      return (numsensor - 1) * 1000;
    }
  }
  last_value = avg / sum;
  return last_value;
}
