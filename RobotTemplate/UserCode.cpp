/*
 * UserCode.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "UserCode.h"
#include <WProgram.h>
#include "FRCCommunication.h"
void fastLoop(void) {
	//Do fast loop stuff here.
}
void slowLoop(void) {
	//Process control data here.
	//In theory this code will run at 50hz whenever the robot is communicating with the DS.

	//Serial.println("Slow loop: Implement me!");
}
void userInit(void) {
	//Initialize user code, robot sensors, etc. here.

	Serial.println("User init complete.");
}
