/*
 * LimitMotor.h
 *
 *  Created on: Apr 13, 2011
 *      Author: Nick
 */

#ifndef LIMITMOTOR_H_
#define LIMITMOTOR_H_

#include "IMotor.h"
#include <string.h>
#include <WProgram.h>

class LimitMotor : public IMotor {
private:
	IMotor* m_pMotor;
	float m_lastOutput;
	float m_maxShift;

public:
	LimitMotor() :m_pMotor(NULL), m_lastOutput(0), m_maxShift(15) {}

	void init(int port) {}
	void init(IMotor* motor, int maxShift) {
		m_pMotor = motor;
		m_maxShift = maxShift;
		m_lastOutput = m_pMotor->getIdle();
	}

	void setIdle(int idle) {
		m_pMotor->setIdle(idle);
	}

	int getIdle() const {
		return m_pMotor->getIdle();
	}

	void setEnabled(bool enable) {
		m_pMotor->setEnabled(enable);
	}

	bool isEnabled() const {
		return m_pMotor->isEnabled();
	}

	bool setBounds(int min, int max) {
		return m_pMotor->setBounds(min,max);
	}

	int getMinBound() const {
		return m_pMotor->getMinBound();
	}

	int getMaxBound() const {
		return m_pMotor->getMaxBound();
	}

	void setSpeed(int speed) {
		int error = (speed - m_lastOutput);
		int absError = abs(error);
		int output = speed;
		if (absError > m_maxShift) {
			// Clamp.
			if (error < 0) {
				output = m_lastOutput - m_maxShift;
			} else {
				output = m_lastOutput + m_maxShift;
			}
		}
		m_pMotor->setSpeed(output);
		m_lastOutput = output;
	}

	int getMaxShift() const {
		return m_maxShift;
	}

	void setMaxShift(int maxShift) {
		maxShift = abs(maxShift);
		int extreme = getMaxBound() - getMinBound();
		maxShift = constrain(maxShift, 0, extreme);
		m_maxShift = maxShift;
	}
};

#endif /* LIMITMOTOR_H_ */
