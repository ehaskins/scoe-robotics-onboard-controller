/*
 * BaseActuator.h
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick Iannone
 */

#ifndef BASEACTUATOR_H_
#define BASEACTUATOR_H_

#include "IDevice.h"

class BaseActuator : public IDevice {
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
	/**
	 * Handles the initialization of the device.
	 * @param port The control port for the device.
	 */
	virtual void onInit(int port) = 0;

	/**
	 * Handles the enabling of the device.
	 * @param quick If the device is to be re-enabled quickly; ie. in the event of a brown-out reset.
	 */
	virtual void onEnable(bool quick) = 0;

	/**
	 * Handles the disabling of the device.
	 * @param forced If the device is to be disabled by force; ie. in the event of an emergency stop.
	 */
	virtual void onDisable(bool forced) = 0;

	/**
	 * Handles the changing of control values. Should perform the sending of information to the device.
	 */
	virtual void onValuesChanged() = 0;
};

#endif /* BASEACTUATOR_H_ */
