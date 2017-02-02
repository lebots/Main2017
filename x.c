#pragma config(Sensor, in1,    armAngleSensor, sensorPotentiometer)
#pragma config(Sensor, in2,    hugAngleSensor, sensorPotentiometer)
#pragma config(Sensor, in3,    ratchetAngleSensor, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoderSensor, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoderSensor, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  auto3,          sensorDigitalIn)
#pragma config(Sensor, dgtl6,  auto1,          sensorDigitalIn)
#pragma config(Sensor, dgtl7,  auto2,          sensorDigitalIn)
#pragma config(Motor,  port1,           BRDrive,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FRDrive,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           L2Arm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           L3Arm,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           R1Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           R2Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           R3Arm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           FLDrive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          BLDrive,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "./joysticks.h"
#include "./var.h"

#define HUG_CLOSED 		3500
#define HUG_OPEN		2877
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

string autonMode = "ledAuto"; // preloadStraight, leftCube, rightCube, fastForward (rightCube has yet to be tested), ledAuto

void updateMotors() {

	motor[FLDrive] = FLDriveVel;
	motor[BLDrive] = BLDriveVel;
	motor[FRDrive] = FRDriveVel;
	motor[BRDrive] = BRDriveVel;

	//motor[LHug] = hugVel;

	//motor[L1Arm] = armVel;
	motor[L2Arm] = armVel;
	motor[L3Arm] = armVel;
	motor[R1Arm] = armVel;
	motor[R2Arm] = armVel;
	motor[R3Arm] = armVel;

	//motor[armLock] = armLockVel;
}

void updateSensors() {
	armAngle = SensorValue[armAngleSensor];
	hugAngle = SensorValue[hugAngleSensor];
	ratchetAngle = SensorValue[ratchetAngleSensor];
}

task unlockRatchet() {
	while (abs(SensorValue[ratchetAngleSensor] - RATCHET_LOCKED) <= RATCHET_DB) {
		//motor[armLock] = -50;
	}
	//motor[armLock] = 0;
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

		if (hugVel > 127)	hugVel = 127;
		if (hugVel < -127)	hugVel = -127;
		if (abs(hugVel) < 15) hugVel = 0;
		//motor[LHug] = hugVel;
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

		//motor[L1Arm] = armVel;
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
		//LDriveVel = (kLeftDriveP * leftDriveError) + (kLeftDriveI * leftDriveIntegral) + (kLeftDriveD * leftDriveDeriv);
		leftDrivePrevError = leftDriveError;

		rightDriveError = SensorValue[rightEncoderSensor] - rightDriveTargetAngle;
		rightDriveIntegral += rightDriveError;
		rightDriveDeriv = rightDrivePrevError - rightDriveError;
		//RDriveVel = (kRightDriveP * rightDriveError) + (kRightDriveI * rightDriveIntegral) + (kRightDriveD * rightDriveDeriv);
		rightDrivePrevError = rightDriveError;

		//if (LDriveVel > 127) LDriveVel = 127;
		//else if (LDriveVel < -127) LDriveVel = -127;
		//if (RDriveVel > 127) RDriveVel = 127;
		//else if (RDriveVel < -127) RDriveVel = -127;

		//motor[LDrive] = LDriveVel * drivePIDMultiplier;
		//motor[RDrive] = RDriveVel * drivePIDMultiplier;
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
	drivePIDMultiplier = 0.5;
	wait1Msec(100);
	drivePIDMultiplier = 0.7;
	wait1Msec(100);
	drivePIDMultiplier = 1;
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

task leftCubeAuto() {
	hugTargetAngle = hugAngle;
	armTargetAngle = ARM_DOWN;
	leftDriveTargetAngle = 0;
	rightDriveTargetAngle = 0;
	drivePIDMultiplier = 1.0;
	startTask(huggerPID);
	startTask(armPID);
	startTask(drivePostitionPID);
	leftDriveTargetAngle = 775;
	rightDriveTargetAngle = -775;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 310);
	resetTimer();
	hugTargetAngle = HUG_CLOSED;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30);
	waitUntil((abs(SensorValue[hugAngleSensor] - hugTargetAngle) < 350) || getTimer() > 3);
	wait1Msec(250);
	armTargetAngle = ARM_HIGH_FENCE - 100;
	waitUntil(abs(SensorValue[armAngleSensor] - armTargetAngle) < 30);
	wait1Msec(750);
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = -245;
	rightDriveTargetAngle = -245;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 50);
	wait1Msec(100);
	resetTimer();
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 950;
	rightDriveTargetAngle = -950;
	waitUntil((abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30) || getTimer() > 2.5);
	hugTargetAngle = HUG_MIDDLE;
}

task rightCubeAuto() {
	hugTargetAngle = hugAngle;
	armTargetAngle = ARM_DOWN;
	leftDriveTargetAngle = 0;
	rightDriveTargetAngle = 0;
	drivePIDMultiplier = 1.0;
	startTask(huggerPID);
	startTask(armPID);
	startTask(drivePostitionPID);
	leftDriveTargetAngle = 750;
	rightDriveTargetAngle = -750;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 275);
	resetTimer();
	hugTargetAngle = HUG_CLOSED;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30);
	waitUntil((abs(SensorValue[hugAngleSensor] - hugTargetAngle) < 350) || getTimer() > 3);
	wait1Msec(250);
	armTargetAngle = ARM_HIGH_FENCE - 100;
	waitUntil(abs(SensorValue[armAngleSensor] - armTargetAngle) < 30);
	wait1Msec(750);
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 245;
	rightDriveTargetAngle = 245;
	waitUntil(abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 50);
	wait1Msec(100);
	resetTimer();
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 950;
	rightDriveTargetAngle = -950;
	waitUntil((abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30) || getTimer() > 2.5);
	hugTargetAngle = HUG_MIDDLE;
}

task forwardAuto() {
	resetTimer();
	hugTargetAngle = HUG_MIDDLE;
	armTargetAngle = ARM_HIGH_FENCE;
	leftDriveTargetAngle = 1550;
	rightDriveTargetAngle = -1550;
	drivePIDMultiplier = 1.0;
	startTask(huggerPID);
	startTask(armPID);
	startTask(drivePostitionPID);
	waitUntil((abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30) || getTimer() > 2.5);
	wait1Msec(250);
	armTargetAngle = ARM_UP;
	resetTimer();
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 200;
	rightDriveTargetAngle = -200;
	waitUntil((abs(SensorValue[leftEncoderSensor] - leftDriveTargetAngle) < 30) || getTimer() > 1);
	SensorValue[leftEncoderSensor] = 0;
	SensorValue[rightEncoderSensor] = 0;
	leftDriveTargetAngle = 0;
	rightDriveTargetAngle = 0;
}

task autonomous() {
	pre_auton();
	updateSensors();
	/*if (autonMode == "preloadStraight") {
		startTask(preloadStraightAuto);
	} else if (autonMode == "leftCube") {
		startTask(leftCubeAuto);
	} else if (autonMode == "rightCube") {
		startTask(rightCubeAuto);
	} else if (autonMode == "fastForward") {
		startTask(forwardAuto);
	} else if (autonMode == "ledAuto") {
		startTask(ledAuto);
	}*/

	// UNTESTED:
	if (SensorValue[auto1] && !SensorValue[auto2] && SensorValue[auto3]) {
		startTask(forwardAuto);
	} else if (!SensorValue[auto1] && SensorValue[auto2] && SensorValue[auto3]) {
		startTask(leftCubeAuto);
	} else if (SensorValue[auto1] && SensorValue[auto2] && !SensorValue[auto3]) {
		startTask(rightCubeAuto);
	} else {
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
			armTargetAngle = ARM_CLIMB;
			hugTargetAngle = HUG_CLIMBPREP;
		}

		if (LDown) {
			armTargetAngle = ARM_LOW_FENCE;
			hugTargetAngle = HUG_MIDDLE;
		}

		if (LRight) {
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
			hugVel = -127;
			armLocked = true;
		} else if (!LRight && armLocked) {
			hugTargetAngle = hugAngle;
			armLocked = false;
		}

		if (getTimer() >= 1) {
			if (RUp){
				armLockVel = 50;
				armLocked = true;
			} else if (RDown) {
				armLockVel = -50;
			} else if (!LRight && armLocked) {
				hugTargetAngle = hugAngle;
			} else {
				armLockVel = 0;
				armLocked = false;
			}
		}


		/*
		* Drive code
		*/
		FLDriveVel = LY + LX + RX;
		BLDriveVel = LY - (LX * 0.7) + RX;
		FRDriveVel = LY - LX - RX;
		BRDriveVel = LY + (LX * 0.7) - RX;

		/*if (LLeft) {
			LDriveVel = 127;
			RDriveVel = 127;
		}*/

		//if (abs(LDriveVel) < 15) LDriveVel = 0;
		//if (abs(RDriveVel) < 15) RDriveVel = 0;

		updateMotors();
	}
}
