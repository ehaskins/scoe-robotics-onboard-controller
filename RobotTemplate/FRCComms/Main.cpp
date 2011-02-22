#include <WProgram.h>
#include "..\UserCode.h"
#include "..\UserConstants.h"
#include "FRCCommunication.h"
#include "Configuration.h"
#include "Ethernet.h"
#include "CRC32.h"

//const int interval = 250; //Milliseconds

int main() {
	//Initialize the Arduino library.
	//Not doing so will prevent the delay function
	//from working. Calling this functions is a must
	//for all arduino projects.
	setup();
	while (true) {
		loop();
	}
	//Unreachable code but it's required by
	//the compiler
	return 0;
}

void setup() {
	init();
	Serial.begin(9600);

	unsigned char buf[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	Serial.println(crc(buf, 10));

	config.init();
	Ethernet.begin(config.mac, config.robotIp, config.gatewayIp, config.subnetMask);
	Serial.print("Ethernet initialized. IP:");
	for (int i = 0; i < 4; i++){
		Serial.print((int)config.robotIp[i]);
		Serial.print(".");
	}
	Serial.print(" MAC:");
	for (int i = 0; i < 6; i++){
		Serial.print((int)config.mac[i], 16);
		if (i < 5) Serial.print(":");
	}
	Serial.println();
	config.netInit();
	communication.init();

	userInit();

	Serial.println("Ready.");
}

unsigned long lastLoopTime = 0;
unsigned long nextLoopTime = 0;
unsigned long fixedLoopPeriod = 0;
void loop() {
	config.poll();
	if (communication.newDataReady()){
		commLoop();
		communication.sendData();
	}
	unsigned long now = millis();
	if (nextLoopTime == 0)
	{
		fixedLoopPeriod = 1000/FIXED_LOOP_FREQUENCY;
		nextLoopTime = now;
		lastLoopTime = 0;
	}
	if (now >= nextLoopTime){
		fixedLoop(now - nextLoopTime, now - lastLoopTime);
		nextLoopTime += fixedLoopPeriod;
		lastLoopTime = now;
	}
	fastLoop();
}
