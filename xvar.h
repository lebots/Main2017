#ifndef XVAR_H
#define XVAR_H

int FLDriveVel = 0; // Velocity of front left drive
int BLDriveVel = 0; // Velocity of back left drive
int FRDriveVel = 0; // Velocity of front right drive
int BRDriveVel = 0; // Velocity of back right drive
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

int FLDriveTargetAngle	= 0; // Encoder pos for left drive PID
int FLDriveError 		= 0; // Front Left Drive positional error for PID
int FLDriveIntegral 	= 0; // Front Left Drive integral for PID
int FLDriveDeriv 		= 0; // Front Left Drive deriv for PID
int FLDrivePrevError 	= 0; // Front Left Drive prev error for PID
float kFLDriveP = 0.5;
float kFLDriveI = 0.0;
float kFLDriveD = 2.0;

int BLDriveTargetAngle	= 0; // Encoder pos for front left drive PID
int BLDriveError 		= 0; // Back Left Drive positional error for PID
int BLDriveIntegral 	= 0; // Back Left Drive integral for PID
int BLDriveDeriv 		= 0; // Back Left Drive deriv for PID
int BLDrivePrevError 	= 0; // Back Left Drive prev error for PID
float kBLDriveP = 0.5;
float kBLDriveI = 0.0;
float kBLDriveD = 2.0;

int FRDriveTargetAngle	= 0; // Encoder pos for FR drive PID
int FRDriveError 		= 0; // FR Drive positional error for PID
int FRDriveIntegral 	= 0; // FR Drive integral for PID
int FRDriveDeriv 		= 0; // FR Drive deriv for PID
int FRDrivePrevError 	= 0; // FR Drive prev error for PID
float kFRDriveP = 0.5;
float kFRDriveI = 0.0;
float kFRDriveD = 2.0;

int BRDriveTargetAngle	= 0; // Encoder pos for BR drive PID
int BRDriveError 		= 0; // BR Drive positional error for PID
int BRDriveIntegral		= 0; // BR Drive integral for PID
int BRDriveDeriv 		= 0; // BR Drive deriv for PID
int BRDrivePrevError 	= 0; // BR Drive prev error for PID
float kBRDriveP = 0.5;
float kBRDriveI = 0.0;
float kBRDriveD = 2.0;

float drivePIDMultiplier = 1.0;

int armLockVel = 0; // Velocity of locking motor for ratchet after climb

bool climbing = false;
bool wasClimbing = false;
bool armLocked = false;
bool armFineTune = false;
bool wasArmTuning = false;

#endif
