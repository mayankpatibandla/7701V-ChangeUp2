#include "vex.h"

using namespace vex;

void inertialDebug()
{  
  inertial::quaternion inertialSensor_quaternion;
  inertialSensor_quaternion = inertialSensor.orientation();
  Brain.Screen.clearScreen();

  Brain.Screen.setFont(mono15);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  
  Brain.Screen.printAt(20, 30, "GX  %8.3f", inertialSensor.gyroRate(xaxis, dps));
  Brain.Screen.printAt(20, 45, "GY  %8.3f", inertialSensor.gyroRate(yaxis, dps));
  Brain.Screen.printAt(20, 60, "GZ  %8.3f", inertialSensor.gyroRate(zaxis, dps));

  Brain.Screen.printAt(20, 90, "AX  %8.3f", inertialSensor.acceleration(xaxis));
  Brain.Screen.printAt(20, 105, "AY  %8.3f", inertialSensor.acceleration(yaxis));
  Brain.Screen.printAt(20, 120, "AZ  %8.3f", inertialSensor.acceleration(zaxis));

  Brain.Screen.printAt(20, 150, "A   %8.3f", inertialSensor_quaternion.a);
  Brain.Screen.printAt(20, 165, "B   %8.3f", inertialSensor_quaternion.b);
  Brain.Screen.printAt(20, 180, "C   %8.3f", inertialSensor_quaternion.c);
  Brain.Screen.printAt(20, 195, "D   %8.3f", inertialSensor_quaternion.d);

  Brain.Screen.printAt(150, 30, "Roll     %7.2f", inertialSensor.roll());
  Brain.Screen.printAt(150, 45, "Pitch    %7.2f", inertialSensor.pitch());
  Brain.Screen.printAt(150, 60, "Yaw      %7.2f", inertialSensor.yaw());

  Brain.Screen.printAt(150, 90, "Heading  %7.2f", inertialSensor.heading());
  Brain.Screen.printAt(150, 105, "Rotation %7.2f", inertialSensor.rotation());

  Brain.Screen.render();
}

int P(int currentPos, int target = 158, float kP = 0.5)
{
  int error = target - currentPos;
  int pow = error * kP;
  return pow;
}

void inertialTurn(int target, turnType turnDir, int speed, bool c)
{
  if(turnDir == right)
  {
    leftMotors.spin(forward, speed, percentUnits::pct);
    rightMotors.spin(reverse, speed, percentUnits::pct);

    if(c) while(inertialSensor.heading(degrees) <= target) wait(1, msec);
    if(!c) while(inertialSensor.heading(degrees) >= target) wait(1, msec);
  }
  else if(turnDir == left)
  {
    leftMotors.spin(reverse, speed, percentUnits::pct);
    rightMotors.spin(forward, speed, percentUnits::pct);

    if(c) while(inertialSensor.heading(degrees) <= target) wait(1, msec);
    if(!c) while(inertialSensor.heading(degrees) >= target) wait(1, msec);
  }
  
  driveMotors.stop(brake);
}

//void t_inertialTurn(int target = 90, turnType turnDir = right, int speed = 50)

void f_forward(int rots = 360, int speed = 50, int timeout = 0, bool wait = true)
{
  driveMotors.setTimeout(timeout, msec);
  driveMotors.spinFor(rots, deg, speed, velocityUnits::pct, wait);
}

void pInertialTurn(int target = 90, float kP = 0.5, int accuracy = 3)
{
  bool done = false;
  while(!done)
  {
    int currentPos = inertialSensor.heading();
    int speed = P(currentPos, target, kP);
    rightMotors.setVelocity(speed, pct);
    leftMotors.setVelocity(-speed, pct);
    if(currentPos < target - accuracy || currentPos > target + accuracy) driveMotors.spin(fwd);
    else done = true;
    Task.sleep(1);
  }
  driveMotors.stop();
}

void pVisionTurn(vision::signature sig, float kP = 0.5, int accuracy = 3)
{
  const int minSize = 15;

  visionSensor.takeSnapshot(sig);
  vision::object obj = visionSensor.largestObject;

  if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
  {
    LCD.clearScreen();
    LCD.printAt(20, 20, "Object doesn't exist");
    LCD.render();
  }
  else
  {
    bool done = false;
    while(!done)
    {
      int speed = P(obj.centerX, 158, kP);
      rightMotors.setVelocity(speed, pct);
      leftMotors.setVelocity(-speed, pct);

      if(obj.centerX < 158 - accuracy || obj.centerX > 158 + accuracy)
      {
        driveMotors.spin(fwd);
        LCD.clearScreen();
        LCD.printAt(20, 20, "Turning");
        LCD.printAt(20, 60, "%d", obj.centerX);
        LCD.render();
      }
      else done = true;
      visionSensor.takeSnapshot(sig);
      obj = visionSensor.largestObject;
      Task.sleep(5);
    }
    LCD.clearScreen();
    LCD.printAt(20, 20, "Done");
    LCD.render();
    driveMotors.stop();
  }
}

void visionTurn(vision::signature sig, int accuracy = 3, int speed = 10)
{
  const int minSize = 10;

  accuracy = abs(accuracy);

  visionSensor.takeSnapshot(sig);
  vision::object obj = visionSensor.largestObject;

  if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
  {
    LCD.clearScreen();
    LCD.printAt(20, 20, "Object doesn't exist");
    LCD.render();
  }
  else
  {
    bool done = false;
    while(!done)
    {
      visionSensor.takeSnapshot(sig);
      vision::object obj = visionSensor.largestObject;
      if(obj.centerX < 158 - accuracy)
      {
        leftMotors.spin(reverse, speed, percentUnits::pct);
        rightMotors.spin(forward, speed, percentUnits::pct);
      }
      else if(obj.centerX > 158 + accuracy)
      {
        leftMotors.spin(forward, speed, percentUnits::pct);
        rightMotors.spin(reverse, speed, percentUnits::pct);
      }
      else done = true;
    }
    driveMotors.stop();
  }
}

bool charToBool(char str)
{
  if(str == '0') return false;
  else if(str == '1') return true;
  else return false;
}

int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, float kP, float kI, float kD, inertial sensor, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;
  int sensorValue = sensor.heading(deg);

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue < (target - accuracy) % 360)
  {
    sensorValue = sensor.heading(deg);
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motor1.setVelocity(pow * reverse, pct);
    motor2.setVelocity(-pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}

/*int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, float kP, float kI, float kD, encoder sensor, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;
  int sensorValue = sensor.heading(deg);

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue < (target - accuracy) % 360)
  {
    sensorValue = sensor.heading(deg);
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motor1.setVelocity(pow * reverse, pct);
    motor2.setVelocity(-pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}*/

int PID(motor_group motors, int target, int range, int accuracy, float kP, float kI, float kD, int sensorValue, int dT = 15, bool reversed = false)
{
  int integral;
  int error;
  int prevError;
  int derivative;
  int pow;
  int reverse = 1;

  if(reversed)
  {
    reverse = -1;
  }

  while(sensorValue > (target + accuracy) % 360 || sensorValue > (target - accuracy) % 360)
  {
    error = target - sensorValue;
    integral += error;

    if(error == 0 || error > range)
    {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;
    pow = (error * kP) + (integral * kI) + (derivative * kD);
    motors.setVelocity(pow * reverse, pct);
    Task.sleep(dT);
  }

  return 1;
}