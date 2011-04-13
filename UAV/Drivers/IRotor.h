/*
 * IRotor.h
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick
 */

#ifndef IROTOR_H_
#define IROTOR_H_

#include <inttypes.h>

class IRotor {
public:
	virtual ~IRotor() = 0;

	/**
	 * Sets the rotor to output the given amount of thrust, in Newtons (?).
	 */
	virtual void setThrust(float thrust) = 0;

	/**
	 * Calculates the torque applied to the robot frame, in Newton-meters (?).
	 */
	virtual float calcTorque(float thrust) = 0;
};

#endif /* IROTOR_H_ */
