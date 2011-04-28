/*
 * Utils.h
 *
 *  Created on: Apr 4, 2011
 *      Author: EHaskins
 */

#ifndef UTILS_H_
#define UTILS_H_

int deadband(int value, int deadband);

float Vector_Dot_Product(float vector1[3],float vector2[3]);
void Vector_Cross_Product(float vectorOut[3], float v1[3],float v2[3]);
void Vector_Scale(float vectorOut[3],float vectorIn[3], float scale2);
void Vector_Add(float vectorOut[3],float vectorIn1[3], float vectorIn2[3]);
void Matrix_Multiply(float a[3][3], float b[3][3],float mat[3][3]);		//Function developed by Jordi of DIYDrones and is used under the Creative Commons 3.0 License

long parsedecimal(char *str,byte num_car);

#endif /* UTILS_H_ */
