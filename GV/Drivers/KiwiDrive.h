/*
 * KiwiDrive.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef KIWIDRIVE_H_
#define KIWIDRIVE_H_

#include "Drivers.h"
#include "IDriveSystem.h"
#include <string.h>

typedef enum {
	KIWI_LEFT = 0,
	KIWI_RIGHT = 1,
	KIWI_REAR = 2
} KiwiMotor;

class KiwiDrive : public IDriveSystem {
private:
	IMotor* m_pLeftMotor;
	IMotor* m_pRightMotor;
	IMotor* m_pRearMotor;

	bool m_invertForward;
	bool m_invertStrafe;
	bool m_invertYaw;

	inline IMotor* getMotor(KiwiMotor motor) const {
		switch (motor) {
		case KIWI_LEFT:
			return m_pLeftMotor;
		case KIWI_RIGHT:
			return m_pRightMotor;
		case KIWI_REAR:
			return m_pRearMotor;
		default:
			return NULL;
		}
	}

public:
	KiwiDrive()
	:m_pLeftMotor(NULL), m_pRightMotor(NULL), m_pRearMotor(NULL), m_invertForward(false), m_invertStrafe(false), m_invertYaw(false) {}

	void init(int port) {}
	void init(IMotor* left, IMotor* right, IMotor* rear) {
		m_pLeftMotor = left;
		m_pRightMotor = right;
		m_pRearMotor = rear;
	}

	void setEnabled(bool enable) {
		m_pLeftMotor->setEnabled(enable);
		m_pRightMotor->setEnabled(enable);
		m_pRearMotor->setEnabled(enable);
	}

	bool isEnabled() const {
		return (m_pLeftMotor->isEnabled() && m_pRightMotor->isEnabled() && m_pRearMotor->isEnabled());
	}

	inline int getNumMotors() const { return 3; }

	bool setMotorIdle(int motor, int idle);
	int getMotorIdle(int motor) const;

	bool setMotorBounds(int motor, int min, int max);
	int getMotorUpperBound(int motor) const;
	int getMotorLowerBound(int motor) const;
	bool driveMotor(int motor, int value);
	void driveSystem(int* axisVector);

	void invertStrafe(bool invert) {
		m_invertStrafe = invert;
	}
	void invertForward(bool invert) {
		m_invertForward = invert;
	}
	void invertYaw(bool invert) {
		m_invertYaw = invert;
	}
};

#endif /* KIWIDRIVE_H_ */
