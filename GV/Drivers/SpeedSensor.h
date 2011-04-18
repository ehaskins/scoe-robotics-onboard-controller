/*
 * SpeedSensor.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

#include "ISpeedSensor.h"
#include "IEncoder.h"

class SpeedSensor : public ISpeedSensor {
private:
	IEncoder* m_pEncoder;

	int m_diameter;
	long m_lastTimeStep;

public:
	SpeedSensor()
	:m_pEncoder(NULL), m_diameter(0), m_lastTimeStep(0) {}

	void setWheelDiameter(int diameter) {
		m_diameter = diameter;
	}

	int getWheelDiameter() const {
		return m_diameter;
	}

	void init(int port) {}

	void init(IEncoder* encoder, int diameter) {
		m_pEncoder = encoder;
		m_diameter = diameter;
		m_lastTimeStep = millis();
	}

	void setEnabled(bool enable) {
		m_pEncoder->setEnabled(enable);
	}

	bool isEnabled() const {
		return m_pEncoder->isEnabled();
	}

	int getSpeed() {
		// Get the number of ticks and the time.
		int numTicks = m_pEncoder->getTickCount();
		long thisTime = millis();
		long timeStep = thisTime - m_lastTimeStep;
  
		// Reset the tick counter after fetching.
		m_pEncoder->resetTickCount();

		// one tick is n percent of the wheel.
		float wheelPercent = (float)numTicks / (float)m_pEncoder->getNumTicksPerCycle();
		
		// n percent moves me d far
		float distance = wheelPercent * PI * (float)m_diameter;

		// Store the time of this computation, and return.
		m_lastTimeStep = thisTime;

		// Upscale to get the approximate units per second.
		return (int)((distance * 1000.0f) / (float)timeStep);
	}
};

#endif /* SPEEDSENSOR_H_ */
