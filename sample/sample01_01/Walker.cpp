#include "Walker.h"
#include <stdio.h>

Walker::Walker():               
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true), 
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),  
  forceSensor(EPort::PORT_D) {
}

void Walker::run() {
  while(1) {
    printf("Forwarding...\n");
    leftWheel.setPower(pwm);
    rightWheel.setPower(pwm);
    clock.sleep(duration); 

    printf("Backwarding...\n");
    leftWheel.setPower(-pwm);
    rightWheel.setPower(-pwm);
    clock.sleep(duration);

    // フォースセンサーを押し、それを捕捉する
    if (forceSensor.isTouched()) {
      break;
    }
  }

  printf("Stopped.\n");
  leftWheel.stop();
  rightWheel.stop();
  // フォースセンサーを押し、それを捕捉する
  while(forceSensor.isTouched()) {
      ;
  }
}