#include "app.h"
#include <stdio.h>

#include "Motor.h" 
#include "Clock.h" 
#include "ForceSensor.h" 

using namespace spikeapi; 


/**
 * メインタスク
 */
void main_task(intptr_t unused) { 

  Motor leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true); // <1>
  Motor rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true);  // <2>
  ForceSensor forceSensor(EPort::PORT_D); // <3>
  Clock clock; // <4>

#ifndef MAKE_RASPIKE
  const int8_t pwm = 30;
#else
  const int8_t pwm = 60;
#endif

  const uint32_t duration = 2000*1000; 

  while(1) { 
    printf("Forwarding...\n");
    leftWheel.setPower(pwm); 
    rightWheel.setPower(pwm);
    clock.sleep(duration); 

    printf("Backwarding...\n");
    leftWheel.setPower(-pwm);
    rightWheel.setPower(-pwm);
    clock.sleep(duration);

    // フォースセンサーが押されているかどうか調べる
    if (forceSensor.isTouched()) {
      break;
    }
  } 

  printf("Stopped.\n");
  leftWheel.stop();
  rightWheel.stop();
  // フォースセンサーの押された状態が解除されたかを調べる
  while(forceSensor.isTouched()) {
      ;
  }

  ext_tsk(); 
}
