/*
 * ILaunchSystem.h
 *
 *  Created on: Apr 21, 2011
 *      Author: Nick
 */

#ifndef ILAUNCHSYSTEM_H_
#define ILAUNCHSYSTEM_H_

#include "IDevice.h"
#include "IDigitalInput.h"
#include "IMotor.h"

class ILaunchSystem : public IDevice {
public:
	// Initialization.
	virtual void init(IDigitalInput* loadSwitch, IDigitalInput* intakeSwitch, IMotor* launcher, IMotor* intake) = 0;

	// Components of the system.
	virtual IDigitalInput* getLoadSwitch() const = 0;
	virtual IDigitalInput* getIntakeSwitch() const = 0;
	virtual IMotor* getLauncher() const = 0;
	virtual IMotor* getIntake() const = 0;

	// Idle mode settings.
	virtual void setIdleSpeeds(int launchSpeed, int intakeSpeed) = 0;

	// Discrete controls.
	virtual bool isLoaded() = 0;
	virtual bool isIntakePrimed() = 0;
	virtual void driveIntake(int speed) = 0;
	virtual void driveLauncher(int speed) = 0;
};

#endif /* ILAUNCHSYSTEM_H_ */
