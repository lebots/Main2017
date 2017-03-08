#ifndef UPDATES_H
#define UPDATES_H

void updateDriveMotors() {
	motor[FLDrive] = FLDriveVel;
	motor[BLDrive] = BLDriveVel;
	motor[FRDrive] = FRDriveVel;
	motor[BRDrive] = BRDriveVel;
}

void updateHugMotors() {
	motor[LHug] = hugVel;
}

void updateLiftMotors() {
	motor[L1Arm] = armVel;
	motor[L2Arm] = armVel;
	motor[R1Arm] = armVel;
	motor[R2Arm] = armVel;
}

void updateLockMotors() {
	motor[armLock] = armLockVel;
}
void updateMotors() {
	updateDriveMotors();
	updateHugMotors();
	updateLiftMotors();
	updateLockMotors();
}

void updateSensors() {
	armAngle = SensorValue[armAngleSensor];
	hugAngle = SensorValue[hugAngleSensor];
	ratchetAngle = SensorValue[ratchetAngleSensor];
}

void resetEncoders() {
	SensorValue[FLEncoderSensor] = 0;
	SensorValue[BLEncoderSensor] = 0;
	SensorValue[FREncoderSensor] = 0;
	SensorValue[BREncoderSensor] = 0;
}

#endif
