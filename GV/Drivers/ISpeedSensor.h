/*
 * ISpeedSensor.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef ISPEEDSENSOR_H_
#define ISPEEDSENSOR_H_

#include "IDevice.h"

class ISpeedSensor : public IDevice {
public:
	virtual ~ISpeedSensor() = 0;

	virtual float getSpeed() = 0;
};

#endif /* ISPEEDSENSOR_H_ */
