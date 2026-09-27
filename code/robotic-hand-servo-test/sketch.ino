#include <Servo.h>
Servo finger;

void setup() {
  finger.attach(9);
}

void loop() {
  finger.write(0);    // open
  delay(1000);
  finger.write(90);   // curled
  delay(1000);
}