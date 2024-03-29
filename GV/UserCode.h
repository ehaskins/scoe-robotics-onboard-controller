/*
 * UserCode.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef USERCODE_H_
#define USERCODE_H_
#include <Servo.h>
#include <FrcComms\Configuration.h>
#include <FrcComms\FRCCommunication.h>
#include "Drivers\Drivers.h"

//Declared and initialized in main.
class UserRobot
{
private:
	bool autoInitComplete;
	bool teleInitComplete;
	bool disabledInitComplete;

	bool attached;
	Configuration *config;
	FRCCommunication *comm;

public:
	void fastLoop(void);
	void commLoop(void);

	void teleopInit(void);
	void teleopLoop(void);
	void disabledInit(void);
	void disabledLoop(void);
	void autonomousInit(void);
	void autonomousLoop(void);
	void fixedLoop(int delayed, int elapsed);
	void userInit(void);
	void setOutputsEnabled(bool enabled);
};

#endif /* USERCODE_H_ */
