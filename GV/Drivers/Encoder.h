/*
 * Encoder.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "Drivers.h"
#include "IEncoder.h"

// Ticks per Cycle Settings: http://products.cui.com/CUI_AMT102-V_Dip_Switch_Settings.pdf?fileID=3816
class Encoder : public IEncoder {
private:
	bool m_enabled;
	int m_dirPort;
	int m_tickINT;
	EncoderDirection m_expectedDirection;
	long m_errorCount;

	long m_tickCount;

	long m_ticksPerCycle;

public:
	Encoder()
	:m_enabled(false), m_dirPort(NO_PORT), m_tickINT(NO_PORT), m_expectedDirection(FORWARD), m_errorCount(0), m_tickCount(0), m_ticksPerCycle(2048) {}

	void init(int port) {}
	void init(int dirPort, int tickINT) {
		m_dirPort = dirPort;
		m_tickINT = tickINT;

		// Set the digital port to input.
		pinMode(m_dirPort, INPUT);
		// Enable the interrupts.
		initInterrupts(m_tickINT);
	}

	void setEnabled(bool enable) {
		enableInterrupts(enable);
		m_enabled = enable;
	}

	bool isEnabled() const {
		return m_enabled;
	}

	void initInterrupts(int tickINT);
	void enableInterrupts(bool enable);

	EncoderDirection getDirection() const {
		return (EncoderDirection)digitalRead(m_dirPort);
	}

	void setExpectedDirection(EncoderDirection dir) {
		m_expectedDirection = dir;
	}

	long getDirectionErrorCount() const {
		return m_errorCount;
	}
	
	void resetDirectionErrorCount() {
		m_errorCount = 0;
	}

	void onTick() {
		EncoderDirection dir = getDirection();
		if (dir == FORWARD) {
			m_tickCount++;
			// Turn on the LED.
			digitalWrite(13, HIGH);
		} else {
			m_tickCount--;
			// Turn off the LED.
			digitalWrite(13, LOW);
		}
		if (dir != m_expectedDirection) {
			m_errorCount++;
		}
	}

/**
	void onCycle() {
		// Determine the offset from the expected tick count.
		long correctCount = m_tickCount + m_phaseShift;

		// Get the number of cycles completed, and the number of ticks off of the mark.
		long offset = (correctCount % getNumTicksPerCycle());

		// Round to the nearest full cycle.
		if (offset > (getNumTicksPerCycle() / 2)) {
			// Offset is closer to forward one cycle.
			m_tickCount += (getNumTicksPerCycle() - offset);
		} else {
			// Throw out the extra ticks.
			m_tickCount -= offset;
		}
	}
*/

	long getNumTicksPerCycle() const {
		return m_ticksPerCycle;
	}
	
	void setNumTicksPerCycle(long numTicks) {
		m_ticksPerCycle = numTicks;
	}

	long getTickCount() const {
		return m_tickCount;
	}

	void resetTickCount() {
		// Determine the phase-shift error.
//		m_phaseShift = (m_tickCount > 0) ? (m_tickCount % getNumTicksPerCycle()) : -(-m_tickCount % getNumTicksPerCycle());
		// Reset the tick counter.
		m_tickCount = 0;
	}
};

#endif /* ENCODER_H_ */
