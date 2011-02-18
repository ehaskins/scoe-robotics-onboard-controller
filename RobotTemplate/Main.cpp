#include <WProgram.h>
#include "UserCode.h"
#include "FRCCommunication.h"
#include "UserConstants.h"
#include "Configuration.h"
#include "Ethernet.h"
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

	config.init();
	Ethernet.begin(config.mac, config.robotIp, config.gatewayIp, config.subnetMask);
	Serial.print("Ethernet initialized. IP:");
	for (int i = 0; i < 4; i++){
		Serial.print((int)config.robotIp[i]);
		Serial.print(".");
	}
	Serial.print(" MAC:");
	for (int i = 0; i < 6; i++){
		Serial.print((int)config.mac[i]);
		Serial.print(" ");
	}
	Serial.println();
	config.netInit();
	communication.init();

	userInit();

	Serial.println("Ready.");
}



void loop() {
	config.poll();
	if (communication.newDataReady()){
		slowLoop();
		communication.sendData();
	}
	fastLoop();
}
