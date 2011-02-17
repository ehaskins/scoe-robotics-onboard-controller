/*
 * StatusData.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef STATUSDATA_H_
#define STATUSDATA_H_

#include "BitField8.h"
#include "Joystick.h"
#include "Mode.h"
#include "CommandData.h"

const static int STATUS_HEADER_SIZE = 32;
const static int STATUS_PACKET_SIZE = STATUS_HEADER_SIZE + USER_STATUS_DATA_SIZE + 8;

struct StatusData {
public:
	Mode mode;
	unsigned int replyId;
	unsigned char robotMac[6];
	unsigned short teamNumber;
	unsigned char batteryVoltageInt;
	unsigned char batteryVoltageFrac;
	BitField8 dsOutputs;
	unsigned char fpgaVersion[8];
	bool codeRunning;

	void updateResponse(CommandData*);
	void getResponseBytes(unsigned char[]);
};

#endif /* STATUSDATA_H_ */
