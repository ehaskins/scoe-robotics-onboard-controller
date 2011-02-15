/*
 * RobotStatusLight.h
 *
 *  Created on: Feb 15, 2011
 *      Author: EHaskins
 */

#ifndef ROBOTSTATUSLIGHT_H_
#define ROBOTSTATUSLIGHT_H_

#include "Mode.h"

struct RobotStatusLight {
public:
	void init(int);
	void update(bool connected, Mode mode);

	bool currentState;
	bool packetDropped;
	unsigned long lastStateChangeTime;
	int ledPin;
	unsigned int onPeriod;
	unsigned int offPeriod;
};

#endif /* ROBOTSTATUSLIGHT_H_ */
