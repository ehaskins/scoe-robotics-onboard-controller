/*
 * FrcNetworkCommunication.cpp
 *
 *  Created on: Apr 28, 2011
 *      Author: EHaskins
 */

#include "FrcNetworkCommunication.h"

FrcNetworkCommunication* FrcNetworkCommunication::instance;
FrcNetworkCommunication* FrcNetworkCommunication::getInstance(){
	if (!instance)
		instance = new FrcNetworkCommunication();
	return instance;
}
void FrcNetworkCommunication::init(){
	Serial.print("FRCComm socket #");
	Serial.println(socket.begin(config->controlReceivePort));
	Serial.print("Control port:");
	Serial.print(config->controlReceivePort);
	Serial.print(" Status port:");
	Serial.println(config->statusTransmitPort);
	FRCCommunication::init();
}
bool FrcNetworkCommunication::dataAvailable(){
	int packetSize = socket.available(); // note that this includes the UDP header
	//bool droppedPacket = false;
	packetSize -= 8; //subtract the 8 byte header;
	if (packetSize == CONTROL_PACKET_SIZE){
		return true;
	}
	else if (packetSize > 0){
		char garbage[2048];
		packetSize = packetSize <= 2048 ? packetSize : 2048;
		socket.readPacket(garbage, packetSize, remoteIp, remotePort);
//		Serial.print("PacketSize:");
//		Serial.println(packetSize);
		Serial.print('*');
		//droppedPacket = true;
	}
	return false;
}
void FrcNetworkCommunication::receiveData(unsigned char buffer[]){
	// read the packet into packetBufffer and get the senders IP addr and port number
	socket.readPacket((char *)buffer, CONTROL_PACKET_SIZE, remoteIp, remotePort);
}
void FrcNetworkCommunication::transmitData(unsigned char buffer[]){
	socket.sendPacket(buffer, STATUS_PACKET_SIZE, remoteIp, config->statusTransmitPort);
}
