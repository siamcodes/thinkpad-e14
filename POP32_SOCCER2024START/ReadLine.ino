void Read() {
  for (int i = 0; i < numsensor; i++) {
    int x = map(analog10(i), Min[i], Max[i], 1000, 0);  // อ่านค่าเซ้นเซอร์
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
  Read();
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

void view() {  // แสดงค่าหน้าจอ
  while (1) {
    oled.text(0, 0, "s[0] = %d  ", analog10(0));
    oled.text(1, 0, "s[1] = %d  ", analog10(1));
    oled.text(2, 0, "s[2] = %d  ", analog10(2));
    oled.show();
    Serial.print(analog10(0));
    Serial.print("\t,");
    Serial.print(analog10(1));
    Serial.print("\t,");
    Serial.println(analog10(2));
  }
  delay(200);
}

void viewRead() {
  while (1) {
    ReadLine();
    oled.text(0, 0, "s[0] = %d  ", s[0]);
    oled.text(1, 0, "s[1] = %d  ", s[1]);
    oled.text(2, 0, "s[2] = %d  ", s[2]);
    oled.show();
  }
  delay(200);
}