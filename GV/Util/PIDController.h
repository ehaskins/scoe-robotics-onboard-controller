/*
 * PIDController.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef PIDCONTROLLER_H_
#define PIDCONTROLLER_H_

#include "IController.h"

#define PID_INTEGRAL_SIZE	10

class PIDController : public IController {
private:
	float m_integral[PID_INTEGRAL_SIZE];
	int m_index;

	float m_kP;
	float m_kI;
	float m_kD;

public:
	PIDController(float idle);
	virtual ~PIDController();

	void fill(float fill) {
		for (int i = 0; i < PID_INTEGRAL_SIZE; i++) {
			m_integral[i] = fill;
		}
	}

	inline float getKP() const { return m_kP; }
	inline float getKI() const { return m_kI; }
	inline float getKD() const { return m_kD; }

	inline void setKP(float kp) { m_kP = kp; }
	inline void setKI(float ki) { m_kI = ki; }
	inline void setKD(float kd) { m_kD = kd; }

	float control(float setpoint, float feedback);
};

#endif /* PIDCONTROLLER_H_ */
