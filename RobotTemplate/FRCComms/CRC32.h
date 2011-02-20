/*
 * CRC32.h
 *
 *  Created on: Feb 19, 2011
 *      Author: EHaskins
 */

#ifndef CRC32_H_
#define CRC32_H_

struct CRC32 {
private:
	unsigned long seed;
	unsigned long polynomial;
	unsigned long table[256];
public:
	void init();
	unsigned long compute(unsigned char data[], int offset, int count);
	void initializeTable();
};
extern CRC32 CRC;
#endif /* CRC32_H_ */
