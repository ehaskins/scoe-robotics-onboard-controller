/*
 * IDevice.h
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */

#ifndef IDEVICE_H_
#define IDEVICE_H_

#ifndef NO_PORT
	#define NO_PORT	(-1)
#endif

class IDevice {
public:
	virtual void init(int port) = 0;

	virtual void setEnabled(bool enable) = 0;

	virtual bool isEnabled() const = 0;
};

#endif /* IDEVICE_H_ */
