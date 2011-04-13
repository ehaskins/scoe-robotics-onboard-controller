/*
 * IController.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

class IController {
public:
	virtual ~IController() = 0;

	/**
	 * Runs an iteration of a control loop, with the given setpoint, feedback, and timestep.
	 */
	virtual float control(float setpoint, float feedback) = 0;
};

#endif /* ICONTROLLER_H_ */
