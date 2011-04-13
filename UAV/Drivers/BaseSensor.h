/*
 * BaseSensor.h
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick Iannone
 */

#ifndef BASESENSOR_H_
#define BASESENSOR_H_

#include "IDevice.h"

class BaseSensor : public IDevice {
private:
	int m_port;
	bool m_enabled;

public:
	void init(int port);
	bool isActive() const;
	bool isEnabled() const;
	void setEnabled(bool enable, bool quick);
	int getPort() const;

public:
	virtual void onInit(int port) = 0;

	virtual void onEnable() = 0;

	virtual void onDisable() = 0;

	virtual void onNewData() = 0;
};

#endif /* BASESENSOR_H_ */
