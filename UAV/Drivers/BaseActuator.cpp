/*
 * BaseActuator.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick Iannone
 */
#include "BaseActuator.h"

void BaseActuator::init(int port) {
	// Let the user respond before assigning the port.
	onInit(port);
	m_port = port;
}

bool BaseActuator::isActive() const {
	// If the port is set to NO_PORT, the device is inactive.
	return (m_port != NO_PORT);
}

int BaseActuator::getPort() const {
	return m_port;
}

void BaseActuator::setEnabled(bool enable, bool quick) {
	// We can't enable unless we're active.
	if (!isActive()) {
		return;
	}
	// NOTE If we pass in quick, do it anyway; we can't expect the system to be responding accurately.
	if ((m_enabled != enable) || quick) {
		if (enable) {
			onEnable(quick);
		} else {
			onDisable(quick);
		}
		m_enabled = enable;
	}
}

bool BaseActuator::isEnabled() const {
	return (isActive() && m_enabled);
}
