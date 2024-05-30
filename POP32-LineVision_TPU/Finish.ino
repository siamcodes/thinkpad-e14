void Finish() {  //หุ่นยนต์หยุดและแสดงเวลาทั้งหมด
  ReadTimer1();
  ao();
  beep(1);
  oled.clear();
  oled.text(0, 0, "Finish");
  oled.text(1, 0, "Time = %l.%l s", Timer1 / 1000, Timer1 % 1000);
  oled.show();
  while (1) {}  //หยุดวนรอบตลอดดไป
}