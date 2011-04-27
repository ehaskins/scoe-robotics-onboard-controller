/*
 * ServoMotor.h
 *
 *  Created on: Apr 26, 2011
 *      Author: Nick
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "IMotor.h"
#include <Servo.h>
#include <WProgram.h>

class ServoMotor : public IMotor {
private:
	int m_servoPort;
	Servo m_servo;

	int m_idle;
	int m_minBound;
	int m_maxBound;

public:
	ServoMotor() :m_servoPort(NO_PORT), m_idle(0), m_minBound(-128), m_maxBound(127) {}

	void init(int port) {
		m_servoPort = port;
		pinMode(m_servoPort, OUTPUT);
	}

	void setEnabled(bool enable) {
		if (enable && !isEnabled()) {
			m_servo.attach(m_servoPort, m_minBound, m_maxBound);
		} else if (!enable && isEnabled()) {
			m_servo.detach();
		}
	}

	bool isEnabled() const {
		return m_servo.attached();
	}

	bool setBounds(int min, int max) {
		if (max < min) {
		  return false;
		}
		m_minBound = min;
		m_maxBound = max;
		if (isEnabled()) {
			m_servo.detach();
			m_servo.attach(m_servoPort, m_minBound, m_maxBound);
		}
		return true;
	}

	int getMinBound() const {
		return m_minBound;
	}

	int getMaxBound() const {
		return m_maxBound;
	}

	void setIdle(int idle) {
		m_idle = idle;
	}

	int getIdle() const {
		return m_idle;
	}

	void setSpeed(int speed) {
		m_servo.write(speed);
	}
};

#endif /* SERVOMOTOR_H_ */
