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
	PIDController m_pid;
	IMotor* m_pMotor;
	ISpeedSensor* m_pSpeedSensor;

public:
	PIDMotor()
	:m_pid(0), m_pMotor(NULL), m_pSpeedSensor(NULL) {}

	PIDController* getPIDController() {
		return &m_pid;
	}

	void init(int port) {}
	void init(IMotor* baseMotor, ISpeedSensor* baseSensor) {
		m_pid.fill(baseMotor->getIdle());
		m_pMotor = baseMotor;
		m_pSpeedSensor = baseSensor;
	}

	void setIdle(int idle) {
		m_pMotor->setIdle(idle);
	}

	int getIdle() const {
		return m_pMotor->getIdle();
	}

	void setEnabled(bool enable) {
		m_pMotor->setEnabled(enable);
		m_pSpeedSensor->setEnabled(enable);
	}

	bool isEnabled() const {
		return (m_pMotor->isEnabled() && m_pSpeedSensor->isEnabled());
	}

	bool setBounds(int min, int max) {
		return m_pMotor->setBounds(min, max);
	}

	int getMinBound() const {
		return m_pMotor->getMinBound();
	}

	int getMaxBound() const {
		return m_pMotor->getMaxBound();
	}

	void setSpeed(int speed) {
		int actual = m_pSpeedSensor->getSpeed();
		int output = m_pid.control(speed, actual);
		m_pMotor->setSpeed(output);
	}
};

#endif /* PIDMOTOR_H_ */
