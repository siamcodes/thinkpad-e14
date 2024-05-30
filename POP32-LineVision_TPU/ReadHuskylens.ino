void ReadHuskylens(){
    huskylens.request(ID1);
    result = huskylens.read();
    //Error = map(result.xTarget, 0, 320, -160, 160);  //Serial.print(String()+("\n err=")+err);  // getting and maping err
    Error = map(result.xCenter, 0, 320, -100, 100);
}