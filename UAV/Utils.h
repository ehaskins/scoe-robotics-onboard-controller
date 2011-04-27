/*
 * Utils.h
 *
 *  Created on: Apr 4, 2011
 *      Author: EHaskins
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <WProgram.h>

int deadband(int value, int deadband);
int restrict(int oldValue, int newValue, int maxShift);

/**
template <typename T>
T deadband(T val, T max, T min, T db, T center) {
	if ((val < (max - db)) && (val > (min + db))) {
		if (val > (center + db)) {
			val -= db;
		} else if (val < (center - db)) {
			val += db;
		} else {
			val = center;
		}
	}
	return val;
}
*/

// For reference, I have included the above code.
//#define DEADBAND(v,max,min,db,c)	\
//	(((v)<((max)-(db)))&&((v)>((min)+(db))))?\
//		(((v)>((c)+(db)))?\
//			(((v)-(db))):\
//		(((v)<((c)-(db)))?\
//			((v)+(db)):\
//		((c)))):\
//	((v))

#endif /* UTILS_H_ */
