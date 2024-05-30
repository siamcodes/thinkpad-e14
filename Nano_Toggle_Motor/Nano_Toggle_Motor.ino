int inPin = 12;   // the number of the input pin
int outPin = 13;  // the number of the output pin
int A=5, B=6, LimitF = 2, LimitB = 4;

int state = HIGH;    // the current state of the output pin
int reading;         // the current reading from the input pin  
int previous = LOW;  // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long time = 0;          // the last time the output pin was toggled
unsigned long debounce = 400UL;  // the debounce time, increase if the output flickers

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT_PULLUP);
  pinMode(LimitB,INPUT_PULLUP);
  pinMode(LimitF,INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
  ao();
  delay(1000);        // หน่วงเวลา 2000ms
}

void loop() {
  reading = digitalRead(inPin);
  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == LOW && previous == HIGH && millis() - time > debounce) {
    if (state == LOW) {
      down(150,100);
      state = HIGH;
    } else {
      up(250,100);     
      state = LOW;
    }
    time = millis();
  }
  digitalWrite(outPin, state);
  previous = reading;
  ao();
}


