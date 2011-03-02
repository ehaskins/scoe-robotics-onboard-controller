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

bool attached;
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

	Serial.println("User init complete.");
}

/*
 * Called as fast as possible. Guaranteed to be called at least once
 * between every call to commLoop.
 */
void fastLoop(void) {
	ControlData control = communication.controlData;
	//Do fast loop stuff here.

	if (!communication.isConnected) {
		setOutputsEnabled(false);
	}
}

void setOutputsEnabled(bool enabled) {
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
 * Process control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
int commCounter;
int start = 0;
int position = 0;
int direction = 1;
int range = 40;
void commLoop(void) {
	ControlData control = communication.controlData;
	//Serial.println((int)communication.commandData.joysticks[1].axis[1]);
	//Serial.println("Slow loop: Implement me!");
	if (control.mode.getEnabled()) {
		setOutputsEnabled(true);
		if (control.mode.getAutonomous()) {
			left.write(-position);
			right.write(position);

			position += direction;
			if (position <= start - range || position >= start + range) {
				direction *= -1;
				//position = 0;
			}

		} else {
			int leftVal = control.joysticks[0].axis[1] - 128;
			int rightVal = control.joysticks[0].axis[4] - 128;

			//Deadband to remove the non-centered stick issues. 360 requires a big deadband.
			leftVal = deadband(leftVal, 25);
			rightVal = deadband(rightVal, 25);

			//Scale to range BoeBot servos respond.
			leftVal = leftVal * 40 / 127;
			rightVal = rightVal * 40 / 127;

			if(commCounter % 5 == 0){
				Serial.print("Left:");
				Serial.print(leftVal);
				Serial.print(" Right:");
				Serial.println(rightVal);
			}

			left.write(-leftVal);
			right.write(rightVal);
		}
	}
	else{
		setOutputsEnabled(false);
	}
	commCounter++;
}
int deadband(int value, int deadband){
	if (value < 127-deadband && value > -128+deadband){
		if (value > deadband){
			value -= deadband;
		}
		else if (value < -deadband){
			value += deadband;
		}
		else{
			value = 0;
		}
	}
	return value;
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
void fixedLoop(int delayed, int elapsed) {
	/*Serial.print("Fixed loop delayed ");
	 Serial.print(delayed);
	 Serial.println("ms.");*/
}
