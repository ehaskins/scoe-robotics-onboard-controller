/*
 * Sonar.h
 *
 *  Created on: Apr 26, 2011
 *      Author: Ryan
 */

#ifndef SONAR_H_
#define SONAR_H_
int Get_Sonar_Pulse();
int Filter(int new_value, int old_value, int max_diff);

#endif /* SONAR_H_ */
