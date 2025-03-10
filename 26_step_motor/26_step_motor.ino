#include <Stepper.h>

#define STEPS 100

//IMPORTANT order of pins (INT1, INT3, INT2, INT4)
Stepper stepper(STEPS, 2, 4, 3, 5);

int previous = 0;

void setup() {
  stepper.setSpeed(60);
}

void loop() {
  int val = analogRead(0);

  // number of steps motor will move according to potentiometer value
  // simply turn potentiometer right, motor will spin to the right for defined steps and vice versa
  stepper.step(val - previous);

  previous = val;
}
