#include <WProgram.h> //Include arduino headers


///CONSTANTS///
//The onboard test LED is connected to pin number 13
const int ledPin = 13;
const int interval = 250; //Milliseconds

///MAIN///
int main()
{
	//Initialize the Arduino library.
	//Not doing so will prevent the delay function
	//from working. Calling this functions is a must
	//for all arduino projects.
	init();

	//Initialize the serial port. This will be used
	//to send diagnostic information in this project.
	Serial.begin(9600);

	//Configure ledPin as an output
	pinMode(ledPin, OUTPUT);

	//Announce the start of program. Usually a
	//hyper-terminal is connected to the serial
	//port on the PC so this message can be seen
	//there
	Serial.println("Ready.");

	//Enter the infinite loop responsible for making
	//the microcontroller do the same thing over and
	//over again. (Almost every microcontroller has
	//such a loop)
	while(true)
	{
		//Turn on the LED
		digitalWrite(ledPin, HIGH);
		//Wait for half of "interval".
		//The LED remains ON during this time.
		delay(interval/2);
		//Turn off the LED
		digitalWrite(ledPin, LOW);
		//Wait for half of "interval".
		//The LED remains OFF during this time.
		delay(interval/2);
	}

	//Unreachable code but it's required by
	//the compiler
	return 0;
}
