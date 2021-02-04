#include "vex.h"
#include "configvalues.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace vex;

std::ifstream ifs;
int data;

int threshold1 = deadbands[0];
int threshold2 = deadbands[1];
int threshold3 = deadbands[2];
int threshold4 = deadbands[3];

brain Brain;
brain::lcd LCD;
controller::lcd ControllerLCD;

competition Competition;
task Task;
color Color;

controller Controller = controller(primary);

motor frontLeftMotor = motor(PORT6, ratio36_1, false); //u
motor frontRightMotor = motor(PORT8, ratio36_1, true); //u
motor backLeftMotor = motor(PORT4, ratio36_1, false);
motor backRightMotor = motor(PORT5, ratio36_1, true);
motor backLiftMotor = motor(PORT10, ratio6_1, false); //u
motor frontLiftMotor = motor(PORT9, ratio6_1, false);
motor leftIntakeMotor = motor(PORT1, ratio6_1, false); //u
motor rightIntakeMotor = motor(PORT7, ratio6_1, true); //u



motor_group leftMotors = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightMotors = motor_group(frontRightMotor, backRightMotor);
motor_group driveMotors = motor_group(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);
motor_group liftMotors = motor_group(backLiftMotor, frontLiftMotor);
motor_group intakeMotors = motor_group(leftIntakeMotor, rightIntakeMotor);

inertial inertialSensor = inertial(PORT2); //u

drivetrain mainDrivetrain = drivetrain(leftMotors, rightMotors);

timer t1;

/*vex-vision-config:begin*/
vision::signature SIG_1 = vision::signature (1, 3297, 8769, 6033, -489, 895, 203, 1.5, 0);
vision::signature SIG_2 = vision::signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_3 = vision::signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_4 = vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_5 = vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_6 = vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision::signature SIG_7 = vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision visionSensor = vision (PORT17, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7); 
/*vex-vision-config:end*/

int error(std::string str1 = "", std::string str2 = "", bool cond = true)
{
  LCD.clearScreen();
  LCD.printAt(20, 20, str1.c_str());
  LCD.printAt(20, 60, str2.c_str());
  LCD.render();
  while(cond) 
  {
    Controller.rumble("-");
    if(Controller.ButtonA.pressing() || Controller.ButtonB.pressing() || Controller.ButtonX.pressing() || Controller.ButtonY.pressing() ||
    Controller.ButtonUp.pressing() || Controller.ButtonDown.pressing() || Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing() || 
    Controller.ButtonL1.pressing()  || Controller.ButtonL2.pressing()  || Controller.ButtonR1.pressing()  || Controller.ButtonR2.pressing() || 
    Controller.Axis3.position() < -threshold3 || Controller.Axis4.position() < -threshold4 || Controller.Axis3.position() > threshold3 || Controller.Axis4.position() > threshold4 ||
    Controller.Axis1.position() < -threshold1 || Controller.Axis2.position() < -threshold2 || Controller.Axis1.position() > threshold1|| Controller.Axis2.position() > threshold2 ||
    LCD.pressing())
    cond = false;
    else wait(0.1, seconds);
  }
  LCD.clearScreen();
  LCD.render();
  driveMotors.stop();
  intakeMotors.stop();
  liftMotors.stop();
  return 0;
}

bool checkMotors()
{
  if(errors)
  {
    std::ostringstream ss;
    std::ostringstream ss2;
    std::string s = "MOTOR NOT INSTALLED | NAME: ";
    std::string ses = "SENSOR NOT INSTALLED | NAME: ";
    std::string s2 = "PORT: ";

    if(!frontLeftMotor.installed())
    {
      ss << s << "FRONT LEFT"; ss2 << s2 << frontLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontLeftMotor.installed());
      return false;
    }
    else if(!frontRightMotor.installed())
    {
      ss << s << "FRONT RIGHT"; ss2  << s2 << frontRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontRightMotor.installed());
      return false;
    }
    else if(!backLeftMotor.installed())
    {
      ss << s << "BACK LEFT"; ss2 << s2 << backLeftMotor.index() + 1;
      error(ss.str(), ss2.str(), !backLeftMotor.installed());
      return false;
    }
    else if(!backRightMotor.installed())
    {
      ss << s << "BACK RIGHT"; ss2 << s2 << backRightMotor.index() + 1;
      error(ss.str(), ss2.str(), !backRightMotor.installed());
      return false;
    }
    else if(!backLiftMotor.installed())
    {
      ss << s << "BACK LIFT"; ss2 << s2 << backLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !backLiftMotor.installed());
      return false;
    }
    else if(!frontLiftMotor.installed())
    {
      ss << s << "FRONT LIFT"; ss2 << s2 << frontLiftMotor.index() + 1;
      error(ss.str(), ss2.str(), !frontLiftMotor.installed());
      return false;
    }
    else if(!leftIntakeMotor.installed())
    {
      ss << s << "LEFT INTAKE"; ss2 << s2 << leftIntakeMotor.index() + 1;
      error(ss.str(), ss2.str(), !leftIntakeMotor.installed());
      return false;
    }
    else if(!rightIntakeMotor.installed())
    {
      ss << s << "RIGHT INTAKE"; ss2 << s2 << rightIntakeMotor.index() + 1;
      error(ss.str(), ss2.str(), !rightIntakeMotor.installed());
      return false;
    }
    else if(!inertialSensor.installed())
    {
      ss << ses << "INERTIAL"; ss2 << s2 << inertialSensor.index() + 1;
      error(ss.str(), ss2.str(), !inertialSensor.installed());
      return false;
    }
    else return true;
  }
  else return true;
}

void vexcodeInit(void)
{
  if(!Brain.SDcard.isInserted())
  {
    error("NO SD CARD");
  }

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

  ifs.open("joysticks.txt", ifs.in);
  ifs >> data;
  dType = data;
  ifs.close();

  ifs.open("deadbands.txt", ifs.in);
  for(int i = 0; i < 4; i++)
  {
    ifs >> data;
    deadbands[i] = data;
  }
  ifs.close();
  int dbands[10];
  for(int i = 0; i < 10; i++)
  {
    dbands[i] = 5 * (i + 1);
  }
  threshold1 = dbands[deadbands[0]];
  threshold2 = dbands[deadbands[1]];
  threshold3 = dbands[deadbands[2]];
  threshold4 = dbands[deadbands[3]];

  ifs.open("settings.txt", ifs.in);
  ifs >> data;
  wTurn = data;
  ifs >> data;
  errors = data;
  ifs.close();

  checkMotors();

  //backLiftMotor.setBrake(brake);
  frontLiftMotor.setBrake(brake);

  visionSensor.setWifiMode(vision::wifiMode::off);
  inertialSensor.calibrate();
  LCD.clearScreen();
  LCD.printAt(20, 20, "Calibrating Inertial Sensor");
  LCD.render();
  while(inertialSensor.isCalibrating()) Task.sleep(25);

  LCD.clearScreen();
  LCD.render();
}