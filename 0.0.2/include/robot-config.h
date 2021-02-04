using namespace vex;

extern brain Brain;
extern brain::lcd LCD;
extern controller::lcd ControllerLCD;

extern competition Competition;
extern task Task;
extern color Color;

extern controller Controller;

extern motor frontLeftMotor;
extern motor frontRightMotor;
extern motor backLeftMotor;
extern motor backRightMotor;
extern motor backMotor;
extern motor frontMotor;

extern motor_group leftMotors;
extern motor_group rightMotors;
extern motor_group rMotors;
extern motor_group intakeMotors;

extern inertial inertialSensor;

extern drivetrain mainDrivetrain;

extern timer t1;

extern vision::signature SIG_1;
extern vision::signature SIG_2;
extern vision::signature SIG_3;
extern vision::signature SIG_4;
extern vision::signature SIG_5;
extern vision::signature SIG_6;
extern vision::signature SIG_7;
extern vision visionSensor;

void vexcodeInit(void);
void autonomous(void);
void drivercontrol(void);