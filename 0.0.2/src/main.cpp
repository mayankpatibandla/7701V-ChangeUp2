#include "vex.h"
#include "functions.h"

using namespace vex;

int main() 
{
  vexcodeInit();

  Competition.autonomous(f_autonomous1);
  Competition.drivercontrol(f_drivercontrol);

  while(true)
  {
    ControllerLCD.clearLine(2);
    ControllerLCD.print(inertialSensor.heading(degrees));
    wait(250, msec);
  }
}