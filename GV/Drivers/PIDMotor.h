/*
 * PIDMotor.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef PIDMOTOR_H_
#define PIDMOTOR_H_

#include "Drivers.h"
#include "IMotor.h"
#include "ISpeedSensor.h"
#include "../Util/PIDController.h"
#include <string.h>

class PIDMotor : public IMotor {
private:
	bool m_enabled;
	PIDController m_pid;
	IMotor* m_pMotor;
	ISpeedSensor* m_pSpeedSensor;

public:
	PIDMotor()
	:m_enabled(false), m_pid(0.0f), m_pMotor(NULL), m_pSpeedSensor(NULL) {}

	void init(int port) {}
	void init(IMotor* baseMotor, ISpeedSensor* baseSensor, float idle = 0.0f) {
		m_pid.fill(idle);
		m_pMotor = baseMotor;
		m_pSpeedSensor = baseSensor;
	}

	void setEnabled(bool enable) {
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	bool setBounds(float min, float max) {
		return m_pMotor->setBounds(min, max);
	}

	float getMinBound() const {
		return m_pMotor->getMinBound();
	}

	float getMaxBound() const {
		return m_pMotor->getMaxBound();
	}

	void setSpeed(float speed) {
		float actual = m_pSpeedSensor->getSpeed();
		float output = m_pid.control(speed, actual);
		m_pMotor->setSpeed(output);
	}
};

#endif /* PIDMOTOR_H_ */
