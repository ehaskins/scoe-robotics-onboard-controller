/*
 * UserCode.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef USERCODE_H_
#define USERCODE_H_


void fastLoop(void);
void commLoop(void);
void fixedLoop(int delayed, int elapsed);
void userInit(void);
void setOutputsEnabled(bool enabled);
int deadband(int value, int deadband);
#endif /* USERCODE_H_ */
