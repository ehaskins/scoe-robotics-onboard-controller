/*
 * UserCode.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "UserCode.h"
#include <WProgram.h>
#include "FRCComms\FRCCommunication.h"
#include <Servo.h>

Servo left;
Servo right;
/*
 * Guaranteed to be called after the following have been initialized:
 * Ethernet, configuration, serial, and FRCComms.
 *
 * Place any robot specific initialization code here.
 */
void userInit(void) {
	//Initialize user code, robot sensors, etc. here.

	left.attach(8);
	right.attach(9);
	Serial.println("User init complete.");
}

/*
 * Called as fast as possible. Guaranteed to be called at least once
 * between every call to commLoop.
 */
void fastLoop(void) {
	ControlData control = communication.controlData;
	//Do fast loop stuff here.
	if (!control.mode.getEnabled() || control.mode.getAutonomous()){
		left.write(127);
		right.write(127);
	}
}

/*
 * Process control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void commLoop(void) {
	ControlData control = communication.controlData;
	//Serial.println((int)communication.commandData.joysticks[1].axis[1]);
	//Serial.println("Slow loop: Implement me!");
	left.write(control.joysticks[0].axis[0]);
	right.write(control.joysticks[1].axis[0]);
}

/*
 * Will be called at the frequency specified in UserConstants.h.
 * Guaranteed to be accurate over time, but inaccurate in the short term.
 *
 * The delayed argument is the number of milliseconds past the seceduled execution
 * time the loop is being called.
 *
 * The elapsed argument is the number of milliseconds since the last execution.
 */
void fixedLoop(int delayed, int elapsed){
	/*Serial.print("Fixed loop delayed ");
	Serial.print(delayed);
	Serial.println("ms.");*/
}
