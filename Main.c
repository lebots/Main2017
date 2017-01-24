#pragma config(Sensor, in1,    armAngleSensor, sensorPotentiometer)
#pragma config(Sensor, in2,    hugAngleSensor, sensorPotentiometer)
#pragma config(Sensor, in3,    ratchetAngleSensor, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoderSensor, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoderSensor, sensorQuadEncoder)
#pragma config(Motor,  port1,           LHug,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           L1Arm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           L2Arm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           L3Arm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           R1Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           R2Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           R3Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          armLock,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "C:/Users/Cameron/Documents/LebotsCode/Main2017/joysticks.h"

#define HUG_CLOSED 		3400
#define HUG_OPEN		900
#define HUG_MIDDLE 		2050
#define HUG_CLIMBPREP	915
#define ARM_UP			950
#define ARM_CLIMB		1400
#define ARM_DOWN		2800
#define ARM_HIGH_FENCE	1200
#define ARM_LOW_FENCE	1405
#define RATCHET_LOCKED	1100
#define RATCHET_DB		600

#define TILE_LENGTH_FOR_DRIVE	660

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

string autonMode = "preloadStraight";

void updateMotors() {

	motor[LDrive] = LDriveVel;
	motor[RDrive] = RDriveVel;

	motor[LHug] = hugVel;
	//motor[RHug] = hugVel;

	motor[L1Arm] = armVel;
	motor[L2Arm] = armVel;
	motor[L3Arm] = armVel;
	motor[R1Arm] = armVel;
	motor[R2Arm] = armVel;
	motor[R3Arm] = armVel;

	motor[armLock] = armLockVel;
}

void updateSensors() {
	armAngle = SensorValue[armAngleSensor];
	hugAngle = SensorValue[hugAngleSensor];
	ratchetAngle = SensorValue[ratchetAngleSensor];
}

task unlockRatchet() {
	while (abs(SensorValue[ratchetAngleSensor] - RATCHET_LOCKED) <= RATCHET_DB) {
		motor[armLock] = -50;
	}
	motor[armLock] = 0;
}

void pre_auton() {
	bStopTasksBetweenModes = true;
	updateSensors();
	resetTimer();
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;

	startTask(unlockRatchet);


	armTargetAngle = armAngle;
	hugTargetAngle = hugAngle;
}

task huggerPID() {
	while (true) {
		updateSensors();
		hugError = hugAngle - hugTargetAngle;
		hugIntegral += hugError;
		hugDeriv = hugPrevError - hugError;
		hugVel = (kHugP * hugError) + (0.0 * hugIntegral) + (1.0 * hugDeriv);
		hugPrevError = hugError;

		if (hugVel > 100)	hugVel = 100;
		if (hugVel < -100)	hugVel = -100;
		if (abs(hugVel) < 15) hugVel = 0;
		//motor[RHug] = hugVel;
		motor[LHug] = hugVel;
	}
}

task armPID() {
	while (true) {
		updateSensors();
		armError = -(armTargetAngle - armAngle);
		armIntegral += armError;
		armDeriv = armPrevError - armError;
		armVel = (kArmP * armError) + (kArmI * armIntegral) + (kArmD * armDeriv);
		armPrevError = armError;
		if (armVel < -31) armVel = 31 * (armVel/127) * (-armVel/127);

		if (armTargetAngle == 925 && armError < 50) armVel = 20;
		if (abs(armVel) < 20) armVel = 0;

		motor[L1Arm] = armVel;
		motor[L2Arm] = armVel;
		motor[L3Arm] = armVel;
		motor[R1Arm] = armVel;
		motor[R2Arm] = armVel;
		motor[R3Arm] = armVel;
	}
}

task drivePostitionPID() {
	while (true) {
		leftDriveError = leftDriveTargetAngle - SensorValue[leftEncoderSensor];
		leftDriveIntegral += leftDriveError;
		leftDriveDeriv = leftDrivePrevError - leftDriveError;
		LDriveVel = (kLeftDriveP * leftDriveError) + (kLeftDriveI * leftDriveIntegral) + (kLeftDriveD * leftDriveDeriv);
		leftDrivePrevError = leftDriveError;

		rightDriveError = SensorValue[rightEncoderSensor] - rightDriveTargetAngle;
		rightDriveIntegral += rightDriveError;
		rightDriveDeriv = rightDrivePrevError - rightDriveError;
		RDriveVel = (kRightDriveP * rightDriveError) + (kRightDriveI * rightDriveIntegral) + (kRightDriveD * rightDriveDeriv);
		rightDrivePrevError = rightDriveError;

		if (LDriveVel > 127) LDriveVel = 127;
		else if (LDriveVel < -127) LDriveVel = -127;
		if (RDriveVel > 127) RDriveVel = 127;
		else if (RDriveVel < -127) RDriveVel = -127;

		motor[LDrive] = LDriveVel * drivePIDMultiplier;
		motor[RDrive] = RDriveVel * drivePIDMultiplier;
	}
}

task preloadStraightAuto() {
	hugTargetAngle = HUG_CLOSED;
	armTargetAngle = ARM_DOWN;
	leftDriveTargetAngle = 0;
	rightDriveTargetAngle = 0;
	drivePIDMultiplier = 0.3;
	startTask(huggerPID);
	startTask(armPID);
	startTask(drivePostitionPID);
	waitUntil(abs(SensorValue[hugAngleSensor] - hugTargetAngle) < 50);
	armTargetAngle = ARM_UP;
	leftDriveTargetAngle = 1550;
	rightDriveTargetAngle = -1550;
	waitUntil(abs(SensorValue[armAngleSensor] - armTargetAngle) < 30);
	wait1Msec(500);
	drivePIDMultiplier = 1.0;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30);
	hugTargetAngle = HUG_MIDDLE;
	waitUntil(abs(SensorValue[hugAngleSensor] - hugTargetAngle) < 50);
	wait1Msec(500);
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = -500;
	rightDriveTargetAngle = 500;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30);
	armTargetAngle += 250;
	waitUntil(abs(SensorValue[armAngleSensor] - armTargetAngle) < 30);
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 500;
	rightDriveTargetAngle = -500;
}

task autonomous() {
	pre_auton();
	updateSensors();
	if (autonMode == "preloadStraight") {
		startTask(preloadStraightAuto);
	}
}


task usercontrol() {
	pre_auton();
	while (true) {

		updateJoysticks();
		updateSensors();


		/*
		* Arm Code :/
		*/
		if (LLeft) {
			armVel = -127;
			climbing = true;
		} else {
			climbing = false;
		}

		if (LBUp)	armTargetAngle = ARM_UP;
		if (LBDown)	armTargetAngle = ARM_DOWN;

		if (LUp) {
			armTargetAngle = ARM_CLIMB
			hugTargetAngle = HUG_CLIMBPREP;
		}

		if (LDown) {
			armTargetAngle = ARM_LOW_FENCE;
			hugTargetAngle = HUG_MIDDLE;
		}

		if (RLeft) {
			armTargetAngle = ARM_HIGH_FENCE;
			hugTargetAngle = HUG_MIDDLE;
		}

		if ((!climbing && wasClimbing) || (!armFineTune && wasArmTuning)) {
			armTargetAngle = armAngle;
		}

		if (!climbing && !armFineTune && !(hugTargetAngle < 850 && armTargetAngle < 1100)) {
			armError = armAngle - armTargetAngle;
			armIntegral += armError;
			armDeriv = armPrevError - armError;
			armVel = (kArmP * armError) + (kArmI * armIntegral) + (kArmD * armDeriv);
			armPrevError = armError;
			if (armVel < -31) armVel = 31 * (armVel/127) * (-armVel/127);
		} else if (hugTargetAngle <= 850) {
			armVel = 0;
		}

		if (armTargetAngle == ARM_UP && armError < 50 && hugTargetAngle > 850) armVel = 20;
		if (abs(armVel) < 20) armVel = 0;

		wasClimbing = climbing;
		wasArmTuning = armFineTune;


		/*
		* Hug code :)
		*/
		if (RRight)		hugTargetAngle = HUG_MIDDLE;
		if (RBDown)		hugTargetAngle = 2877;

		if (!climbing) {
			hugError = hugAngle - hugTargetAngle;
			hugIntegral += hugError;
			hugDeriv = hugPrevError - hugError;
			hugVel = (kHugP * hugError) + (kHugI * hugIntegral) + (kHugD * hugDeriv);
			hugPrevError = hugError;

			if (abs(hugVel) < 20) hugVel = 0;
		}

		if (RBUp){
			hugVel = -50;
			armLocked = true;
		} else if (!RLeft && armLocked) {
			hugTargetAngle = hugAngle;
			armLocked = false;
		}

		if (getTimer() >= 1) {
			if (RUp){
				armLockVel = 50;
				armLocked = true;
			} else if (RDown) {
				armLockVel = -50;
			} else if (!RLeft && armLocked) {
				hugTargetAngle = hugAngle;
			} else {
				armLockVel = 0;
				armLocked = false;
			}
		}


		/*
		* Drive code
		*/
		LDriveVel = LY;
		RDriveVel = RY;

		if (LLeft) {
			LDriveVel = 127;
			RDriveVel = 127;
		}

		if (abs(LDriveVel) < 15) LDriveVel = 0;
		if (abs(RDriveVel) < 15) RDriveVel = 0;

		updateMotors();
	}
}
