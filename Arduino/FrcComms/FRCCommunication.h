/*
 * FRCCommunication.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef FRCCOMMUNICATION_H_
#define FRCCOMMUNICATION_H_

#include "ControlData.h"
#include "StatusData.h"
#include "RobotStatusLight.h"
#include "Configuration.h"

const int PACKET_LOSS_TIMEOUT = 1000;

class FRCCommunication{
private:
	int counter;

	virtual bool dataAvailable();
	virtual void receiveData(unsigned char buffer[]);
	virtual void transmitData(unsigned char buffer[]);
protected:
	Configuration *config;
public:

	virtual void init();
	bool newDataReady(void);
	void sendData(void);

	bool isConnected;
	bool isEStoped;
	ControlData *controlData;
	StatusData *statusData;
	RobotStatusLight rsl;
	unsigned long lastPacketReceivedTime;

	unsigned char commandBytes[CONTROL_PACKET_SIZE];
	unsigned char statusBytes[STATUS_PACKET_SIZE];
};
#endif /* FRCCOMMUNICATION_H_ */
