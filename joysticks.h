#ifndef JOYSTICKS_H
#define JOYSTICKS_H

int LY = 0; // Left Y-axis Joystick
int LX = 0; // Left X-axis Joystick
int RY = 0; // Right Y-axis Joystick
int RX = 0; // Right X-axis Joystick
int LUp		= false; // Left D-Pad Up Button
int LDown 	= false; // Left D-Pad Down Button
int LLeft 	= false; // Left D-Pad Left Button
int LRight 	= false; // Left D-Pad Right Button
int LBUp	= false; // Left Top Bumper
int LBDown 	= false; // Left Bottom Bumper
int RUp		= false; // Right D-Pad Up Button
int RDown 	= false; // Right D-Pad Down Button
int RLeft 	= false; // Right D-Pad Left Button
int RRight 	= false; // Right D-Pad Right Button
int RBUp	= false; // Right Top Bumper
int RBDown 	= false; // Right Bottom Bumper

int LY_s = 0; // Left Y-axis Joystick on the secondary controller
int LX_s = 0; // Left X-axis Joystick on the secondary controller
int RY_s = 0; // Right Y-axis Joystick on the secondary controller
int RX_s = 0; // Right X-axis Joystick on the secondary controller
int LUp_s		= false; // Left D-Pad Up Button on the secondary controller
int LDown_s 	= false; // Left D-Pad Down Button on the secondary controller
int LLeft_s 	= false; // Left D-Pad Left Button on the secondary controller
int LRight_s 	= false; // Left D-Pad Right Button on the secondary controller
int LBUp_s		= false; // Left Top Bumper on the secondary controller
int LBDown_s 	= false; // Left Bottom Bumper on the secondary controller
int RUp_s		= false; // Right D-Pad Up Button on the secondary controller
int RDown_s 	= false; // Right D-Pad Down Button on the secondary controller
int RLeft_s 	= false; // Right D-Pad Left Button on the secondary controller
int RRight_s 	= false; // Right D-Pad Right Button on the secondary controller
int RBUp_s		= false; // Right Top Bumper on the secondary controller
int RBDown_s 	= false; // Right Bottom Bumper on the secondary controller

void updateJoysticks() {
	LY = vexRT[Ch3];
	LX = vexRT[Ch4];
	RY = vexRT[Ch2];
	RX = vexRT[Ch1];
	LUp		= vexRT[Btn7U];
	LDown   = vexRT[Btn7D];
	LLeft   = vexRT[Btn7L];
	LRight  = vexRT[Btn7R];
	LBUp	= vexRT[Btn5U];
	LBDown  = vexRT[Btn5D];
	RUp		= vexRT[Btn8U];
	RDown   = vexRT[Btn8D];
	RLeft   = vexRT[Btn8L];
	RRight  = vexRT[Btn8R];
	RBUp	= vexRT[Btn6U];
	RBDown  = vexRT[Btn6D];

	LY_s  		= vexRT[Ch3Xmtr2];
	LX_s 		= vexRT[Ch4Xmtr2];
	RY_s 		= vexRT[Ch2Xmtr2];
	RX_s 		= vexRT[Ch1Xmtr2];
	LUp_s 		= vexRT[Btn7UXmtr2];
	LDown_s 	= vexRT[Btn7DXmtr2];
	LLeft_s 	= vexRT[Btn7LXmtr2];
	LRight_s 	= vexRT[Btn7RXmtr2];
	LBUp_s 		= vexRT[Btn5UXmtr2];
	LBDown_s 	= vexRT[Btn5DXmtr2];
	RUp_s 		= vexRT[Btn8UXmtr2];
	RDown_s 	= vexRT[Btn8DXmtr2];
	RLeft_s 	= vexRT[Btn8LXmtr2];
	RRight_s 	= vexRT[Btn8RXmtr2];
	RBUp_s 		= vexRT[Btn6UXmtr2];
	RBDown_s 	= vexRT[Btn6DXmtr2];
}
#endif
