/*
 * BitField8.h
 *
 *  Created on: Feb 12, 2011
 *      Author: EHaskins
 */

#ifndef BITFIELD8_H_
#define BITFIELD8_H_

/*class BitField8 {
private:
	unsigned char value;
	unsigned char GetMask(int);
public:
	BitField8();

	bool GetBit(int);
	void SetBit(int, bool);

	unsigned char GetValue();
	void SetValue(unsigned char value);
};*/
struct BitField8{
private:
	unsigned char getBitMask(int);
public:
	unsigned char data;

	bool getBit(int);
	void setBit(int, bool);
};


#endif /* BITFIELD8_H_ */
