#include <ros.h>
#include <std_msgs/String.h>
#include <Servo.h>

// Initialize ROS NodeHandle
ros::NodeHandle nh;

// Define PWM and Servo pins
const int pwmPins[] = {3, 5, 6};
const int servoPins[] = {3, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // Removed pins 2 and 4

// Arrays to keep track of pin modes
bool isPWMPin[14] = {false}; // Assume all pins are not in PWM mode by default
bool isServoPin[14] = {false}; // Assume all pins are not in Servo mode by default

// Servo objects for each pin
Servo servos[sizeof(servoPins) / sizeof(servoPins[0])];

// Function to set PWM mode for a pin
void setPWMPin(int pin, bool mode) {
  if (pin != 2 && pin != 4) { // Ensure pin 2 and 4 are not changed
    if (mode) {
      pinMode(pin, OUTPUT);
      isPWMPin[pin] = true;
    } else {
      isPWMPin[pin] = false;
      pinMode(pin, OUTPUT); // Return to digital output mode
    }
  }
}

// Function to set Servo mode for a pin
void setServoPin(int pin, bool mode) {
  if (pin != 2 && pin != 4) { // Ensure pin 2 and 4 are not changed
    if (mode) {
      for (int i = 0; i < sizeof(servoPins) / sizeof(servoPins[0]); ++i) {
        if (servoPins[i] == pin) {
          servos[i].attach(pin);
          isServoPin[pin] = true;
          break;
        }
      }
    } else {
      for (int i = 0; i < sizeof(servoPins) / sizeof(servoPins[0]); ++i) {
        if (servoPins[i] == pin) {
          servos[i].detach();
          isServoPin[pin] = false;
          break;
        }
      }
      pinMode(pin, OUTPUT); // Return to digital output mode
    }
  }
}

// Callback function to set digital pin states or PWM values
void digitalPinCb(const std_msgs::String& msg) {
  int pin, value;
  sscanf(msg.data, "%d:%d", &pin, &value);

  if (isPWMPin[pin]) {
    analogWrite(pin, value);
  } else if (isServoPin[pin]) {
    for (int i = 0; i < sizeof(servoPins) / sizeof(servoPins[0]); ++i) {
      if (servoPins[i] == pin) {
        servos[i].write(value);
        break;
      }
    }
  } else {
    digitalWrite(pin, value);
  }
}

// Callback function to set pin modes
void pinModeCb(const std_msgs::String& msg) {
  int pin;
  char mode[10];
  sscanf(msg.data, "%d:%s", &pin, mode);

  if (pin != 2 && pin != 4) { // Ensure pin 2 and 4 are not changed
    if (strcmp(mode, "PWM") == 0) {
      setPWMPin(pin, true);
      setServoPin(pin, false);
    } else if (strcmp(mode, "SERVO") == 0) {
      setServoPin(pin, true);
      setPWMPin(pin, false);
    } else {
      setPWMPin(pin, false);
      setServoPin(pin, false);
      pinMode(pin, OUTPUT); // Default to digital output mode
    }
  }
}

// Declare the publisher and subscribers globally
std_msgs::String analog_msg;
std_msgs::String digital_input_msg;
ros::Publisher analog_publisher("analog_read", &analog_msg);
ros::Publisher digital_input_publisher("digital_read", &digital_input_msg);
ros::Subscriber<std_msgs::String> digital_subscriber("digital_write", digitalPinCb);
ros::Subscriber<std_msgs::String> pin_mode_subscriber("pinMode", pinModeCb);

// Function to read analog pins A0 to A5 and publish their values
void publishAnalogValues() {
  char buffer[128];
  sprintf(buffer, "{\"A0\":%d, \"A1\":%d, \"A2\":%d, \"A3\":%d, \"A4\":%d, \"A5\":%d}",
          analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3), analogRead(A4), analogRead(A5));
  analog_msg.data = buffer;
  analog_publisher.publish(&analog_msg);
}

// Function to read digital input pins 2 and 4 and publish their values
void publishDigitalInputValues() {
  char buffer[64];
  sprintf(buffer, "{\"D2\":%d, \"D4\":%d}", digitalRead(2), digitalRead(4));
  digital_input_msg.data = buffer;
  digital_input_publisher.publish(&digital_input_msg);
}

void setup() {
  // Initialize digital pins
  for (int pin = 2; pin <= 13; ++pin) {
    if (pin != 2 && pin != 4) {
      pinMode(pin, OUTPUT);
    } else {
      pinMode(pin, INPUT); // Set pin 2 and 4 as INPUT
    }
  }
 
  nh.initNode();
  nh.advertise(analog_publisher);
  nh.advertise(digital_input_publisher);
  nh.subscribe(digital_subscriber);
  nh.subscribe(pin_mode_subscriber);
}

void loop() {
  publishAnalogValues();
  publishDigitalInputValues();
  nh.spinOnce();
  delay(50); // Publish values every 50 milliseconds
}
