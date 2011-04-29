/*
 * FrcSerialCommunication.cpp
 *
 *  Created on: Apr 28, 2011
 *      Author: EHaskins
 */

#include "FrcSerialCommunication.h"

FrcSerialCommunication *FrcSerialCommunication::instance;
FrcSerialCommunication *FrcSerialCommunication::getInstance() {
	if (!instance)
		instance = new FrcSerialCommunication();
	return instance;
}
void FrcSerialCommunication::init() {
	packetStart[0] = 255;
	packetStart[1] = 254;
	packetStart[2] = 253;
	packetStart[3] = 252;

	CommSerial.begin(9600);
}
bool FrcSerialCommunication::dataAvailable() {
	while (CommSerial.available()) {
		Serial.println(CommSerial.available());
		if (headerPosition == 4){
			if (CommSerial.available() > CONTROL_PACKET_SIZE)
				return true;
			else
				return false;
		}

		if (CommSerial.read() == (int) packetStart[headerPosition])
			headerPosition++;
		else
			headerPosition = 0;
	}
	return false;
}
void FrcSerialCommunication::receiveData(unsigned char buffer[]) {
	for (int i = 0; i < CONTROL_PACKET_SIZE; i++){
		buffer[i] = CommSerial.read();
	}
}
void FrcSerialCommunication::transmitData(unsigned char buffer[]) {
	for (int i = 0; i < CONTROL_PACKET_SIZE; i++){
		CommSerial.write(buffer[i]);
	}
}
