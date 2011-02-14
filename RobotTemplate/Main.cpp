#include <WProgram.h>
#include "UserCode.h"
#include "FRCCommunication.h"
#include "UserConstants.h"
const int ledPin = 13;
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
	//Initialize the serial port. This will be used
	//to send diagnostic information in this project.
	Serial.begin(9600);
	//Configure ledPin as an output
	pinMode(ledPin, OUTPUT);
	communication.init(TEAM_NUMBER);
	userInit();

	//Announce the start of program. Usually a
	//hyper-terminal is connected to the serial
	//port on the PC so this message can be seen
	//there
	Serial.println("Ready.");
}



void loop() {
	if (communication.newDataReady()){
		slowLoop();
		communication.sendData();
	}
	fastLoop();
}
