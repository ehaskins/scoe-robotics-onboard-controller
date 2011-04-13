/*
 * Motor.h
 *
 *  Created on: Apr 13, 2011
 *      Author: Nick
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Drivers.h"
#include "IDevice.h"
#include "IMotor.h"
#include <inttypes.h>
#include "../Utils.h"

class Motor : public IMotor {
private:
	int m_pwmPort;
	bool m_enabled;

	float m_idle;
	float m_minBound;
	float m_maxBound;

	bool m_inverted;

public:
	Motor()
	:m_pwmPort(NO_PORT), m_enabled(false), m_idle(0.0f), m_minBound(-1.0f), m_maxBound(1.0f), m_inverted(false) {}
	virtual ~Motor() {}

	void setIdleSpeed(float idle) {
		m_idle = idle;
	}

	void setInverted(bool invert) {
		m_inverted = invert;
	}

	void init(int port) {
		m_pwmPort = port;
		pinMode(m_pwmPort, OUTPUT);
		setSpeed(m_idle);
	}

	void setEnabled(bool enable) {
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	bool setBounds(float min, float max) {
		if (max < min) {
			return false;
		}
		m_minBound = min;
		m_maxBound = max;
		return true;
	}

	float getMinBound() const {
		return m_minBound;
	}

	float getMaxBound() const {
		return m_maxBound;
	}

	void setSpeed(float speed) {

		// Only set us to our idle speed if disabled.
		if (!m_enabled) {
			speed = m_idle;
		}

		// Constrain to the given bounds.
		speed = constrain(speed, m_minBound, m_maxBound);

		// X = speed, Y = 8-bit PWM.
		// X0 = m_minBound, X1 = m_maxBound
		// Y0 = 0.0f, Y1 = 255.0f

		/**
		 * So, the formula is:
		 * y = 0.0f + [(speed - m_minBound)*255.0f - (speed - m_minBound)*0.0f]/(m_maxBound - m_minBound)
		 * or
		 * y = ( (speed - m_minBound) * 255.0f ) / (m_maxBound - m_minBound).
		 */

		// Calculate the PWM output from the given speed.
		uint8_t output = (uint8_t)(((speed-m_minBound)*255.0f)/(m_maxBound-m_minBound));

		// Output the PWM signal.
		analogWrite(m_pwmPort, output);
	}
};

#endif /* MOTOR_H_ */
