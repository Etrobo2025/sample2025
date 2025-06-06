#include "app.h"
#include <stdio.h>

#include "Motor.h"
#include "Clock.h"
#include "ForceSensor.h"

using namespace spikeapi;

class Walker {
public:
  Walker();
  void run();

private:
  Motor leftWheel;              
  Motor rightWheel;             
  ForceSensor forceSensor;      
  Clock clock;                  

#ifndef MAKE_RASPIKE
  const int8_t pwm = 30;
#else
  const int8_t pwm = 60;
#endif
  const uint32_t duration = 2000*1000;
};

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

void main_task(intptr_t unused) {

  Walker walker;                

  walker.run();                 

  ext_tsk();
}
