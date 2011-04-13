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

class Encoder : public IEncoder {
private:
	bool m_enabled;
	int m_dirPort;
	int m_tickINT;
//	int m_cycleINT;

	int m_tickCount;
//	int m_phaseShift;

public:
	Encoder()
	:m_enabled(false), m_dirPort(NO_PORT), m_tickINT(NO_PORT), m_tickCount(0) {}
	~Encoder() {}

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

	void onTick() {
		if (getDirection() == FORWARD) {
			m_tickCount++;
		} else {
			m_tickCount--;
		}
	}

	void onCycle() {
		// Determine the offset from the expected tick count.
		int correctCount = m_tickCount /* + m_phaseShift */;

		// Get the number of cycles completed, and the number of ticks off of the mark.
		int offset = (correctCount % getNumTicksPerCycle());

		// Round to the nearest full cycle.
		if (offset > (getNumTicksPerCycle() / 2)) {
			// Offset is closer to forward one cycle.
			m_tickCount += (getNumTicksPerCycle() - offset);
		} else {
			// Throw out the extra ticks.
			m_tickCount -= offset;
		}
	}

	int getNumTicksPerCycle() const {
		// TODO Verify this against the encoders themselves!
		return 48;
	}

	int getTickCount() const {
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
