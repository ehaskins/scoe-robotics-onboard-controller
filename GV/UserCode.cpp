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


/*
 * Guaranteed to be called after the following have been initialized:
 * Ethernet, configuration, serial, and FRCComms.
 *
 * Place any one time robot specific initialization code here.
 */
void UserRobot::userInit(void) {
	//Initialize user code, robot sensors, etc. here.

	start = 0;
	position = 0;
	direction = 1;
	range = 40;

	autoInitComplete = false;
	teleInitComplete = false;
	disabledInitComplete = false;

	Serial.println("User init complete.");
}

/*
 * Disabled and enables all outputs. Must be implemented or a disabled robot may behave irratically.
 */
void UserRobot::setOutputsEnabled(bool enabled) {
	if (enabled && !attached) {
		left.attach(8);
		right.attach(9);
		attached = true;
	} else if (!enabled && attached) {
		left.detach();
		right.detach();
		attached = false;
	}
}

/*
 * Perform any initialization needed before teleop mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::teleopInit(){

}
/*
 * Process teleop control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::teleopLoop(){
	Joystick stick = comm->controlData->joysticks[0];
	int leftVal = stick.axis[1] - 128;
	int rightVal = stick.axis[4] - 128;

	//Deadband to remove the non-centered stick issues. 360 controller requires a big deadband.
	leftVal = deadband(leftVal, 25);
	rightVal = deadband(rightVal, 25);

	//Scale to range BoeBot servos respond.
	leftVal = leftVal * 40 / 127;
	rightVal = rightVal * 40 / 127;

	if(teleopCounter % 5 == 0){
		Serial.print("Left:");
		Serial.print(leftVal);
		Serial.print(" Right:");
		Serial.println(rightVal);
	}

	left.write(-leftVal);
	right.write(rightVal);

	teleopCounter++;
}

/*
 * Perform any initialization needed before disabled mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::disabledInit(){

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

}


/*
 * Process autonomous control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::autonomousLoop(){
	left.write(-position);
	right.write(position);

	position += direction;
	if (position <= start - range || position >= start + range) {
		direction *= -1;
		//position = 0;
	}

	autonomousCounter++;
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
	/*Serial.print("Fixed loop delayed ");
	 Serial.print(delayed);
	 Serial.println("ms.");*/
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
