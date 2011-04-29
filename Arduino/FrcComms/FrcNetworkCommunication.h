/*
 * FrcNetworkCommunication.h
 *
 *  Created on: Apr 28, 2011
 *      Author: EHaskins
 */

#ifndef FRCNETWORKCOMMUNICATION_H_
#define FRCNETWORKCOMMUNICATION_H_
#include "FRCCommunication.h"

#include "../Udp.h"
class FrcNetworkCommunication : public FRCCommunication {
private:
	static FrcNetworkCommunication *instance;
	UdpClass socket;
	byte remoteIp[4]; // holds received packet's originating IP
	unsigned int remotePort; // holds received packet's originating port
public:
	static FrcNetworkCommunication *getInstance();
	unsigned char mac[6];
	unsigned char ip[4];
	unsigned char subnet[4];
	unsigned char gateway[4];


	virtual void init();
	virtual bool dataAvailable();
	virtual void receiveData(unsigned char buffer[]);
	virtual void transmitData(unsigned char buffer[]);
};

#endif /* FRCNETWORKCOMMUNICATION_H_ */
