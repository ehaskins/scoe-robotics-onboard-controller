/*
 * StatusData.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "StatusData.h"
#include "ByteWriter.h"
#include "Configuration.h"

void StatusData::updateResponse(CommandData *data) {
	replyId = data->packetId;
	mode = data->mode;
}
void StatusData::getResponseBytes(unsigned char data[]) {
	int offset = 0;

	offset = WriteByte(data, mode.data.data, offset);
	offset = WriteByte(data, batteryVoltageInt, offset);
	offset = WriteByte(data, batteryVoltageFrac, offset);
	offset = WriteByte(data, dsOutputs.data, offset);

	for (int i = 0; i < 4; i++) {
		offset = WriteByte(data, 0, offset);
	}

	offset = WriteUInt16(data, teamNumber, offset);

	for (int i = 0; i < 6; i++) {
		offset = WriteByte(data, config.mac[i], offset);
	}

	for (int i = 0; i < 8; i++) {
		offset = WriteByte(data, fpgaVersion[i], offset);
	}

	for (int i = 0; i < 6; i++) { //Unknown pad
		offset = WriteByte(data, 0, offset);
	}

	offset = WriteUInt16(data, replyId, offset);
}

