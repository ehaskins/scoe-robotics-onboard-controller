/*
 * KiwiDrive.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#include "KiwiDrive.h"

bool KiwiDrive::setMotorBounds(int motor, float min, float max) {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		return false;
	} else {
		return m->setBounds(min, max);
	}
}

float KiwiDrive::getMotorUpperBound(int motor) const {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		Serial.println("Invalid motor specified in getMotorUpperBound()!");
		return 0.0f;
	} else {
		return m->getMaxBound();
	}
}

float KiwiDrive::getMotorLowerBound(int motor) const {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		Serial.println("Invalid motor specified in getMotorLowerBound()!");
		return 0.0f;
	} else {
		return m->getMinBound();
	}
}

bool KiwiDrive::driveMotor(int motor, float value) {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		Serial.println("Invalid motor specified in driveMotor()!");
		return false;
	} else {
		if (value < m->getMinBound() || value > m->getMaxBound()) {
			return false;
		} else {
			m->setSpeed(value);
			return true;
		}
	}
}

void KiwiDrive::driveSystem(float* axisVector) {
	// Get the control axes that matter to us
	float forward = axisVector[0];
	float strafe = axisVector[1];
	float yaw = axisVector[2];

	if (m_invertForward) {
		forward = -forward;
	}

	if (m_invertStrafe) {
		strafe = -strafe;
	}

	if (m_invertYaw) {
		yaw = -yaw;
	}

	// Apply the kiwi drive equations to the motor control values.
	float rearValue = strafe + yaw;
	float rightValue = (-0.5f * strafe) + (-0.866f * forward) + yaw;
	float leftValue = (-0.5f * strafe) + (0.866f * forward) + yaw;

	// Clamp the motor values.
	rearValue = constrain(rearValue, -2.0f, 2.0f);
	rightValue = constrain(rightValue, -2.366f, 2.366f);
	leftValue = constrain(leftValue, -2.366f, 2.366f);

	// Convert and map the values to feet/second speeds.
	rearValue = rearValue * 12.0f / 2.366f;
	rightValue = rightValue * 12.0f / 2.366f;
	leftValue = leftValue * 12.0f / 2.366f;

	// Output the values to the motors.
	driveMotor(KIWI_LEFT, leftValue);
	driveMotor(KIWI_RIGHT, rightValue);
	driveMotor(KIWI_REAR, rearValue);
}
