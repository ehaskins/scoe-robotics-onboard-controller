/*
 * Rotor.cpp
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick
 */

#include "Rotor.h"

Rotor::Rotor(uint8_t idle, uint8_t maxShift) {
	m_idle = idle;
	m_maxShift = maxShift;
	m_lastPWM = idle;
}

Rotor::~Rotor() {
	// If active, deactivate the rotor.
	if (isActive()) {
		analogWrite(getPort(), m_idle);
	}
}

void Rotor::onInit() {
	// Set the pin to output.
	pinMode(getPort(), OUTPUT);
}

void Rotor::onEnable(bool quick) {
	pinMode(getPort(), OUTPUT);
	if (quick) {
		analogWrite(getPort(), m_lastPWM);
	} else {
		analogWrite(getPort(), m_idle);
	}
}

void Rotor::onDisable(bool forced) {
	// TODO Make sure this works properly.
	if (forced) {
		analogWrite(getPort(), 0);
	} else {
		analogWrite(getPort(), ROTOR_SAFE_LANDING);
	}
}

void Rotor::onValuesChanged() {
	// Perform output to the rotor.
	// The value to be sent is stored in m_lastPWM, and the port is accessible via getPort().
	// This is the last step before actual output, so safety features and limiters can be added here.thithisis
	analogWrite(getPort(), m_lastPWM);
}

void Rotor::setThrust(float thrust) {

	// Prevent us from writing out to the rotor if it is disabled.
	if (!isEnabled()) {
		return;
	}

	// Four steps:
	// 1. Clamp to between the minimum and maximum thrust.
	// 2. Compute the PWM output to the rotor.
	// 3. Ensure that the PWM output is not too different from the last value.
	// 4. Output the PWM signal to the rotor.

	// 1. Clamp the thrust.
	thrust = constrain(thrust, MIN_THRUST, MAX_THRUST);

	// 2. Compute the PWM output to the motor.
	int output = map((long)thrust, MIN_THRUST, MAX_THRUST, MIN_ROTOR_PWM, MAX_ROTOR_PWM);

	// 3. Ensure that the PWM output is not too different from the last value.
	output = restrict(m_lastPWM, output, m_maxShift);

	// 4. Output to the rotor.
	m_lastPWM = output;
	onValuesChanged();
}

float Rotor::calcTorque(float thrust) {
	// According to the WPI MQP Quadrotor Report
	// (2009, Gustafson, DiCesare, Lindenfelzer),
	// the value retrieved from their experiments
	// relating torque to thrust (pg.33-40) was
	// approximately 1.83.
	// (http://www.wpi.edu/Pubs/E-project/Available/E-project-030609-124019/unrestricted/MQP_Report_Quadrotor_Final[1].pdf)
	return ((float)thrust * ROTOR_THRUST_TORQUE_RATIO);
}
