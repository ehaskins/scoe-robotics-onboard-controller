/*
 * FRCCommunication.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "FRCCommunication.h"
#include "FrcNetworkCommunication.h"
#include "ControlData.h"
#include "../Ethernet.h"
#include "../Udp.h"
#include "CommConstants.h"
#include "Configuration.h"
#include "cpp.h"

void FRCCommunication::init() {
	rsl.init(13);
	config = Configuration::getInstance();
	statusData = new StatusData();
	controlData = new ControlData();
	statusData->teamNumber = config->teamNumber;
	Serial.print("Control User Data ");
	Serial.print(USER_CONTROL_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(CONTROL_PACKET_SIZE);
	Serial.print("Status User Data ");
	Serial.print(USER_STATUS_DATA_SIZE);
	Serial.print("bytes, with a total size of ");
	Serial.println(STATUS_PACKET_SIZE);
	Serial.println("Communication init complete.");
}
bool FRCCommunication::dataAvailable(){
	return false;
}
void FRCCommunication::receiveData(unsigned char buffer[]){
	return;
}
void FRCCommunication::transmitData(unsigned char buffer[]){
	return;
}
bool FRCCommunication::newDataReady() {
	counter++;

	rsl.update(isConnected, false, statusData->mode);


	if (dataAvailable()) {
		receiveData(commandBytes);

		lastPacketReceivedTime = millis();

		controlData->parse(commandBytes);

		if (!controlData->isValid){
			isConnected = false;
			Serial.println("Invalid packet received.");
		}

		//Implement E-Stop safety
		if (controlData->mode.getEStop()){
			if (!isEStoped){
				Serial.println("E-STOP SET");
			}
			isEStoped = true;
		}

		if (isEStoped){
			controlData->mode.setEStop(true);
			controlData->mode.setEnabled(false);
		}

		if (statusData->replyId > controlData->packetId && !controlData->mode.getResync()){
			Serial.print("Lower packet ID without resync: PacketID:");
			Serial.print(controlData->packetId);
			Serial.print(" Reply Id:");
			Serial.println(statusData->replyId);
			isConnected = false;
		}
		else{
			statusData->replyId = controlData->packetId;
			statusData->mode = controlData->mode;
		}
		return true;
	}

	unsigned long now = millis();
	if (lastPacketReceivedTime + PACKET_LOSS_TIMEOUT < now){ //No Comms
		isConnected = false;
	}

	if (!isConnected){
		controlData->mode.setEnabled(false);
	}

	return false;
}

void FRCCommunication::sendData() {
	isConnected = !controlData->mode.getResync();
	statusData->getResponseBytes(statusBytes);
	transmitData(statusBytes);
}
