/*
 * CommandData.cpp
 *
 *  Created on: Feb 12, 2011
 *      Author: EHaskins
 */

#include "CommandData.h"
#include "ByteReader.h"

	/*CommandData::CommandData(){
		for (int i = 0; i < NUM_JOYSTICKS; i++){
			Joystick *temp = new Joystick();
			Joysticks[i] = temp;
		}
	}*/

	void CommandData::parse(unsigned char data[]){
		//CommandData out;

		int offset = 0;
		packetId = readUInt16(data, &offset);
		mode.data.data = readUInt8(data, &offset);
		dsInputs = readUInt8(data, &offset);
		teamNumber = readUInt16(data, &offset);
		alliance = readUInt8(data, &offset);
		position = readUInt8(data, &offset);
		//TODO:Read joysticks.
		for (int i = 0; i < 4; i++){
			joysticks[i].parse(data, &offset);
		}

		cRioChecksum = readUInt64(data, &offset);
		fpgaChecksum0 = readUInt32(data, &offset);
		fpgaChecksum1 = readUInt32(data, &offset);
		fpgaChecksum2 = readUInt32(data, &offset);
		fpgaChecksum3 = readUInt32(data, &offset);

		//TODO:Read version.

		//TODO:Verify Checksum

	}
