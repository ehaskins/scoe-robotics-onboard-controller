/*
 * Joystick.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: EHaskins
 */
#include "Joystick.h"
#include "ByteReader.h"

void Joystick::parse(unsigned char data[], int *offset) {
	for (int i = 0; i < NUM_AXES; i++){
		axis[i] = readUInt8(data, offset);
	}
	buttons.data = readUInt16(data, offset);
}
