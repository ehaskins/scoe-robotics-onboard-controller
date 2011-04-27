/*
 * IDriveSystem.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef IDRIVESYSTEM_H_
#define IDRIVESYSTEM_H_

#include "Drivers.h"
#include "IDevice.h"

class IDriveSystem : public IDevice {
public:

	/**
	 * Gets the number of motors in the drive system.
	 * @return The number of motors.
	 */
	virtual int getNumMotors() const = 0;

	/**
	 * Sets the motor bounds for the given motor.
	 * @param motor The motor to set.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @return <b>true</b> if the bounds are valid and the motor exists, <b>false</b> otherwise.
	 */
	virtual bool setMotorBounds(int motor, int min, int max) = 0;

	/**
	 * Gets the upper bound for the given motor.
	 * @param motor The motor to get.
	 * @return The defined upper bound, or 0 if the motor is not valid.
	 */
	virtual int getMotorUpperBound(int motor) const = 0;

	/**
	 * Gets the lower bound for the given motor.
	 * @param motor The motor to get.
	 * @return The defined lower bound, or 0 if the motor is not valid.
	 */
	virtual int getMotorLowerBound(int motor) const = 0;

	virtual bool setMotorIdle(int motor, int idle) = 0;

	virtual int getMotorIdle(int motor) const = 0;

	/**
	 * Drives the motor at the given value, if possible.
	 * @param motor The motor to drive.
	 * @param value The drive value to send.
	 * @return <b>true</b> if the motor is valid; <b>false</b> otherwise.
	 */
	virtual bool driveMotor(int motor, int value) = 0;

	/**
	 * Drives the full system.
	 * @param axisVector An array of axial movement values.
	 */
	virtual void driveSystem(int* axisVector) = 0;
};

#endif /* IDRIVESYSTEM_H_ */
