#include "POP32.h"
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <Servo.h>

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);

//Servo Lservo;
//Servo Rservo;

// Declare variables
int32_t error;
int ID1;
float Kc = 10.80;  // Controller gain (0.80)
float Paction;
int Avspeed = 100;  // Average speed (100)

void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}

void Lspeed(int speed)  // Set speed of left motor, -500 < speed < 500
{
  //Lservo.writeMicroseconds(speed + 1500);
  motor(1, speed + 1500);
}

void Rspeed(int speed)  // Set speed of right motor, -500 < speed < 500
{
  //Rservo.writeMicroseconds(1500 - speed);
  motor(2, 1500 - speed);
}

void setup() {
  //Lservo.attach(5);
  //Rservo.attach(6);
  Serial.begin(115200);
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);  //Switch the algorithm to line tracking.
  beep();
  sw_ok_press();
  beep(3);
}

void loop() {
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  else if (!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
  else {
    HUSKYLENSResult result = huskylens.read();
    printResult(result);

    // Calculate the error
    error = (int32_t)160 - (int32_t)result.xTarget;

    // Perform P-only control
    Paction = Kc * error;
    //Lspeed(Avspeed - int(Paction));
    //Rspeed(Avspeed + int(Paction) + 40);  // Motors behave different
    motor(1, Avspeed-int(Paction));
    motor(2, Avspeed+ int(Paction) + 40);
    delay(10);
  }
}
