/*
 * RobotStatusLight.h
 *
 *  Created on: Feb 15, 2011
 *      Author: EHaskins
 */

#ifndef ROBOTSTATUSLIGHT_H_
#define ROBOTSTATUSLIGHT_H_

#include "Mode.h"
#include "Period.h"

static const int NUM_PERIODS = 4;
struct RobotStatusLight {
public:
	void init(int);
	void update(bool connected,bool configMode,  Mode mode);

	int period;
	bool packetDropped;
	unsigned long lastStateChangeTime;
	int ledPin;
	Period periods[NUM_PERIODS];
};

#endif /* ROBOTSTATUSLIGHT_H_ */
