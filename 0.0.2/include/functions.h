#include "vex.h"

using namespace vex;

void inertialDebug();
void inertialTurn(turnType turnDir = right, float deg = 90, int speed = 50);
int P(int currentPos, float kP = 0.5, int target = 158, int accuracy = 3);
void visionTurn(vision::signature sig, float kP = 0.5, int accuracy = 3);
bool charToBool(char str);
int PIDTurn(motor_group motor1, motor_group motor2, int target, int range, int accuracy, float kP, float kI, float kD, inertial sensor, int dT = 15, bool reversed = false);
int PID(motor_group motors, int target, int range, int accuracy, float kP, float kI, float kD, int sensorValue, int dT = 15, bool reversed = false);

void f_drivercontrol();
void f_autonomous();