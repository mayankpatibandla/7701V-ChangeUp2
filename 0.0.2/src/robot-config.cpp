#include "vex.h"

using namespace vex;

brain Brain;
brain::lcd LCD;
controller::lcd ControllerLCD;

competition Competition;
task Task;
color Color;

controller Controller = controller(primary);

motor frontLeftMotor = motor(PORT1, ratio18_1, false);
motor frontRightMotor = motor(PORT2, ratio18_1, true);
motor backLeftMotor = motor(PORT3, ratio18_1, false);
motor backRightMotor = motor(PORT4, ratio18_1, true);
motor backMotor = motor(PORT5, ratio18_1, false);
motor frontMotor = motor(PORT6, ratio18_1, false);
motor leftIntakeMotor = motor(PORT7, ratio18_1, false);
motor rightIntakeMotor = motor(PORT8, ratio18_1, true);

motor_group leftMotors = motor_group(frontLeftMotor, backLeftMotor);
motor_group rightMotors = motor_group(frontRightMotor, backRightMotor);
motor_group rMotors = motor_group(backMotor, frontMotor);
motor_group intakeMotors = motor_group(leftIntakeMotor, rightIntakeMotor);

inertial inertialSensor = inertial(PORT10);

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
vision visionSensor = vision (PORT9, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/

void vexcodeInit(void)
{
  if(!Brain.SDcard.isInserted())
  {
    LCD.print("NO SD CARD");
    LCD.render();
    Controller.rumble("--------");
    while(true) wait(10, sec);
  }
  visionSensor.setWifiMode(vision::wifiMode::off);
  LCD.setCursor(1, 1);
  inertialSensor.calibrate();
  LCD.clearScreen();
  LCD.print("Calibrating Inertial Sensor");
  LCD.render();
  while(inertialSensor.isCalibrating()) 
  {
    wait(25, msec);
  }
}