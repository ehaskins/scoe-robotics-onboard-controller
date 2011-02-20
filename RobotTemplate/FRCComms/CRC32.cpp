/*
 * CRC32.cpp
 *
 *  Created on: Feb 19, 2011
 *      Author: EHaskins
 */

#include "CRC32.h"
#include <WProgram.h>
#include <stdio.h>

void CRC32::init() {
	polynomial = 0x04C11DB7;
	seed = 0xffffffff;
	initializeTable();
}
unsigned int CRC32::compute(unsigned char data[], int offset, int count) {
	unsigned int crc = seed;
	for (int i = offset; i < offset + count; i++) {
		crc = (crc >> 8) ^ table[data[i] ^ crc & 0xff];
	}
	return crc;
}

void CRC32::initializeTable() {
	for (unsigned int i = 0; i < 256; i++) {
		unsigned int entry = i;
		for (int j = 0; j < 8; j++)
			if ((entry & 1) == 1)
				entry = (entry >> 1) ^ polynomial;
			else
				entry = entry >> 1;

		table[i] = entry;
	}
}

CRC32 CRC;
