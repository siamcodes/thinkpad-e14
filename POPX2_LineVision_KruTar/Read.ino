void ReadHuskylens() {  //ดัดแปลงจาก Read()
  huskylens.request();
  result = huskylens.read();
  //int x = map(result.xCenter, 0, 320, -160, 160);
  //oled.text(0,0,"x = %d", x);
  //oled.show();
  //delay(100);

  for (int i = 0; i < numsensor; i++) {
    int x = map(result.xCenter, Min[i], Max[i], 1000, 0);  //Serial.print(String()+("\n err=")+err);
    if (x > 1000) x = 1000;    
    if (x < 0) x = 0;                                     
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

void printResult(HUSKYLENSResult result) {  // ปริ้นค่าตำแหน่งเฉยยยย
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}
