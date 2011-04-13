/*
 * Encoder.cpp
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#include "Encoder.h"
#include <wiring_private.h>

typedef struct {
	Encoder* encoder;
	bool isFullCycle;
	bool isEnabled;
} EncoderMapping;

// The map of encoders to interrupt pins.
static volatile EncoderMapping s_encoderIntPins[EXTERNAL_NUM_INTERRUPTS];

// The generic interrupt service routine.
void _handleEncoderINT() {
	// Get the interrupt number.
	uint8_t mask = EIFR;
	uint8_t i = 0;
	for (i = 0; i < EXTERNAL_NUM_INTERRUPTS; i++) {
		if (mask & (1 << i)) {
			i++;
			break;
		}
	}
	// Get the mapping, and conditionally read the interrupt.
	if (i != 0) {
		volatile EncoderMapping* mapping = &s_encoderIntPins[i-1];
		Encoder* enc = mapping->encoder;
		if (enc != NULL && mapping->isEnabled) {
			if (mapping->isFullCycle) {
				enc->onCycle();
			} else {
				enc->onTick();
			}
		}
	}
}

void Encoder::initInterrupts(int tickINT) {

	// Clamp the interrupt numbers.
	tickINT %= EXTERNAL_NUM_INTERRUPTS;

	// Map the first encoder.
	volatile EncoderMapping* tickMap = &s_encoderIntPins[tickINT];
	tickMap->encoder = this;
	tickMap->isFullCycle = false;

	// Map the interrupts themselves.
	attachInterrupt(tickINT, _handleEncoderINT, RISING);
}

void Encoder::enableInterrupts(bool enable) {
	// Enable/disable both interrupts.
	s_encoderIntPins[m_tickINT].isEnabled = enable;
}
