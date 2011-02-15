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
		packetId = ReadUInt16(data, &offset);
		mode.data.data = ReadUInt8(data, &offset);
		dsInputs = ReadUInt8(data, &offset);
		teamNumber = ReadUInt16(data, &offset);
		alliance = ReadUInt8(data, &offset);
		position = ReadUInt8(data, &offset);
		//TODO:Read joysticks.
		offset += 8*4;//8 bytes/sitck * 4 sticks

		cRioChecksum = ReadUInt64(data, &offset);
		fpgaChecksum0 = ReadUInt32(data, &offset);
		fpgaChecksum1 = ReadUInt32(data, &offset);
		fpgaChecksum2 = ReadUInt32(data, &offset);
		fpgaChecksum3 = ReadUInt32(data, &offset);

		//TODO:Read version.

		//TODO:Verify Checksum

	}
