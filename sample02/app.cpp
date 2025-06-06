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

protected:             // <1>
  void forward(void);  // <2>
  void back(void);     // <2>
  void stop(void);     // <2>
};

Walker::Walker():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true),
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),
  forceSensor(EPort::PORT_D) {
}

void Walker::forward(void) {  // <3>
    printf("Forwarding...\n");
    leftWheel.setPower(pwm);
    rightWheel.setPower(pwm);
}

void Walker::back(void) {  // <3>
    printf("Backwarding...\n");
    leftWheel.setPower(-pwm);
    rightWheel.setPower(-pwm);
}

void Walker::stop(void) {  // <3>
  printf("Stopped.\n");
  leftWheel.stop();
  rightWheel.stop();
}

void Walker::run() {
  while(1) {
    forward();             // <4>
    clock.sleep(duration);
    back();                // <4>
    clock.sleep(duration);

    // フォースセンサーを押し、それを捕捉する
    if (forceSensor.isTouched()) {
      break;
    }
  }

  stop();                // <4>
  while(forceSensor.isTouched()) {
      ;
  }
}

void main_task(intptr_t unused) { // <5>
  Walker walker;
  walker.run();
  ext_tsk();
}
