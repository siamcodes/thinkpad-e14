void ReadADC() {
  L = analog(1);
  C = analog(2);
  R = analog(3);
}

void ShowADC() {
  ReadADC();
  oled.text(0, 0, "L=%d", L);
  oled.text(1, 0, "C=%d", C);
  oled.text(2, 0, "R=%d", R);
  oled.show();
}

void ConvertADC() {
  ReadADC();  //ขาวมาก=1  เขียวน้อย=0
  if (L > RefL) L = 0; else L = 1;
  if (C > RefC) C = 0; else C = 1;
  if (R > RefR) R = 0; else R = 1;
}

