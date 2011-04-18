/*
 * IDigitalInput.h
 *
 *  Created on: Apr 18, 2011
 *      Author: Nick
 */

#ifndef IDIGITALINPUT_H_
#define IDIGITALINPUT_H_

#include "IDevice.h"

class IDigitalInput : public IDevice {
public:
	virtual bool getValue() = 0;
};

#endif /* IDIGITALINPUT_H_ */
