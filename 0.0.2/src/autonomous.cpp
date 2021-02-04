#include "vex.h"
#include "configvalues.h"
#include "functions.h"

using namespace vex;

void f_autonomous()
{
  LCD.clearLine();
  LCD.clearScreen();
  LCD.render();
  LCD.setPenColor(white);
  if(skills) //skills auton
  {
    LCD.print("SKILLS");
    LCD.render();  

    //score 1
    liftMotors.spin(fwd, -100, pct);
    Task.sleep(500);
    liftMotors.stop();

    leftMotors.spin(fwd, -50, pct);
    rightMotors.spin(fwd, 50, pct);
    while(inertialSensor.heading(deg) >= 325) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(1000);
    wait(1.5, sec);
    intakeMotors.stop();

    leftMotors.spin(fwd, 50, pct);
    rightMotors.spin(fwd, -50, pct);
    while(inertialSensor.heading(deg) <= 359) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(1100);

    leftMotors.spin(fwd, 50, pct);
    rightMotors.spin(fwd, -50, pct);
    while(inertialSensor.heading(deg) <= 85) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(200);

    //score 2
    liftMotors.spin(fwd, -100, pct);
    wait(1.5, sec);
    liftMotors.stop(brake);
    f_forward(-200);

    leftMotors.spin(fwd, -50, pct);
    rightMotors.spin(fwd, 50, pct);
    while(inertialSensor.heading(deg) >= 12) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(1400);
    wait(1.5, sec);
    intakeMotors.stop();

    leftMotors.spin(fwd, 50, pct);
    rightMotors.spin(fwd, -50, pct);
    while(inertialSensor.heading(deg) <= 20) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(690);

    //score 3
    liftMotors.spin(fwd, -100, pct);
    wait(1.5, sec);
    liftMotors.stop(brake);
    f_forward(-300);

    leftMotors.spin(fwd, -50, pct);
    rightMotors.spin(fwd, 50, pct);
    while(inertialSensor.heading(deg) <= 359) wait(0.01, sec);
    driveMotors.stop(brake);

    leftMotors.spin(fwd, -50, pct);
    rightMotors.spin(fwd, 50, pct);
    while(inertialSensor.heading(deg) >= 280) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(1750);
    wait(1.5, sec);
    intakeMotors.stop();

    f_forward(200);

    leftMotors.spin(fwd, 50, pct);
    rightMotors.spin(fwd, -50, pct);
    while(inertialSensor.heading(deg) <= 359) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(150);

    //score 4
    liftMotors.spin(fwd, -100, pct);
    wait(1.5, sec);
    liftMotors.stop(brake);
    f_forward(-575);

    leftMotors.spin(fwd, -50, pct);
    rightMotors.spin(fwd, 50, pct);
    wait(0.2, sec);
    while(inertialSensor.heading(deg) >= 280) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(1750);
    wait(1.5, sec);
    intakeMotors.stop();

    leftMotors.spin(fwd, 50, pct);
    rightMotors.spin(fwd, -50, pct);
    while(inertialSensor.heading(deg) <= 315) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(70 -0);

    //score 5
    liftMotors.spin(fwd, -100, pct);
    wait(1.5, sec);
    liftMotors.stop(brake);
    f_forward(-500);
  }
  else if(team) //blue autons
  {
    if(side) //right side
    {
      LCD.print("BLUE RIGHT");
      LCD.render();
      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

      leftMotors.spin(fwd, 50, pct);
      rightMotors.spin(fwd, -50, pct);
      while(inertialSensor.heading(deg) <= 348) wait(0.01, sec);
      driveMotors.stop(brake);

      intakeMotors.spin(fwd, 100, pct);
      f_forward(1200);
      wait(1.5, sec);
      intakeMotors.stop();

      leftMotors.spin(fwd, 50, pct);
      rightMotors.spin(fwd, -50, pct);
      while(inertialSensor.heading(deg) <= 359) wait(0.01, sec);
      driveMotors.stop(brake);
      
      leftMotors.spin(fwd, 50, pct);
      rightMotors.spin(fwd, -50, pct);
      while(inertialSensor.heading(deg) <= 7) wait(0.01, sec);
      driveMotors.stop(brake);

      f_forward(250);

      liftMotors.spin(fwd, -100, pct);
      wait(1.5, sec);
      liftMotors.stop(brake);
      f_forward(-250);
    }
    else //left side
    {
      LCD.print("BLUE LEFT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

      leftMotors.spin(fwd, -50, pct);
      rightMotors.spin(fwd, 50, pct);
      while(inertialSensor.heading(deg) >= 12) wait(0.01, sec);
      driveMotors.stop(brake);

      intakeMotors.spin(fwd, 100, pct);
      f_forward(1200);
      wait(1.5, sec);
      intakeMotors.stop();

      leftMotors.spin(fwd, -50, pct);
      rightMotors.spin(fwd, 50, pct);
      while(inertialSensor.heading(deg) >= 1) wait(0.01, sec);
      driveMotors.stop(brake);
      
      leftMotors.spin(fwd, -50, pct);
      rightMotors.spin(fwd, 50, pct);
      while(inertialSensor.heading(deg) >= 353) wait(0.01, sec);
      driveMotors.stop(brake);

      f_forward(250);

      liftMotors.spin(fwd, -100, pct);
      wait(1.5, sec);
      liftMotors.stop(brake);
      f_forward(-250);

    }
  }
  else //red autons
  {
    if(side) //right side
    {
      LCD.print("RED RIGHT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

      /*//face 0 and go forward with intakes on
      intakeMotors.spin(fwd, 100, pct);
      pInertialTurn(0);
      f_forward(1080, 75);
      
      //face ball, go forward, and intake
      pInertialTurn(45);
      f_forward(540, 50);
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();
      intakeMotors.stop();

      //backup, face and go to side tower
      f_forward(1080, -75);
      pInertialTurn(135);
      f_forward(1500, 75);

      //score ball and backup
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(1500);
      liftMotors.stop();
      f_forward(1080, -75);*/
    }
    else //left side
    {
      LCD.print("RED LEFT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

      /*//face 0 and go forward with intakes on
      intakeMotors.spin(fwd, 100, pct);
      pInertialTurn(0);
      f_forward(1080, 75);
      
      //face ball, go forward, and intake
      pInertialTurn(135);
      f_forward(540, 50);
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();
      intakeMotors.stop();

      //backup, face and go to side tower
      f_forward(1080, -75);
      pInertialTurn(45);
      f_forward(1500, 75);

      //score ball and backup
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(1500);
      liftMotors.stop();
      f_forward(1080, -75);*/
    }
  }
}

void f_autonomous1()
{
  LCD.clearLine();
  LCD.clearScreen();
  LCD.render();
  LCD.setPenColor(white);
  if(skills) //skills auton
  {
    LCD.print("SKILLS");
    LCD.render();  

    //score ball 1
    liftMotors.spin(fwd, -100, pct);
    Task.sleep(500);
    liftMotors.stop();

    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    while(inertialSensor.heading(deg) >= 335) wait(0.01, sec);
    driveMotors.stop(brake);

    //get ball 2
    intakeMotors.spin(fwd, 100, pct);
    f_forward(250, 45);
    liftMotors.spin(fwd, -100, pct);
    wait(0.35, msec);
    intakeMotors.stop();
    wait(0.2, sec);
    liftMotors.stop();

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 352) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(432, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    wait(0.85, msec);
    while(inertialSensor.heading(deg) <= 80) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(75, 45, 1500);

    //score ball 2
    liftMotors.spin(fwd, -100, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-45, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 125) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    while(inertialSensor.heading(deg) >= 17) wait(0.01, sec);
    driveMotors.stop(brake);

    //get ball 3
    intakeMotors.spin(fwd, 100, pct);
    f_forward(550, 45, 7500);
    wait(0.25, sec);
    intakeMotors.stop();
    //f_forward(-125, 35);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    wait(0.85, msec);
    while(inertialSensor.heading(deg) <= 30) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(130, 45, 2000);

    //score ball 3
    liftMotors.spin(fwd, -90, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-35, 45);
    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    f_forward(-30, 45);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    wait(1.2, sec);
    while(inertialSensor.heading(deg) >= 283) wait(0.01, sec);
    driveMotors.stop(brake);

    //get ball 4
    intakeMotors.spin(fwd, 100, pct);
    f_forward(600, 45);
    intakeMotors.stop();

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 352) wait(0.01, sec);
    driveMotors.stop(brake);
    f_forward(115, 45, 1750);

    //score ball 4
    liftMotors.spin(fwd, -100, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-135, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    wait(0.25, sec);
    while(inertialSensor.heading(deg) <= 50) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    wait(1.2, sec);
    while(inertialSensor.heading(deg) >= 286) wait(0.01, sec);
    driveMotors.stop(brake);
    
    //get ball 5
    intakeMotors.spin(fwd, 100, pct);
    f_forward(630, 45, 4000);
    wait(0.5, sec);
    intakeMotors.stop();

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 323) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(270, 45, 2500);

    //score ball 5
    liftMotors.spin(fwd, -90, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-60, 45);
    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    f_forward(-30, 45);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    //get ball 6
    f_forward(-300, 45);
    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 355) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(445, 45, 4000);
    wait(0.5, sec);
    intakeMotors.stop();

    f_forward(-200, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    wait(0.5, sec);
    while(inertialSensor.heading(deg) <= 169) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(443, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 255) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(130, 45, 1500);

    //score ball 6
    liftMotors.spin(fwd, -100, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-63, 45);
    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 300) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    //get ball 7
    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    while(inertialSensor.heading(deg) >= 194) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(710, 45);
    wait(0.5, sec);
    intakeMotors.stop();

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 205) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(200, 45, 2000);

    //score ball 7
    f_forward(-30, 50, 500);
    liftMotors.spin(fwd, -100, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(0.75, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-60, 45);
    intakeMotors.spin(fwd, -100, pct);
    liftMotors.spin(fwd, 100, pct);
    f_forward(-50, 45);
    wait(0.5, sec);
    intakeMotors.stop();
    liftMotors.stop();

    //get ball 8
    leftMotors.spin(fwd, -25, pct);
    rightMotors.spin(fwd, 25, pct);
    while(inertialSensor.heading(deg) >= 104) wait(0.01, sec);
    driveMotors.stop(brake);

    intakeMotors.spin(fwd, 100, pct);
    f_forward(600, 45);
    wait(0.75, sec);
    intakeMotors.stop();
    f_forward(-50, 45);

    leftMotors.spin(fwd, 25, pct);
    rightMotors.spin(fwd, -25, pct);
    while(inertialSensor.heading(deg) <= 173) wait(0.01, sec);
    driveMotors.stop(brake);

    f_forward(100, 45, 1500);

    //score ball 8
    liftMotors.spin(fwd, -100, pct);
    intakeMotors.spin(fwd, 100, pct);
    wait(1, sec);
    liftMotors.stop();
    intakeMotors.stop();

    f_forward(-200, 45);
    //f_forward(100, 50, 1500, false);
  }
  else if(team) //blue autons
  {
    if(side) //right side
    {
      LCD.print("BLUE RIGHT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

    }
    else //left side
    {
      LCD.print("BLUE LEFT");
      LCD.render();

      f_forward(300);
      leftMotors.spin(fwd, -25, pct);
      rightMotors.spin(fwd, 25, pct);
      wait(0.5, sec);
      while(inertialSensor.heading(deg) >= 241) wait(0.01, sec);
      driveMotors.stop(brake);

      intakeMotors.spin(fwd, 100, pct);
      f_forward(300, 35, 2500);
      liftMotors.spin(fwd, -100, pct);
      f_forward(200, 35, 2500);
      f_forward(-50, 100);

      wait(1.4, sec);
      liftMotors.spin(fwd, 100, pct);
      wait(0.3, sec);
      liftMotors.spin(fwd, -100, pct);
      f_forward(35, 35);
      wait(1.1, sec);
      liftMotors.stop();

      f_forward(-200, 35);
      intakeMotors.stop();
    }
  }
  else //red autons
  {
    if(side) //right side
    {
      LCD.print("RED RIGHT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

    }
    else //left side
    {
      LCD.print("RED LEFT");
      LCD.render();

      //launch ball with hood
      liftMotors.spin(fwd, -100, pct);
      Task.sleep(500);
      liftMotors.stop();

    }
  }
}