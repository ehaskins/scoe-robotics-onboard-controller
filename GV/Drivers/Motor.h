/*
 * Motor.h
 *
 *  Created on: Apr 13, 2011
 *      Author: Nick
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "IMotor.h"
#include <WProgram.h>
#include <Servo.h>

class Motor : public IMotor {
private:
	Servo m_servo;
	int m_pwmPort;
	bool m_enabled;

	int m_idle;
	int m_minBound;
	int m_maxBound;

	bool m_inverted;

public:
	Motor()
	:m_pwmPort(NO_PORT), m_enabled(false), m_idle(0), m_minBound(-128), m_maxBound(127), m_inverted(false) {}

	void setIdle(int idle) {
		m_idle = idle;
	}

	int getIdle() const {
		return m_idle;
	}

	void setInverted(bool invert) {
		m_inverted = invert;
	}

	void init(int port) {
		m_pwmPort = port;
		//pinMode(m_pwmPort, OUTPUT);
		setSpeed(m_idle);
	}

	void setEnabled(bool enable) {
		if (enable) {
			m_servo.attach(m_pwmPort);
		} else {
			m_servo.detach();
		}
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	bool setBounds(int min, int max) {
		if (max < min) {
			return false;
		}
		m_minBound = min;
		m_maxBound = max;
		return true;
	}

	int getMinBound() const {
		return m_minBound;
	}

	int getMaxBound() const {
		return m_maxBound;
	}

	void setSpeed(int speed) {

		// Only set us to our idle speed if disabled.
		if (!m_enabled) {
			speed = m_idle;
		}

		// Constrain to the given bounds.
		speed = constrain(speed, m_minBound, m_maxBound);

		// Convert from speed bounds to PWM duty cycle.
		int output = map(speed, m_minBound, m_maxBound, 0, 180);

		// Invert if necessary.
		if (m_inverted) {
			output = 180 - output;
		}

		// Output the PWM signal.
		m_servo.write(output);
	}
};

#endif /* MOTOR_H_ */
