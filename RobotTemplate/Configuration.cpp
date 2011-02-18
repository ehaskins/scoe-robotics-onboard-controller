/*
 * Configuration.cpp
 *
 *  Created on: Feb 18, 2011
 *      Author: EHaskins
 */

#include "Configuration.h"
#include "ByteWriter.h"
#include "ByteReader.h"
#include <EEPROM.h>
Configuration config;

void Configuration::init(void){
	offset = 3;
	if (EEPROM.read(0) == INITIALIZED){
		loadData();
	}
	else{
		initStorage();
	}
	Serial.print("Device ID:");
	Serial.println(deviceId);
}
void Configuration::initStorage(){
	Serial.print("EEPROM Initializing...");
	randomSeed(analogRead(0));
	deviceId = (unsigned short)random(0xFFFF);

	mac[0] = 0x90;
	mac[1] = 0xA2;
	mac[2] = 0xDA;
	mac[3] = 0x00;
	mac[4] = 0x30;
	mac[5] = 0x98;

	network = 172;
	robotHostIp = 198;

	subnetMask[0] = 255;
	subnetMask[1] = 255;
	subnetMask[2] = 255;
	subnetMask[3] = 0;

	gatewayIp[0] = 0;
	gatewayIp[1] = 0;
	gatewayIp[2] = 0;
	gatewayIp[3] = 0;

	teamNumber = 1692;

	statusTransmitPort = 1150;
	controlReceivePort = 1140;

	writeData();

	Serial.println(" COMPLETE!");
}
void Configuration::loadData(){
	byte deviceIdBytes[2];
	for(int i = 0; i < 2; i++){
		deviceIdBytes[i] = EEPROM.read(i + 1);
	}
	int temp = 0;
	deviceId = readUInt16(deviceIdBytes, &temp);

	byte data[CONFIG_DATA_SIZE];
	for(int i = 0; i < CONFIG_DATA_SIZE; i++){
		data[i] = EEPROM.read(i + offset);
	}
	loadData(data);
}
void Configuration::writeData(){
	byte deviceIdBytes[2];
	WriteUInt16(deviceIdBytes, deviceId, 0);
	EEPROM.write(0, INITIALIZED);

	for(int i = 0; i < 2; i++){
		EEPROM.write(i + 1, deviceIdBytes[i]);
	}

	byte data[CONFIG_DATA_SIZE];
	int dataOffset = 0;
	dataOffset = WriteUInt16(data, teamNumber, dataOffset);
	dataOffset = writeBytes(data, dataOffset, mac, 6, 0);
	data[dataOffset] = network; dataOffset++;
	data[dataOffset] = robotHostIp; dataOffset++;
	dataOffset = writeBytes(data, dataOffset, gatewayIp, 4, 0);
	dataOffset = writeBytes(data, dataOffset, subnetMask, 4, 0);
	dataOffset = WriteUInt16(data, statusTransmitPort, dataOffset);
	dataOffset = WriteUInt16(data, controlReceivePort, dataOffset);

	for(int i = 0; i < CONFIG_DATA_SIZE; i++){
		EEPROM.write(i + offset, data[i]);
	}
}

void Configuration::loadData(unsigned char data[]){
	int dataOffset = 0;

	teamNumber = readUInt16(data, &dataOffset);
	readBytes(data, mac, 6, &dataOffset);
	network = data[dataOffset]; dataOffset++;
	robotHostIp = data[dataOffset]; dataOffset++;
	readBytes(data, subnetMask, 4, &dataOffset);
	readBytes(data, gatewayIp, 4, &dataOffset);
	statusTransmitPort = readUInt16(data, &dataOffset);
	controlReceivePort = readUInt16(data, &dataOffset);

	robotIp[0] = network;
	robotIp[1] = teamNumber / 100;
	robotIp[2] = teamNumber % 100;
	robotIp[3] = robotHostIp;
}
void Configuration::netInit(void){
	Serial.print("Configuration socket #");
	Serial.println(socket.begin(1000));
}

void Configuration::poll(void){
	int packetSize = socket.available();
	packetSize -= 8;
	if (packetSize == 3){//Discovery packet
		unsigned char request[3];
		socket.readPacket((char *)request, 3, remoteIp, remotePort);

		byte response[] = {0, 0, config.mac[0], config.mac[1], config.mac[2], config.mac[3], config.mac[4], config.mac[5]};
		WriteUInt16(response, config.teamNumber, 0);
		Serial.println("Config discovery packet received.");
		unsigned char ip[4] = {0xff, 0xff, 0xff, 0xff};
		socket.sendPacket(response, 8, ip, 1001);
	}
	else if (packetSize == CONFIG_DATA_SIZE + 2){
		unsigned char request[CONFIG_DATA_SIZE + 2];
		socket.readPacket((char *)request, CONFIG_DATA_SIZE + 2, remoteIp, remotePort);
		Serial.println("Configuration update request received.");
		unsigned short id = readUInt16(request, 0);
		if (id == deviceId){
			Serial.print("Updating configuration...");
			unsigned char data[CONFIG_DATA_SIZE];
			int temp = 2;
			readBytes(request, data, CONFIG_DATA_SIZE, &temp);
			loadData(data);
			writeData();
			Serial.print(" Complete!");

		}
	}
}
