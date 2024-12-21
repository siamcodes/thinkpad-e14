#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);           // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  lcd.print("ArduinoAll TEST");  //พิมพ์ข้อความ
  lcd.setCursor(2, 1);           // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 2 บรรทัดที่ 1
  lcd.print("arduinoall.com");   //พิมพ์ข้อความ "arduinoall.com"
}
void loop() {
}