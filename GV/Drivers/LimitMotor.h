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
	float m_idle;

public:
	LimitMotor() :m_pMotor(NULL), m_lastOutput(0.0f), m_maxShift(0.1f), m_idle(0.0f) {}
	~LimitMotor() {}

	void init(int port) {}
	void init(IMotor* motor) {
		m_pMotor = motor;
		m_pMotor->setSpeed(m_idle);
	}

	void setEnabled(bool enable) {
		m_pMotor->setEnabled(enable);
	}

	bool isEnabled() const {
		return m_pMotor->isEnabled();
	}

	bool setBounds(float min, float max) {
		return m_pMotor->setBounds(min,max);
	}

	float getMinBound() const {
		return m_pMotor->getMinBound();
	}

	float getMaxBound() const {
		return m_pMotor->getMaxBound();
	}

	void setSpeed(float speed) {
		float error = (speed - m_lastOutput);
		float absError = (error < 0.0f) ? (-error) : (error);
		float output = speed;
		if (absError > m_maxShift) {
			// Clamp.
			if (error < 0.0f) {
				output = m_lastOutput - m_maxShift;
			} else {
				output = m_lastOutput + m_maxShift;
			}
		}
		m_pMotor->setSpeed(output);
		m_lastOutput = output;
	}

	float getMaxShift() const {
		return m_maxShift;
	}

	void setMaxShift(float maxShift) {
		if (maxShift < 0.0f) {
			maxShift = -maxShift;
		}
		float extreme = getMaxBound() - getMinBound();
		maxShift = constrain(maxShift, 0.0f, extreme);
		m_maxShift = maxShift;
	}
};

#endif /* LIMITMOTOR_H_ */
