#ifndef VAR_H
#define VAR_H

int LDriveVel = 0; // Velocity of left drive
int RDriveVel = 0; // Velocity of right drive
int hugVel = 0; // Velocity of hug
int armVel = 0; // Velocity of arm

int armAngle = 0; // Angle of the arm
int hugAngle = 0; // Angle of the hug
int ratchetAngle = 0; // Angle of ratchet

int hugTargetAngle	= 1300; // Target angle of hugger
int hugError 		= 0; // Hug angle error for PID
int hugIntegral 	= 0; // Hug integral for PID
int hugDeriv 		= 0; // Hug deriv for PID
int hugPrevError 	= 0; // Hug prev error for PID
float kHugP = 0.5;
float kHugI = 0.0;
float kHugD = 1.0;

int armTargetAngle	= 2700; // Target angle of arm
int armError 		= 0; // Arm angle error for PID
int armIntegral 	= 0; // Arm integral for PID
int armDeriv 		= 0; // Arm deriv for PID
int armPrevError 	= 0; // Arm prev error for PID
float kArmP = 0.9;
float kArmI = 0.0;
float kArmD = 0.0;

int leftDriveTargetAngle	= 0; // Encoder pos for left drive PID
int leftDriveError 		= 0; // Left Drive positional error for PID
int leftDriveIntegral 	= 0; // Left Drive integral for PID
int leftDriveDeriv 		= 0; // Left Drive deriv for PID
int leftDrivePrevError 	= 0; // Left Drive prev error for PID
float kLeftDriveP = 0.5;
float kLeftDriveI = 0.0;
float kLeftDriveD = 2.0;

int rightDriveTargetAngle	= 0; // Encoder pos for right drive PID
int rightDriveError 		= 0; // Right Drive positional error for PID
int rightDriveIntegral 		= 0; // Right Drive integral for PID
int rightDriveDeriv 		= 0; // Right Drive deriv for PID
int rightDrivePrevError 	= 0; // Right Drive prev error for PID
float kRightDriveP = 0.5;
float kRightDriveI = 0.0;
float kRightDriveD = 2.0;

float drivePIDMultiplier = 1.0;

int armLockVel = 0; // Velocity of locking motor for ratchet after climb

bool climbing = false;
bool wasClimbing = false;
bool armLocked = false;
bool armFineTune = false;
bool wasArmTuning = false;

#endif
