void MotorStop(){
   analogWrite(AIN1, 0);
   analogWrite(AIN2, 0);
   analogWrite(BIN1, 0);
   analogWrite(BIN2, 0);
   delay(10);
}

void Forward(int MotorSpeed){
   analogWrite(AIN1, MotorSpeed);
   analogWrite(AIN2, 0);
   analogWrite(BIN1, MotorSpeed);
   analogWrite(BIN2, 0);
}

void Backward(int MotorSpeed){
   analogWrite(AIN1, 0);
   analogWrite(AIN2, MotorSpeed);
   analogWrite(BIN1, 0);
   analogWrite(BIN2, MotorSpeed);
}

void TurnLeft(){
   analogWrite(AIN1, TurnSpeed);
   analogWrite(AIN2, 0);
   analogWrite(BIN1, 0);
   analogWrite(BIN2, TurnSpeed);
}

void TurnRight(){
   analogWrite(AIN1, 0);
   analogWrite(AIN2, TurnSpeed);
   analogWrite(BIN1, TurnSpeed);
   analogWrite(BIN2, 0);
}
