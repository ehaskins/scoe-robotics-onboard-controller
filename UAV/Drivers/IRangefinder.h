/*
 * IRangefinder.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef IRANGEFINDER_H_
#define IRANGEFINDER_H_

class IRangefinder {
public:
	virtual ~IRangefinder() = 0;

	/**
	 * Gets the distance, in meters, reported by this rangefinder.
	 * @return The approximate distance, in meters.
	 */
	virtual float getDistance() = 0;

	/**
	 * Gets the uncertainty of measurements reported at different ranges.
	 * @param distance The distance reported by the target.
	 * @return The uncertainty value.
	 */
	virtual float getUncertainty(float distance) = 0;
};

#endif /* IRANGEFINDER_H_ */
