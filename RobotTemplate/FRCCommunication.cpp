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

FRCCommunication communication;

// UDP library from: bjoern@cs.stanford.edu 12/30/2008
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:


// the next two variables are set when a packet is received
byte remoteIp[4]; // holds received packet's originating IP
unsigned int remotePort; // holds received packet's originating port

// buffers for receiving and sending data

void FRCCommunication::init(short teamNumber) {
	rsl.init(13);
	byte ip[] = {ROBOT_NETWORK, teamNumber / 100, teamNumber % 100, ROBOT_IP};
	Ethernet.begin(MAC, ip, GATEWAY, SUBNET);
	Udp.begin(COMMAND_PACKET_PORT);

	communication.statusData.teamNumber = teamNumber;
	Serial.print("Control User Data ");
	Serial.print(USER_CONTROL_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(COMMAND_PACKET_SIZE);
	Serial.print("Status User Data ");
	Serial.print(USER_STATUS_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(STATUS_PACKET_SIZE);
	Serial.println("Communication init complete.");
}

int counter;
bool FRCCommunication::newDataReady() {
	int packetSize = Udp.available(); // note that this includes the UDP header

	packetSize -= 8; //subtract the 8 byte header;
	if (packetSize == COMMAND_PACKET_SIZE) {

		// read the packet into packetBufffer and get the senders IP addr and port number
		Udp.readPacket((char *)commandBytes, COMMAND_PACKET_SIZE, remoteIp, remotePort);

		lastPacketReceivedTime = millis();

		commandData.parse(commandBytes);

		/*if (counter % 10 == 0) {
			Serial.print("COMMAND: Packet ID:");
			Serial.print(commandData.packetId);
			Serial.print(" Mode:");
			Serial.print((int) commandData.mode.data.data);
			Serial.print(" Team:");
			Serial.println((int) commandData.teamNumber);
		}*/

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

		statusData.replyId = commandData.packetId;
		statusData.mode = commandData.mode;

		return true;
	}
	else if (packetSize > 0){
		char garbage[2048];
		Udp.readPacket(garbage, 2048, remoteIp, remotePort);
		Serial.print("PacketSize:");
		Serial.println(packetSize);
	}
	else{

	}

	unsigned long now = millis();
	if (lastPacketReceivedTime + PACKET_LOSS_TIMEOUT < now){ //No Comms
		isConnected = false;
		commandData.mode.setEnabled(false);
	}

	rsl.update(isConnected, statusData.mode);

	return false;
}

void FRCCommunication::sendData() {
	/*if (counter % 10 == 0) {
		Serial.print("STATUS: Reply ID:");
		Serial.print(statusData.replyId);
		Serial.print(" Mode:");
		Serial.print((int) commandData.mode.data.data);
		Serial.print(" Team:");
		Serial.println((int) commandData.teamNumber);
	}*/

	counter++;

	if (statusData.replyId > commandData.packetId && !commandData.mode.getResync()){
		Serial.print("Lower packet ID without resync: PacketID:");
		Serial.print(commandData.packetId);
		Serial.print(" Reply Id:");
		Serial.println(statusData.replyId);
		isConnected = false;
		return;
	}

	isConnected = !commandData.mode.getResync();
	statusData.getResponseBytes(statusBytes);
	Udp.sendPacket(statusBytes, STATUS_PACKET_SIZE, remoteIp, STATUS_PACKET_PORT);
}
