/*
 * BaseSensor.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick
 */

#include "BaseSensor.h"

void BaseSensor::init(int port) {
	// Let the user respond before assigning the port.
	onInit(port);
	m_port = port;
}

bool BaseSensor::isActive() const {
	// If the port is set to NO_PORT, the device is inactive.
	return (m_port != NO_PORT);
}

int BaseSensor::getPort() const {
	return m_port;
}

void BaseSensor::setEnabled(bool enable, bool quick) {
	if (!isActive()) {
		return;
	}
	if (m_enabled != enable) {
		if (enable) {
			onEnable();
		} else {
			onDisable();
		}
		m_enabled = enable;
	}
}

bool BaseSensor::isEnabled() const {
	return (isActive() && m_enabled);
}
