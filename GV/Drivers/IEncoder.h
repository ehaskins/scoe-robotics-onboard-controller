/*
 * IEncoder.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef IENCODER_H_
#define IENCODER_H_

#include "IDevice.h"
#include <WProgram.h>

typedef enum {
	FORWARD = HIGH,
	BACKWARD = LOW
} EncoderDirection;

class IEncoder : public IDevice {
public:

	/**
	 * Initializes the two required interrupts for the controller.
	 * @param tickINT The interrupt for the one-tick pulse channel.
	 */
	virtual void initInterrupts(int tickINT) = 0;

	/**
	 * Enables or disables the encoder interrupt channels.
	 * @param enabled <b>true</b> to enable, <b>false</b> to disable.
	 */
	virtual void enableInterrupts(bool enabled) = 0;

	/**
	 * Gets the direction of the encoder.
	 * @return <b>FORWARD</b> if the shaft was last moved forwards, <b>BACKWARD</b> otherwise.
	 */
	virtual EncoderDirection getDirection() const = 0;
	
	/**
	 * Sets the expected direction of the encoder.
	 * @param dir The expected direction of the system.
	 */
	virtual void setExpectedDirection(EncoderDirection dir) = 0;

	/**
	 * Gets the number of direction errors counted since the last reset.
	 */
	virtual long getDirectionErrorCount() const = 0;
	
	/**
	 * Resets the direction error counter.
	 */
	virtual void resetDirectionErrorCount() = 0;
	
	/**
	 * Called upon the one-tick interrupt. Adds or subtracts a tick from the counter.
	 */
	virtual void onTick() = 0;

	/**
	 * Retrieves the number of ticks per cycle.
	 */
	virtual long getNumTicksPerCycle() const = 0;

	/**
	 * Sets the number of ticks per cycle.
	 * @param numTicks The number of ticks per cycle.
	 */
	virtual void setNumTicksPerCycle(long numTicks) = 0;
	
	/**
	 * Gets the number of ticks counted since the last reset.
	 */
	virtual long getTickCount() const = 0;

	/**
	 * Resets the tick counter to zero.
	 */
	virtual void resetTickCount() = 0;
};

#endif /* IENCODER_H_ */
