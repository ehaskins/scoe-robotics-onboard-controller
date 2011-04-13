/*
 * PIDController.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: Nick
 */
#include "PIDController.h"

PIDController::PIDController(float idle)
:m_kP(1.0f), m_kI(0.01f), m_kD(0.1f), m_index(0)
{
	for (int i = 0; i < PID_INTEGRAL_SIZE; i++) {
		m_integral[i] = idle;
	}
}

float PIDController::control(float setpoint, float feedback)
{
	float error = setpoint - feedback;

	float proportional = m_kP * error;

	float integral = 0;
	for (int i = 0; i < PID_INTEGRAL_SIZE; i++) {
		integral += m_integral[i];
	}
	integral *= m_kI;

	float derivative = m_kD * (error - m_integral[m_index]);

	float output = proportional + integral + derivative;
	m_index = (m_index + 1) % PID_INTEGRAL_SIZE;
	m_integral[m_index] = output;

	return output;
}
