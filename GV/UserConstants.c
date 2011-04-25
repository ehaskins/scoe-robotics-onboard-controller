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

	// Calculate our speed. See "Motor Speed vs. Servo Angle".
	float fltSpeed = (2.7642e-8 * pow(x, 6)) + (-8.3954e-6 * pow(x, 5)) +
		(9.8045e-4 * pow(x, 4)) + (-5.4009e-2 * pow(x, 3)) +
		(1.3146 * pow(x, 2)) + (5.7580 * x) + 2.8107;

	// Clamp less-than-zero values.
	if (fltSpeed < 0.0f) {
		fltSpeed = 0.0f;
	}

	// Convert to integer type and assign the proper sign.
	int motorSpeed = (int)((servoDegs < 0) ? (-fltSpeed) : (fltSpeed));

	return motorSpeed;
}

long calcDriveMotorPulseWidth(int speed, long minWidth, long maxWidth) {
	// Get our data point.
	float x = (float)(abs(speed));

	// Calculate the pulse width in degrees. See "Servo Angle vs. Motor Speed".
	float fltDegs = (1.7468e-11 * pow(x, 6)) + (-4.1073e-9 * pow(x, 5)) +
		(-4.7308e-7 * pow(x, 4)) + (2.1142e-4 * pow(x, 3)) +
		(-1.9961e-2 * pow(x, 2)) + (0.73262 * x) + 3.6268;

	// Give the proper sign.
	if (speed < 0) {
		fltDegs = -fltDegs;
	}

	// Re-map to the appropriate value range.
	long pulseWidth = map((long)fltDegs, -USER_MOTOR_MAX_SPEED, USER_MOTOR_MAX_SPEED, minWidth, maxWidth);

	// Return.
	return pulseWidth;
}
