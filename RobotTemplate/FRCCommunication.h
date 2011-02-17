/*
 * FRCCommunication.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */
#include "CommandData.h"
#include "StatusData.h"
#include "RobotStatusLight.h"

#ifndef FRCCOMMUNICATION_H_
#define FRCCOMMUNICATION_H_



const int PACKET_LOSS_TIMEOUT = 1000;

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
	RobotStatusLight rsl;
	unsigned long lastPacketReceivedTime;

	unsigned char commandBytes[COMMAND_PACKET_SIZE];
	unsigned char statusBytes[STATUS_PACKET_SIZE];
};

extern FRCCommunication communication;
#endif /* FRCCOMMUNICATION_H_ */
