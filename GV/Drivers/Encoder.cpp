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
//	bool isFullCycle;
	bool isEnabled;
} EncoderMapping;

// The map of encoders to interrupt pins.
static volatile EncoderMapping s_encoderIntPins[EXTERNAL_NUM_INTERRUPTS];

#define DECL_ENC_INT(intnum)  \
  static void _handleEncoder_##intnum##_ () { \
    uint8_t mask = EIFR; \
    volatile EncoderMapping* mapping = &s_encoderIntPins[(intnum)]; \
    Encoder* enc = mapping->encoder; \
    if (enc != NULL && mapping->isEnabled) { \
      enc->onTick(); \
    } \
  }

#define ENC_INT(intnum)  _handleEncoder_##intnum##_

// Void function pointer
typedef void(*VoidFunc)();

// Generate the interrupt declarations.
DECL_ENC_INT(0)
DECL_ENC_INT(1)
DECL_ENC_INT(2)
DECL_ENC_INT(3)
DECL_ENC_INT(4)
DECL_ENC_INT(5)

static VoidFunc _encHandlers[] = {
  ENC_INT(0),
  ENC_INT(1),
  ENC_INT(2),
  ENC_INT(3),
  ENC_INT(4),
  ENC_INT(5)
};

void Encoder::initInterrupts(int tickINT) {

	// Clamp the interrupt numbers.
	tickINT %= EXTERNAL_NUM_INTERRUPTS;

	// Map the first encoder.
	volatile EncoderMapping* tickMap = &s_encoderIntPins[tickINT];
	tickMap->encoder = this;
//	tickMap->isFullCycle = false;

	// Enable the LED blink pin.
//	pinMode(13, OUTPUT);

	// Map the interrupts themselves.
	attachInterrupt(tickINT, _encHandlers[tickINT], RISING);
}

void Encoder::enableInterrupts(bool enable) {
	// Enable/disable both interrupts.
	s_encoderIntPins[m_tickINT].isEnabled = enable;
}
