/*
 * FRCCommunication.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */
#include "CommandData.h"
#include "StatusData.h"

#ifndef FRCCOMMUNICATION_H_
#define FRCCOMMUNICATION_H_

const int STATUS_PACKET_PORT = 1150;
const int COMMAND_PACKET_PORT = 1140;
struct FRCCommunication{
public:
	unsigned char mac[6];
	unsigned char ip[4];
	unsigned char subnet[4];
	unsigned char gateway[4];

	void init(short);
	bool newDataReady(void);
	void sendData(void);

	bool isConnected;
	bool isEStoped;
	CommandData commandData;
	StatusData statusData;
	unsigned char commandBytes[COMMAND_PACKET_SIZE];
	unsigned char statusBytes[STATUS_PACKET_SIZE];
};

extern FRCCommunication communication;
#endif /* FRCCOMMUNICATION_H_ */
