#include "Tracer.h" // <1>
#include <stdio.h>


Tracer::Tracer():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true), // <2>
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),  // <2>
  colorSensor(EPort::PORT_E) { // <2>
}

void Tracer::init() {
  printf("Tracer\n");
}

void Tracer::terminate() {
  printf("Stopped.\n");
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  if( colorSensor.getReflection() >= mThreshold) { // <1>
    leftWheel.setPower(0);
    rightWheel.setPower(pwm);
  } else {   // <2>
    leftWheel.setPower(pwm);
    rightWheel.setPower(0);
  }
}
