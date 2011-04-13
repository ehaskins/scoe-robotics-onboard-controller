/*
 * UserCode.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */
#include <WProgram.h>

#ifndef USERCONSTANTS_H_
#define USERCONSTANTS_H_

const int FIXED_LOOP_FREQUENCY = 1;

// The PWM pins for the motor controllers.
#define PIN_LEFT_MOTOR			5
#define PIN_RIGHT_MOTOR			6
#define PIN_REAR_MOTOR			7

// Whether or not any of the drive directions are inverted.
#define USER_INVERT_FORWARD		false
#define USER_INVERT_STRAFE		false
#define USER_INVERT_YAW			false

// Whether or not any of the motor lines are inverted.
#define USER_INVERT_LEFT_MOTOR	false
#define USER_INVERT_RIGHT_MOTOR	false
#define USER_INVERT_REAR_MOTOR	false

// The maximum shift in motor speed between timesteps.
#define USER_MAX_SHIFT			1.0f

#endif
