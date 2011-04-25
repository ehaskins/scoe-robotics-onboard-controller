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

	comm = FRCCommunication::getInstance();
	Serial.println("User init complete.");
}

/*
 * Disabled and enables all outputs. Must be implemented or a disabled robot may behave irratically.
 */
void UserRobot::setOutputsEnabled(bool enabled) {
	if (enabled && !attached) {
		nw.attach(8);
		ne.attach(9);
		sw.attach(10);
		se.attach(11);
		pan.attach(12);
		tilt.attach(13);
		attached = true;
	} else if (!enabled && attached) {
		nw.detach();
		ne.detach();
		sw.detach();
		se.detach();
		pan.detach();
		tilt.detach();
		attached = false;
	}
}

/*
 * Perform any initialization needed before teleop mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::teleopInit(){
	Serial.println("Entering tele-op");
}
/*
 * Process teleop control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::teleopLoop(){
	Joystick stick = comm->controlData->joysticks[0];

	int y = stick.axis[1];
	int x = stick.axis[2];
	int z = stick.axis[0];
	if (teleopCounter % 25 == 0)
	{
		Serial.println(z);
		Serial.println(y);
		Serial.println(x);
	}
	int panVal = position; //= stick.axis[3];
	position += 1;
	if (position > 127)
		position = -128;
	int tiltVal = stick.axis[4];

	int nwVal = y + z + x;
	int neVal = y - z - x;
	int swVal = y + z - x;
	int seVal = y - z + x;
/*
	nw.write(limit(nwVal, -128, 127));
	ne.write(limit(neVal, -128, 127));
	sw.write(limit(swVal, -128, 127));
	se.write(limit(seVal, -128, 127));
	pan.write(panVal);
	tilt.write(tiltVal);*/
	teleopCounter++;
}



/*
 * Perform any initialization needed before disabled mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::disabledInit(){
	Serial.println("Entering disabled");
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
	Serial.println("Entering autonomous");
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
	Mode mode = comm->controlData->mode;
	//Serial.println((int)mode.data.data);
	if (mode.getEnabled()) {
		//setOutputsEnabled(true);
		if (mode.getAutonomous()) {
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
