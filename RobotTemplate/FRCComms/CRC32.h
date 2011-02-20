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
	unsigned int seed;
	unsigned int polynomial;
	unsigned int table[256];
public:
	void init();
	unsigned int compute(unsigned char data[], int offset, int count);
	void initializeTable();
};
extern CRC32 CRC;
#endif /* CRC32_H_ */
