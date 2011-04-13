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
