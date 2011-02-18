/*
 * ByteWriter.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef BYTEWRITER_H_
#define BYTEWRITER_H_

int WriteByte(unsigned char data[], unsigned char val, int offset);
int WriteUInt16(unsigned char data[], unsigned short val, int offset);
int writeBytes(unsigned char data[], int dataOffset, unsigned char val[], int count, int valOffset);
#endif /* BYTEWRITER_H_ */
