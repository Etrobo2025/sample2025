#include "app.h"
#include "Walker.h"

void main_task(intptr_t unused) {

  Walker walker;                

  walker.run();                 

  ext_tsk();
}
