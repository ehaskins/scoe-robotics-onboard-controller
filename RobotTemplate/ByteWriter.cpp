/*
 * ByteWriter.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "ByteWriter.h"
int WriteByte(unsigned char data[], unsigned char val, int offset){
	data[offset] = val;
	return offset + 1;
}
int WriteUInt16(unsigned char data[], unsigned short val, int offset){

	data[offset] = (unsigned char)(val >> 8);
	data[offset + 1] = (unsigned char)val;
	return offset + 2;
}
int writeBytes(unsigned char data[], int dataOffset, unsigned char val[], int count, int valOffset){
	for (int i = 0; i < count; i++){
		data[i + dataOffset] = val[i + valOffset];
	}
	return dataOffset + count;
}
