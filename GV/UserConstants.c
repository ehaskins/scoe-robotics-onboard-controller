/*
 * UserConstants.c
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */
#include "UserConstants.h"

/**
* A utility function for calculating the CIM motor servo pulse width, in microseconds.
* Determined experimentally by ramping motor across full servo range, observing the
* speed of the motor, and fitting a set of functions to the data.
*/
int calcDriveMotorSpeed(long pulseWidth, long minWidth, long maxWidth) {

	// Calculate the servo degrees, from -90 to +90.
	int servoDegs = (int)map(pulseWidth, minWidth, maxWidth, -90L, 90L);
	int absServoDegs = abs(servoDegs);

	// Get our data point.
	float x = (float)absServoDegs;

	float powers[7] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 1; i < 7; i++) {
		powers[i] = powers[i-1] * x;
	}

	// Calculate our speed. See "Motor Speed vs. Servo Angle".
	float fltSpeed = (2.7642e-8 * powers[6]) + (-8.3954e-6 * powers[5]) +
		(9.8045e-4 * powers[4]) + (-5.4009e-2 * powers[3]) +
		(1.3146 * powers[2]) + (5.7580 * powers[1]) +
		(2.8107 * powers[0]);

	// Clamp less-than-zero values.
	if (fltSpeed < 0.0f) {
		fltSpeed = 0.0f;
	}

	// Convert to integer type and assign the proper sign.
	int motorSpeed = (int)((servoDegs < 0) ? (-fltSpeed) : (fltSpeed));

	return motorSpeed;
}
