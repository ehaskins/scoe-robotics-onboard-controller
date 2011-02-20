/*
 * ByteWriter.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "ByteWriter.h"
int writeByte(unsigned char data[], unsigned char val, int offset){
	data[offset] = val;
	return offset + 1;
}
int writeUInt16(unsigned char data[], unsigned short val, int offset){

	data[offset] = (unsigned char)(val >> 8);
	data[offset + 1] = (unsigned char)val;
	return offset + 2;
}
int writeUInt32(unsigned char data[], unsigned int val, int offset){
	data[offset] = (unsigned char)(val >> 24);
	data[offset + 1] = (unsigned char)(val >> 16);
	data[offset + 2] = (unsigned char)(val >> 8);
	data[offset + 3] = (unsigned char)val;
	return offset + 2;
}
int writeBytes(unsigned char data[], int dataOffset, unsigned char val[], int count, int valOffset){
	for (int i = 0; i < count; i++){
		data[i + dataOffset] = val[i + valOffset];
	}
	return dataOffset + count;
}
