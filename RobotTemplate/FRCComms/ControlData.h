/*
 * CommandData.h
 *
 *  Created on: Feb 12, 2011
 *      Author: EHaskins
 */

#include "BitField8.h"
#include "Joystick.h"
#include "Mode.h"
#include "..\UserConstants.h"
#ifndef COMMANDDATA_H_
#define COMMANDDATA_H_
const int NUM_JOYSTICKS = 4;
const static int COMMAND_HEADER_SIZE = 80;
const static int COMMAND_PACKET_SIZE = COMMAND_HEADER_SIZE + USER_CONTROL_DATA_SIZE + 8;

struct ControlData {
	void parse(unsigned char[]);

	unsigned short packetId;
	Mode mode;
	unsigned char dsInputs;
	int teamNumber;
	unsigned char alliance;
	unsigned char position;
	Joystick joysticks[NUM_JOYSTICKS];
	unsigned long cRioChecksum;
	unsigned int fpgaChecksum0;
	unsigned int fpgaChecksum1;
	unsigned int fpgaChecksum2;
	unsigned int fpgaChecksum3;
	char version[8];
	bool isValid;
};


#endif /* COMMANDDATA_H_ */
