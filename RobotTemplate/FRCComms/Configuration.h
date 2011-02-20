/*
 * Configuration.h
 *
 *  Created on: Feb 18, 2011
 *      Author: EHaskins
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Udp.h>
#include <WProgram.h>

static const int INITIALIZED = 101;
static const int CONFIG_DATA_SIZE = 22;

struct Configuration {
private:
	byte remoteIp[4]; // holds received packet's originating IP
	unsigned int remotePort; // holds received packet's originating port
	UdpClass socket;
	void writeData(void);
	void loadData(void);
	void loadData(unsigned char data[]);
	void initStorage(void);
	int offset;
public:
	void init(void);
	void netInit(void);
	void poll(void);

	unsigned short deviceId;

	byte mac[6];
	byte network;
	byte robotHostIp;
	byte robotIp[4];
	byte subnetMask[4];
	byte gatewayIp[4];

	unsigned short teamNumber;

	unsigned short statusTransmitPort;
	unsigned short controlReceivePort;
};
extern Configuration config;
#endif /* CONFIGURATION_H_ */
