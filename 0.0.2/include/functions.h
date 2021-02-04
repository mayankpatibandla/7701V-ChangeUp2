#include "vex.h"

using namespace vex;

void inertialDebug();
int P(int currentPos, float kP = 0.5, int target = 158, int accuracy = 3);
void inertialTurn(int target, turnType turnDir, int speed, bool c);
void pInertialTurn(int target = 90, float kP = 0.5, int accuracy = 3);
void pVisionTurn(vision::signature sig, float kP = 0.5, int accuracy = 3);
void visionTurn(vision::signature sig, int accuracy = 3, int speed = 10);
void f_forward(int rots = 360, int speed = 50, int timeout = 0, bool wait = true);
bool charToBool(char str);
int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, float kP, float kI, float kD, inertial sensor, int dT = 15, bool reversed = false);
int PID(motor_group motors, int target, int range, int accuracy, float kP, float kI, float kD, int sensorValue, int dT = 15, bool reversed = false);

void f_drivercontrol();
void f_autonomous();
void f_autonomous1();