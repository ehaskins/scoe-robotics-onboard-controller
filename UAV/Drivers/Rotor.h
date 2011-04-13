/*
 * Rotor.h
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick
 */

#ifndef ROTOR_H_
#define ROTOR_H_

#include "Drivers.h"

#include "BaseActuator.h"
#include "IRotor.h"

/**
 * Our rotor system:
 *
 * ESC:
 * 	Mystery 20A Speed Controller (blue series)
 * 	Current Rating: 20A
 * 	BEC Output: 5v / 2A
 * 	Voltage: 7.4v - 11.1v
 *
 * BLDC:
 *	Turnigy 2730 Brushless Motor 1500kv
 *	Kv (RPM/v): 1500
 *	Max. Current: 8A
 *	Max. Voltage: 11v
 *
 * Prop:
 *	To be determined
 *
 */

// Max. and min. "thrusts", in grams offset against gravity per rotor.
// TODO Determine these experimentally with actual equipment! Values used represent the APC 9x6 2-blade rotor
#define MAX_THRUST	255
#define MIN_THRUST	0

// Max. and min. PWM duty cycles.
// TODO Determine these experimentally with actual equipment!
#define MAX_ROTOR_PWM	178
#define MIN_ROTOR_PWM	102

// Idle thrust (10 N ~= 9.8 N)
#define IDLE_THRUST		10

// Conversion factor relating thrust and torque.
#define ROTOR_THRUST_TORQUE_RATIO	1.83f

// Value to perform a safe, consistent landing.
#define ROTOR_SAFE_LANDING	102

class Rotor: public BaseActuator, public IRotor {
protected:
	uint8_t m_idle;
	uint8_t m_maxShift;

	uint8_t m_lastPWM;

public:
	Rotor(uint8_t idle, uint8_t maxShift);
	virtual ~Rotor();

public:
	void onInit();
	void onEnable(bool quick);
	void onDisable(bool forced);
	void onValuesChanged();

	void setThrust(float thrust);
	float calcTorque(float thrust);
};

#endif /* ROTOR_H_ */
