#include "vex.h"
#include "configvalues.h"
#include "functions.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace vex;

typedef int (*f)();

std::ofstream ofs;

int F1()
{
  rMotors.setVelocity(100, pct);
  LCD.clearScreen();
  LCD.printAt(20, 20, "F1");
  LCD.render();
  return 0;
}

int F2()
{
  rMotors.setVelocity(-100, pct);
  LCD.clearScreen();
  LCD.printAt(20, 20, "F2");
  LCD.render();
  return 0;
}

int F3()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F3");
  LCD.render();
  return 0;
}

int F4()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F4");
  LCD.render();
  return 0;
}

int F5()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F5");
  LCD.render();
  return 0;
}

int F6()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F6");
  LCD.render();
  return 0;
}

int F7()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F7");
  LCD.render();
  return 0;
}

int F8()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F8");
  LCD.render();
  return 0;
}

int F9()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F9");
  LCD.render();
  return 0;
}

int F10()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F10");
  LCD.render();
  return 0;
}

int F11()
{
  LCD.clearScreen();
  LCD.printAt(20, 20, "F11");
  LCD.render();
  return 0;
}

int F12()
{
  f_autonomous();
  /*LCD.clearScreen();
  LCD.printAt(20, 20, "F12");
  LCD.render();*/
  return 0;
}

f functions[12] =
{
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12
};

void f_drivercontrol()
{ 
  int F1F2[12];
  bool bF1F2 = false;
  for(int i = 0; i < 12; i++)
  {
    if(funcs[i] == 0 || funcs[i] == 1)
    {
      F1F2[i] = 1;
    }
    else F1F2[i] = 0;
  }

  ofs.open("debug.txt", ofs.out);
  for(int i = 0; i < 12; i++)
  {
    ofs << F1F2[i] << "\n";
  }
  ofs.close();

  int q = 0;

  while(true)
  {
    //inertialDebug();

    if(Controller.ButtonL1.pressing())
    {
      q = 0;
      functions[funcs[q]]();
      
    } 
    if(Controller.ButtonL2.pressing())
    { 
      q = 1;
      functions[funcs[q]]();
    }
    if(Controller.ButtonR1.pressing()) 
    {
      q = 2;
      functions[funcs[q]]();
    }
    if(Controller.ButtonR2.pressing()) 
    {
      q = 3;
      functions[funcs[q]]();
    }
    if(Controller.ButtonX.pressing()) 
    {
      q = 4;
      functions[funcs[q]]();
    }
    if(Controller.ButtonY.pressing())
    {
      q = 5;
      functions[funcs[q]]();
    }
    if(Controller.ButtonA.pressing()) 
    {
      q = 6;
      functions[funcs[q]]();
    }
    if(Controller.ButtonB.pressing()) 
    {
      q = 7;
      functions[funcs[q]]();
    }
    if(Controller.ButtonUp.pressing()) 
    {
      q = 8;
      functions[funcs[q]]();
    }
    if(Controller.ButtonDown.pressing()) 
    {
      q = 9;
      functions[funcs[q]]();
    }
    if(Controller.ButtonLeft.pressing()) 
    {
      q = 10;
      functions[funcs[q]]();
    }
    if(Controller.ButtonRight.pressing()) 
    {
      q = 11;
      functions[funcs[q]]();
    }

    if(F1F2[q] == 1) bF1F2 = false;
    else bF1F2 = true;
    if(bF1F2) 
    {
      rMotors.setVelocity(0, pct);
      //LCD.printAt(20, 40, "F0");
      //LCD.render();
    }

    Task.sleep(5);
  }
}