/*
 * IMotor.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef IMOTOR_H_
#define IMOTOR_H_

#include "IDevice.h"

class IMotor : public IDevice {
public:

	/**
	 * Sets the upper and lower bounds of the motor's operating range.
	 * @param min The lower bound.
	 * @param max The upper bound.
	 * @return <b>true</b> if the bounds are valid, <b>false</b> otherwise.
	 */
	virtual bool setBounds(int min, int max) = 0;

	virtual int getMinBound() const = 0;

	virtual int getMaxBound() const = 0;

	virtual void setIdle(int idle) = 0;

	virtual int getIdle() const = 0;

	virtual void setSpeed(int speed) = 0;
};

#endif /* IMOTOR_H_ */
