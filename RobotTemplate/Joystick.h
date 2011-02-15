/*
 * Joystick.h
 *
 *  Created on: Feb 12, 2011
 *      Author: EHaskins
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

const int NUM_AXES = 6;
const int NUM_BUTTONS = 16;

struct Joystick{
	unsigned char Axis[NUM_AXES];
	bool Button[NUM_BUTTONS];

};

#endif /* JOYSTICK_H_ */
