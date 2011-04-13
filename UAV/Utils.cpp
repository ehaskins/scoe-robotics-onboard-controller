/*
 * Utils.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: EHaskins
 */

#include "Utils.h"

int deadband(int value, int deadband) {
	if (value < 127-deadband && value > -128+deadband){
		if (value > deadband){
			value -= deadband;
		}
		else if (value < -deadband){
			value += deadband;
		}
		else{
			value = 0;
		}
	}
	return value;
}

int restrict(int oldValue, int newValue, int maxShift) {
	int shift = min(abs(maxShift), abs(newValue - oldValue));
	if (newValue < oldValue) {
		shift = -shift;
	}
	return oldValue + shift;
}
