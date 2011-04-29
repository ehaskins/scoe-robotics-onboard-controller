/*
 * FrcSerialCommunication.h
 *
 *  Created on: Apr 28, 2011
 *      Author: EHaskins
 */

#ifndef FRCSERIALCOMMUNICATION_H_
#define FRCSERIALCOMMUNICATION_H_

#include "FRCCommunication.h"

class FrcSerialCommunication : public FRCCommunication {
private:
	unsigned int headerPosition;
	unsigned char packetStart[4];
	static FrcSerialCommunication *instance;
public:
	static FrcSerialCommunication *getInstance();
	virtual void init();
	virtual bool dataAvailable();
	virtual void receiveData(unsigned char buffer[]);
	virtual void transmitData(unsigned char buffer[]);
};

#endif /* FRCSERIALCOMMUNICATION_H_ */
