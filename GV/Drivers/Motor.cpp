/*
 * Motor.cpp
 *
 *  Created on: Apr 13, 2011
 *      Author: Nick
 */

#include "Motor.h"
#include "../UserConstants.h"

#if USING_TRUE_SPEED
long calcDriveMotorPulseWidth(int speed, long minWidth, long maxWidth) {
	// Get our data point.
	float x = (float)(abs(speed));

	float powers[7] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	for (int i = 1; i < 7; i++) {
		powers[i] = powers[i-1] * x;
	}

	// Calculate the pulse width in degrees. See "Servo Angle vs. Motor Speed".
	float fltDegs = (1.7468e-11 * powers[6]) + (-4.1073e-9 * powers[5]) +
		(-4.7308e-7 * powers[4]) + (2.1142e-4 * powers[3]) +
		(-1.9961e-2 * powers[2]) + (0.73262 * powers[1]) +
		(3.6268 * powers[0]);

	// Give the proper sign.
	if (speed < 0) {
		fltDegs = -fltDegs;
	}

	// Re-map to the appropriate value range.
	long pulseWidth = map((long)fltDegs, -USER_MOTOR_MAX_SPEED, USER_MOTOR_MAX_SPEED, minWidth, maxWidth);

	// Return.
	return pulseWidth;
}
#endif
