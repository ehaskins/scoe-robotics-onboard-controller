/*
 * UserCode.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "UserCode.h"
#include <WProgram.h>
#include <FrcComms\FRCCommunication.h>
#include <Servo.h>
#include "Utils.h"
#include "UserConstants.h"

// Drive motors and PID controllers.
static Motor leftMotor;
static Motor rightMotor;
static Motor rearMotor;

static LimitMotor leftLimitMotor;
static LimitMotor rightLimitMotor;
static LimitMotor rearLimitMotor;

// Drive encoders.
//	static Encoder leftEncoder;
//	static Encoder rightEncoder;
//	static Encoder rearEncoder;

// Drive speed sensors.
//	static SpeedSensor leftSensor;
//	static SpeedSensor rightSensor;
//	static SpeedSensor rearSensor;

// Drive system.
static KiwiDrive kiwidrive;

/*
 * Guaranteed to be called after the following have been initialized:
 * Ethernet, configuration, serial, and FRCComms.
 *
 * Place any one time robot specific initialization code here.
 */
void UserRobot::userInit(void) {
	//Initialize user code, robot sensors, etc. here.
	autoInitComplete = false;
	teleInitComplete = false;
	disabledInitComplete = false;

	// Initialize the robot parts.

	// 137"/s max speed, approx., with gearbox and CIM motors.
	leftMotor.setBounds(-137, 137);
	rightMotor.setBounds(-137, 137);
	rearMotor.setBounds(-137, 137);

	leftMotor.setInverted(USER_INVERT_LEFT_MOTOR);
	rightMotor.setInverted(USER_INVERT_RIGHT_MOTOR);
	rearMotor.setInverted(USER_INVERT_REAR_MOTOR);

	leftMotor.setIdle(0);
	rightMotor.setIdle(0);
	rearMotor.setIdle(0);

	leftMotor.init(PIN_LEFT_MOTOR);
	rightMotor.init(PIN_RIGHT_MOTOR);
	rearMotor.init(PIN_REAR_MOTOR);

	leftLimitMotor.init(&leftMotor, USER_MAX_SHIFT);
	rightLimitMotor.init(&rightMotor, USER_MAX_SHIFT);
	rearLimitMotor.init(&rearMotor, USER_MAX_SHIFT);

	kiwidrive.init((IMotor*)&leftLimitMotor, (IMotor*)&rightLimitMotor, (IMotor*)&rearLimitMotor);
	kiwidrive.invertForward(USER_INVERT_FORWARD);
	kiwidrive.invertStrafe(USER_INVERT_STRAFE);
	kiwidrive.invertYaw(USER_INVERT_YAW);
}

/*
 * Disabled and enables all outputs. Must be implemented or a disabled robot may behave irratically.
 */
void UserRobot::setOutputsEnabled(bool enabled) {
	if (enabled && !attached) {
		kiwidrive.setEnabled(true);
		attached = true;
	} else if (!enabled && attached) {
		kiwidrive.setEnabled(false);
		attached = false;
	}
}

/*
 * Perform any initialization needed before teleop mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::teleopInit(){
	setOutputsEnabled(true);
}

enum XboxJoysticks {
	LEFT_X = 0,
	LEFT_Y = 1,
	LR_ANALOG = 2,
	RIGHT_X = 3,
	RIGHT_Y = 4
};


/*
 * Process teleop control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::teleopLoop(){
	// Get the control stick.
	Joystick stick = comm->controlData->joysticks[0];

	// Re-center the control axes.
	int forward = stick.axis[LEFT_Y] - 128;
	int strafe = stick.axis[LEFT_X] - 128;
	int rotate = stick.axis[RIGHT_X] - 128;

	// Drive the damn robot.
	int controls[] = { forward, strafe, rotate };
	kiwidrive.driveSystem(controls);
}

/*
 * Perform any initialization needed before disabled mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::disabledInit(){
	setOutputsEnabled(false);
}
/*
 * Process disabled control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::disabledLoop(){

}

/*
 * Perform any initialization needed before autonomous mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::autonomousInit(){
	setOutputsEnabled(false);
}


/*
 * Process autonomous control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::autonomousLoop(){

}

/*
 * Will be called at the frequency specified in UserConstants.h.
 * Guaranteed to be accurate over time, but inaccurate in the short term.
 *
 * The delayed argument is the number of milliseconds past the scheduled execution
 * time the loop is being called.
 *
 * The elapsed argument is the number of milliseconds since the last execution.
 */
void UserRobot::fixedLoop(int delayed, int elapsed) {

}

/*
 * Called as fast as possible. Guaranteed to be called at least once
 * between every call to commLoop.
 */
void UserRobot::fastLoop(void) {
	ControlData *control = comm->controlData;
	//Do fast loop stuff here.

	if (!comm->isConnected) {
		setOutputsEnabled(false);
	}
}



/*
 * Processes control data here, and calls the appropriate init and/or loop functions.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::commLoop(void) {
	//Serial.println((int)communication.commandData.joysticks[1].axis[1]);
	//Serial.println("Slow loop: Implement me!");
	if (comm->controlData->mode.getEnabled()) {
		setOutputsEnabled(true);
		if (comm->controlData->mode.getAutonomous()) {
			if (!autoInitComplete){
				autonomousInit();
				autoInitComplete = true;
				teleInitComplete = false;
				disabledInitComplete = false;
			}
			autonomousLoop();
		} else {
			if (!teleInitComplete){
				teleopInit();
				autoInitComplete = false;
				teleInitComplete = true;
				disabledInitComplete = false;
			}
			teleopLoop();
		}
	}
	else{
		setOutputsEnabled(false);
		if (!disabledInitComplete){
			disabledInit();
			autoInitComplete = false;
			teleInitComplete = false;
			disabledInitComplete = true;
		}
		disabledLoop();
	}
}
