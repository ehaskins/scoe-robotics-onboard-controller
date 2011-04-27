/*
 * BallLauncher.h
 *
 *  Created on: Apr 21, 2011
 *      Author: Nick
 */

#ifndef BALLLAUNCHER_H_
#define BALLLAUNCHER_H_

#include "ILaunchSystem.h"
#include "ServoMotor.h"
#include <string.h>
#include <WProgram.h>

class BallLauncher : public ILaunchSystem {
private:
	IDigitalInput* m_pLoadSwitch;
	IDigitalInput* m_pIntakeSwitch;
	ServoMotor m_launchServo;
	ServoMotor m_intakeServo;
	IMotor* m_pLauncher;
	IMotor* m_pIntake;
	int m_launchOpen, m_launchClosed;
	int m_intakeOpen, m_intakeClosed;

public:
	BallLauncher() :m_pLoadSwitch(NULL), m_pIntakeSwitch(NULL), m_launchServo(), m_intakeServo(), m_pLauncher(NULL), m_pIntake(NULL) {
		m_launchOpen = m_launchClosed = m_intakeOpen = m_intakeClosed = 0;
	}

	void init(int port) {}
	void init(IDigitalInput* loadSwitch, IDigitalInput* intakeSwitch, int launchServo, int intakeServo, IMotor* launcher, IMotor* intake) {
		// Initialize the switches.
		m_pLoadSwitch = loadSwitch;
		m_pIntakeSwitch = intakeSwitch;
		// Now the servos.
		m_launchServo.init(launchServo);
		m_intakeServo.init(intakeServo);
		// Now the motors.
		m_pLauncher = launcher;
		m_pIntake = intake;
	}
	void setEnabled(bool enable) {
		m_pLoadSwitch->setEnabled(enable);
		m_pIntakeSwitch->setEnabled(enable);
		m_launchServo.setEnabled(enable);
		m_intakeServo.setEnabled(enable);
		m_pLauncher->setEnabled(enable);
		m_pIntake->setEnabled(enable);
	}
	bool isEnabled() const {
		return (m_pLoadSwitch->isEnabled() && m_pIntakeSwitch->isEnabled() && m_launchServo.isEnabled() && m_intakeServo.isEnabled() && m_pLauncher->isEnabled() && m_pIntake->isEnabled());
	}

	IDigitalInput* getLoadSwitch() const { return m_pLoadSwitch; }
	IDigitalInput* getIntakeSwitch() const { return m_pIntakeSwitch; }

	IMotor* getLauncherServo() const { return (IMotor*)&m_launchServo; }
	IMotor* getIntakeServo() const { return (IMotor*)&m_intakeServo; }

	IMotor* getLauncherMotor() const { return m_pLauncher; }
	IMotor* getIntakeMotor() const { return m_pIntake; }

	void setIdleSpeeds(int launchSpeed, int intakeSpeed) {
		m_pLauncher->setIdle(launchSpeed);
		m_pIntake->setIdle(intakeSpeed);
	}

	void setLaunchServoPositions(int open, int closed) {
		m_launchOpen = open;
		m_launchClosed = closed;
	}

	void setIntakeServoPositions(int open, int closed) {
		m_intakeOpen = open;
		m_intakeClosed = closed;
	}

	bool isLoaded() {
		return m_pLoadSwitch->getValue();
	}

	bool isIntakePrimed() {
		return m_pIntakeSwitch->getValue();
	}

	void driveLauncher(int speed) {
		m_pLauncher->setSpeed(speed);
	}

	void driveIntake(int speed) {
		m_pIntake->setSpeed(speed);
	}

	void openIntake(bool open) {
		if (open) {
			m_intakeServo.setSpeed(m_intakeOpen);
		} else {
			m_intakeServo.setSpeed(m_intakeClosed);
		}
	}

	void openLauncher(bool open) {
		if (open) {
			m_launchServo.setSpeed(m_launchOpen);
		} else {
			m_launchServo.setSpeed(m_launchClosed);
		}
	}
};

#endif /* BALLLAUNCHER_H_ */
