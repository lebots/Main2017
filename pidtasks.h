#ifndef PIDTASKS_H
#define PIDTASKS_H

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
		motor[R1Arm] = armVel;
		motor[R2Arm] = armVel;
	}
}

task drivePostitionPID() {
	while (true) {
		FLDriveIntegral += FLDriveError;
		FLDriveDeriv = FLDrivePrevError - FLDriveError;
		FLDriveVel = (kFLDriveP * FLDriveError) + (kFLDriveI * FLDriveIntegral) + (kFLDriveD * FLDriveDeriv);
		FLDrivePrevError = FLDriveError;

		BLDriveIntegral += BLDriveError;
		BLDriveDeriv = BLDrivePrevError - BLDriveError;
		BLDriveVel = (kBLDriveP * BLDriveError) + (kBLDriveI * BLDriveIntegral) + (kBLDriveD * BLDriveDeriv);
		BLDrivePrevError = BLDriveError;

		FRDriveError = SensorValue[FREncoderSensor] - FRDriveTargetAngle;
		FRDriveIntegral += FRDriveError;
		FRDriveDeriv = FRDrivePrevError - FRDriveError;
		FRDriveVel = (kFRDriveP * FRDriveError) + (kFRDriveI * FRDriveIntegral) + (kFRDriveD * FRDriveDeriv);
		FRDrivePrevError = FRDriveError;

		BRDriveError = SensorValue[BREncoderSensor] - BRDriveTargetAngle;
		BRDriveIntegral += BRDriveError;
		BRDriveDeriv = BRDrivePrevError - BRDriveError;
		BRDriveVel = (kBRDriveP * BRDriveError) + (kBRDriveI * BRDriveIntegral) + (kBRDriveD * BRDriveDeriv);
		BRDrivePrevError = BRDriveError;

		FLDriveVel *= drivePIDMultiplier;
		BLDriveVel *= drivePIDMultiplier;
		FRDriveVel *= drivePIDMultiplier;
		BRDriveVel *= drivePIDMultiplier;

		if (FLDriveVel > 127) FLDriveVel = 127;
		else if (FLDriveVel < -127) FLDriveVel = -127;
		if (BLDriveVel > 127) BLDriveVel = 127;
		else if (BLDriveVel < -127) BLDriveVel = -127;
		if (FRDriveVel > 127) FRDriveVel = 127;
		else if (FRDriveVel < -127) FRDriveVel = -127;
		if (BRDriveVel > 127) BRDriveVel = 127;
		else if (BRDriveVel < -127) BRDriveVel = -127;

		motor[FLDrive] = FLDriveVel;
		motor[BLDrive] = BLDriveVel;
		motor[FRDrive] = FRDriveVel;
		motor[BRDrive] = BRDriveVel;
	}
}

#endif
