/*
 * RobotStatusLight.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: EHaskins
 */

#include "RobotStatusLight.h"
#include <WProgram.h>

/*
Solid ON = Autonomous Enabled

Solid ON, but blinks OFF every 1.5s = Teleoperated Enabled

Slow Blink (900ms on/ 900ms off) = System Disabled; caused by system watchdog, user watchdog or Driver's Station set to disabled

Fast-Slow Blink (200ms on/900ms off) = Low Battery (<12V) or no user code AND system disabled either by system watchdog, user watchdog, or Driver;s station set to disabled

Fast Blink (200ms on/200ms off) = System error: No driver's station communication, bad cRIO Image, bad team ID, extensive comm. error
 */

void RobotStatusLight::init(int pin){
	ledPin = pin;
	pinMode(ledPin, OUTPUT);
	lastStateChangeTime = millis();
}

void RobotStatusLight::update(bool connected, Mode mode){
	if (connected){
		if (mode.getEnabled()){
			if(mode.getAutonomous()){
				onPeriod = 1500;
				offPeriod = 0;
			}
			else{
			onPeriod = 1500;
			offPeriod = 100;
			}
		}
		else{
			onPeriod = 900;
			offPeriod = 900;
		}
	}
	else{
		onPeriod = 200;
		offPeriod = 200;
	}

	unsigned int period = currentState ? onPeriod : offPeriod;
	unsigned long now = millis();
	unsigned long elapsed = now - lastStateChangeTime;
	if (elapsed >= period){
		lastStateChangeTime = now;
		currentState = !currentState;
		digitalWrite(ledPin, currentState ? HIGH : LOW);
	}
}
