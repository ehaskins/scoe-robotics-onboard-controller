/*
 * DigitalInput.h
 *
 *  Created on: Apr 18, 2011
 *      Author: Nick
 */

#ifndef DIGITALINPUT_H_
#define DIGITALINPUT_H_

#include <WProgram.h>
#include "IDigitalInput.h"

class DigitalInput : public IDigitalInput {
private:
	int m_pin;
	bool m_enabled;

public:
	DigitalInput() :m_pin(NO_PORT), m_enabled(false) {}

	void init(int port) {
		pinMode(port, INPUT);
		m_pin = port;
	}

	void setEnabled(bool enable) {
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	bool getValue() const {
		if (!isEnabled()) {
			return false;
		}
		return digitalRead(m_pin);
	}
};

#endif /* DIGITALINPUT_H_ */
