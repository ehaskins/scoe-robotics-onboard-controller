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
	virtual bool setBounds(float min, float max) = 0;

	virtual float getMinBound() const = 0;

	virtual float getMaxBound() const = 0;

	virtual void setSpeed(float speed) = 0;
};

#endif /* IMOTOR_H_ */
