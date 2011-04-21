/*
 * BallLauncher.h
 *
 *  Created on: Apr 21, 2011
 *      Author: Nick
 */

#ifndef BALLLAUNCHER_H_
#define BALLLAUNCHER_H_

#include "ILaunchSystem.h"
#include <string.h>

class BallLauncher : public ILaunchSystem {
private:
	bool m_enabled;
	IDigitalInput* m_pLoadSwitch;
	IDigitalInput* m_pIntakeSwitch;
	IMotor* m_pLauncher;
	IMotor* m_pIntake;

public:
	BallLauncher() :m_enabled(false), m_pLoadSwitch(NULL), m_pIntakeSwitch(NULL), m_pLauncher(NULL), m_pIntake(NULL) {}

	void init(int port) {}
	void init(IDigitalInput* loadSwitch, IDigitalInput* intakeSwitch, IMotor* launcher, IMotor* intake) {
		m_pLoadSwitch = loadSwitch;
		m_pIntakeSwitch = intakeSwitch;
		m_pLauncher = launcher;
		m_pIntake = intake;
	}
	void setEnabled(bool enable) {
		m_pLoadSwitch->setEnabled(enable);
		m_pIntakeSwitch->setEnabled(enable);
		m_pLauncher->setEnabled(enable);
		m_pIntake->setEnabled(enable);
	}
	bool isEnabled() const {
		return (m_pLoadSwitch->isEnabled() && m_pIntakeSwitch->isEnabled() && m_pLauncher->isEnabled() && m_pIntake->isEnabled());
	}

	IDigitalInput* getLoadSwitch() const { return m_pLoadSwitch; }
	IDigitalInput* getIntakeSwitch() const { return m_pIntakeSwitch; }
	IMotor* getLauncher() const { return m_pLauncher; }
	IMotor* getIntake() const { return m_pIntake; }

	void setIdleSpeeds(int launchSpeed, int intakeSpeed) {
		m_pLauncher->setIdle(launchSpeed);
		m_pIntake->setIdle(intakeSpeed);
	}

	bool isLoaded() {
		return m_pLoadSwitch->getValue();
	}

	bool isIntakePrimed() {
		return m_pIntakeSwitch->getValue();
	}

	void driveIntake(int speed) {
		m_pIntake->setSpeed(speed);
	}

	void driveLauncher(int speed) {
		m_pLauncher->setSpeed(speed);
	}
};

#endif /* BALLLAUNCHER_H_ */
