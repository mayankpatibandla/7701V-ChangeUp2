#include "vex.h"
#include "configvalues.h"
#include "functions.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace vex;

std::ifstream ifs;
int data;

int main() 
{
  vexcodeInit();

  LCD.clearScreen();
  LCD.render();

  ifs.open("matchsettings.txt", ifs.in);
  ifs >> data;
  team = data;
  ifs >> data;
  side = data;
  ifs >> data;
  skills = data;
  ifs.close();

  ifs.open("keybinds.txt", ifs.in);
  for(int i = 0; i < 12; i++)
  {
    ifs >> data;
    funcs[i] = data;
  }
  ifs.close();

  Competition.autonomous(f_autonomous);
  Competition.drivercontrol(f_drivercontrol);

  while(true) {
    Task.sleep(20);
  }    
}