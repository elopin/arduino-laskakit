#include <Servo.h>

Servo servo;
int servoPin = 2;
int position = 0;

void setup() {
  servo.attach(servoPin);
}

void loop() {
  for (position = 0; position <= 160; position++) {  // turn around from 0 to 160 degrees
    // in steps of 1 degree
    servo.write(position);  // set servo to "position"
    delay(15);              // wait 15ms for servo to get position
  }
  for (position = 160; position >= 0; position--) {  // turn around from 160 to 0 degrees
    servo.write(position);                           // set servo to "position"
    delay(15);                                       // wait 15ms for servo to get position
  }
}
