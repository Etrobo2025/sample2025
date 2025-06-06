#ifndef WALKER_H
#define WALKER_H

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

#endif // WALKER_H