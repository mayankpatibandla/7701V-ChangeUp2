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

int P(int currentPos, float kP = 0.5, int target = 158, int accuracy = 3)
{
  int error = target - currentPos;
  int pow = error * kP;
  return pow;
}

void inertialTurn(turnType turnDir = right, float deg = 90, int speed = 50)
{
  if(turnDir == right)
  {
    leftMotors.spin(forward, speed, percentUnits::pct);
    rightMotors.spin(reverse, speed, percentUnits::pct);
    waitUntil((inertialSensor.heading(degrees) >= deg));
  }
  else
  {
    leftMotors.spin(reverse, speed, percentUnits::pct);
    rightMotors.spin(forward, speed, percentUnits::pct);
    waitUntil((inertialSensor.heading(degrees) <= deg));
  }
  
  leftMotors.stop();
  rightMotors.stop();
}

void visionTurn(vision::signature sig, float kP = 0.5, int accuracy = 3)
{
  LCD.clearScreen();
  LCD.print("asdashhf;gmhlkdf");
  LCD.render();
  const int minSize = 15;

  visionSensor.takeSnapshot(sig);

  vision::object obj = visionSensor.largestObject;

  if((!obj.exists) || (obj.width < minSize || obj.height < minSize))
  {
    LCD.clearScreen();
    LCD.print("asdasdasdas");
    LCD.render();
  }
  else
  {
    bool done = false;
    while(!done)
    {
      int speed = P(obj.centerX, kP, 158, accuracy);
      rightMotors.setVelocity(speed, pct);
      leftMotors.setVelocity(-speed, pct);

      if(obj.centerX < 158 - accuracy || obj.centerX > 158 + accuracy)
      {
        rightMotors.spin(fwd);
        leftMotors.spin(fwd);
        LCD.clearScreen();
        LCD.printAt(20, 20, "Turning");
        LCD.render();
      }
      else done = true;
      Task.sleep(5);
    }
    LCD.clearScreen();
    LCD.printAt(20, 20, "Done");
    LCD.render();
    leftMotors.stop();
    rightMotors.stop();
    Task.sleep(10000);
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