void ResetTimer0() {       //เริ่มใช้งาน Timer0
  StartTimer0 = millis();  //เก็บเวลาเริมต้นนใน StartTimer0
  Timer0 = 0;              //เคลียร์ Timer0
}

void ReadTimer0() {                 //อ่านค่า Timer0
  Timer0 = millis() - StartTimer0;  //เอาเวลาปัจจุบัน - เวลาเริ่มต้น
}

void ResetTimer1() {       //เริ่มใช้งาน Timer1
  StartTimer1 = millis();  //เก็บเวลาเริมต้นนใน StartTimer1
  Timer1 = 0;              //เคลียร์ Timer1
}

void ReadTimer1() {                 //อ่านค่า Timer0
  Timer1 = millis() - StartTimer1;  //เอาเวลาปัจจุบัน - เวลาเริ่มต้น
}