/*
 * SpeedSensor.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

#include "Drivers.h"
#include "ISpeedSensor.h"
#include "IEncoder.h"
#include <WProgram.h>

class SpeedSensor : public ISpeedSensor {
private:
	bool m_enabled;

	IEncoder* m_pEncoder;

	long m_lastTimeStep;

public:
	SpeedSensor() :m_enabled(false), m_pEncoder(NULL) { m_lastTimeStep = millis(); }

	void init(IEncoder* encoder) {
		m_pEncoder = encoder;
	}
	void setEnabled(bool enable) {
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	float getSpeed() {
		// Get the number of ticks and the time.
		int numTicks = m_pEncoder->getTickCount();
		long thisTime = millis();

		// Reset the tick counter after fetching
		m_pEncoder->resetTickCount();

		// The speed in rotations/millisecond is:
		float rotsPerTimeStep = ((float)numTicks / (float)(thisTime - m_lastTimeStep));

		// Multiplying 0.5*PI feet per rotation and 1/1000 milliseconds per second, we get:
		float feetPerSecond = (rotsPerTimeStep * 3.141592f / 500.0f);

		// Store the time of this computation, and return.
		m_lastTimeStep = thisTime;
		return feetPerSecond;
	}
};

#endif /* SPEEDSENSOR_H_ */
