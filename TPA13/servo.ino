void SV() {
  servo(1, 40); delay(1000);  //จับบอล
  servo(1, 80); delay(100);
  servo(1, 100); delay(100);
  servo(1, 160); delay(2000);    //เทเข้า
}

void sv2() {
  servo(2, 180); delay(100);  //ปิดทางออก
  servo(2, 100); delay(2000);  //เปิดทางออก
  ao(); delay(5000);
}

//for(int pos = 40; pos <=180; pos++){
//    servo(1,pos);
//    if(pos == 150){
//      break;
//    }
