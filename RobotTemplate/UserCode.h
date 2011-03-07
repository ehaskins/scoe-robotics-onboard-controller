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

void teleopInit(void);
void teleopLoop(void);
void disabledInit(void);
void disabledLoop(void);
void autonomousInit(void);
void autonomousLoop(void);
void fixedLoop(int delayed, int elapsed);
void userInit(void);
void setOutputsEnabled(bool enabled);
int deadband(int value, int deadband);
#endif /* USERCODE_H_ */
