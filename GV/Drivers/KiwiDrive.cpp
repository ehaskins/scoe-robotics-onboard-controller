/*
 * KiwiDrive.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#include "KiwiDrive.h"

bool KiwiDrive::setMotorBounds(int motor, int min, int max) {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		return false;
	} else {
		return m->setBounds(min, max);
	}
}

int KiwiDrive::getMotorUpperBound(int motor) const {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
//		Serial.println("Invalid motor specified in getMotorUpperBound()!");
		return 0;
	} else {
		return m->getMaxBound();
	}
}

int KiwiDrive::getMotorLowerBound(int motor) const {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
//		Serial.println("Invalid motor specified in getMotorLowerBound()!");
		return 0;
	} else {
		return m->getMinBound();
	}
}

bool KiwiDrive::setMotorIdle(int motor, int idle) {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		return false;
	} else {
		m->setIdle(idle);
		return true;
	}
}

int KiwiDrive::getMotorIdle(int motor) const {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
		return 0;
	} else {
		return m->getIdle();
	}
}

bool KiwiDrive::driveMotor(int motor, int value) {
	IMotor* m = getMotor((KiwiMotor)motor);
	if (m == NULL) {
//		Serial.println("Invalid motor specified in driveMotor()!");
		return false;
	} else {
		m->setSpeed(isEnabled() ? value : getMotorIdle(motor));
		return true;
	}
}

void KiwiDrive::driveSystem(int* axisVector) {
	// Get the control axes that matter to us
	int forward = axisVector[0];
	int strafe = axisVector[1];
	int yaw = axisVector[2];

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
	int rearValue = strafe + yaw;
	int rightValue = (-strafe / 2) + (int)(forward * 0.866f) + yaw;
	int leftValue = (-strafe / 2) + (int)(-forward * 0.866f) + yaw;

	// Clamp the motor values.
	rearValue = constrain(rearValue, -255, 255);
	rightValue = constrain(rightValue, -300, 300);
	leftValue = constrain(leftValue, -300, 300);

	// Convert and map the values to feet/second speeds.
	rearValue = map(rearValue, -300, 300, getMotorLowerBound(KIWI_REAR), getMotorUpperBound(KIWI_REAR));
	rightValue = map(rightValue, -300, 300, getMotorLowerBound(KIWI_RIGHT), getMotorUpperBound(KIWI_RIGHT));
	leftValue = map(leftValue, -300, 300, getMotorLowerBound(KIWI_LEFT), getMotorUpperBound(KIWI_LEFT));

#if DEBUG
	Serial.println("Kiwi Drive: ");
	Serial.print("Rear: ");
	Serial.print(rearValue);
	Serial.print("in/s, Right: ");
	Serial.print(rightValue);
	Serial.print("in/s, Left: ");
	Serial.print(leftValue);
	Serial.println("in/s.");
#endif

	// Output the values to the motors.
	driveMotor(KIWI_LEFT, leftValue);
	driveMotor(KIWI_RIGHT, rightValue);
	driveMotor(KIWI_REAR, rearValue);
}
