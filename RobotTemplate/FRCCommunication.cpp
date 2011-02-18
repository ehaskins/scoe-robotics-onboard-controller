/*
 * FRCCommunication.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "FRCCommunication.h"
#include "CommandData.h"
#include <Ethernet.h>
#include <Udp.h>
#include "UserConstants.h"
#include "Configuration.h"
FRCCommunication communication;

byte remoteIp[4]; // holds received packet's originating IP
unsigned int remotePort; // holds received packet's originating port


void FRCCommunication::init() {
	rsl.init(13);
	Serial.print("FRCComm socket #");
	Serial.println(socket.begin(config.controlReceivePort));
	communication.statusData.teamNumber = config.teamNumber;
	Serial.print("Control User Data ");
	Serial.print(USER_CONTROL_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(COMMAND_PACKET_SIZE);
	Serial.print("Status User Data ");
	Serial.print(USER_STATUS_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(STATUS_PACKET_SIZE);
	Serial.println("Communication init complete.");
	Serial.print("Control port:");
	Serial.print(config.controlReceivePort);
	Serial.print(" Status port:");
	Serial.println(config.statusTransmitPort);
}

int counter;
bool FRCCommunication::newDataReady() {
	int packetSize = socket.available(); // note that this includes the UDP header
	packetSize -= 8; //subtract the 8 byte header;
	if (packetSize == COMMAND_PACKET_SIZE) {
		// read the packet into packetBufffer and get the senders IP addr and port number
		socket.readPacket((char *)commandBytes, COMMAND_PACKET_SIZE, remoteIp, remotePort);

		lastPacketReceivedTime = millis();

		commandData.parse(commandBytes);

		//Implement E-Stop safety
		if (commandData.mode.getEStop()){
			if (!isEStoped){
				Serial.println("E-STOP SET");
			}
			isEStoped = true;
		}

		if (isEStoped){
			commandData.mode.setEStop(true);
			commandData.mode.setEnabled(false);
		}

		if (statusData.replyId > commandData.packetId && !commandData.mode.getResync()){
			Serial.print("Lower packet ID without resync: PacketID:");
			Serial.print(commandData.packetId);
			Serial.print(" Reply Id:");
			Serial.println(statusData.replyId);
			isConnected = false;
		}
		else{
			statusData.replyId = commandData.packetId;
			statusData.mode = commandData.mode;
		}
		return true;
	}
	else if (packetSize > 0){
		char garbage[2048];
		packetSize = packetSize <= 2048 ? packetSize : 2048;
		socket.readPacket(garbage, packetSize, remoteIp, remotePort);
		Serial.print("PacketSize:");
		Serial.println(packetSize);
	}

	unsigned long now = millis();
	if (lastPacketReceivedTime + PACKET_LOSS_TIMEOUT < now){ //No Comms
		isConnected = false;
	}

	if (!isConnected){
		commandData.mode.setEnabled(false);
	}

	rsl.update(isConnected, false, statusData.mode);

	return false;
}

void FRCCommunication::sendData() {
	counter++;

	isConnected = !commandData.mode.getResync();
	statusData.getResponseBytes(statusBytes);
	socket.sendPacket(statusBytes, STATUS_PACKET_SIZE, remoteIp, config.statusTransmitPort);
}
