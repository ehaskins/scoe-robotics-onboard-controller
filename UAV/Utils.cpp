/*
 * Utils.cpp
 *
 *  Created on: Apr 4, 2011
 *      Author: EHaskins
 */
#include <WProgram.h>

int deadband(int value, int deadband){
	if (value < 127-deadband && value > -128+deadband){
		if (value > deadband){
			value -= deadband;
		}
		else if (value < -deadband){
			value += deadband;
		}
		else{
			value = 0;
		}
	}
	return value;
}






//Computes the dot product of two vectors
float Vector_Dot_Product(float vector1[3],float vector2[3])
{
  float op=0;

  for(int c=0; c<3; c++)
  {
  op+=vector1[c]*vector2[c];
  }

  return op;
}

//Computes the cross product of two vectors
void Vector_Cross_Product(float vectorOut[3], float v1[3],float v2[3])
{
  vectorOut[0]= (v1[1]*v2[2]) - (v1[2]*v2[1]);
  vectorOut[1]= (v1[2]*v2[0]) - (v1[0]*v2[2]);
  vectorOut[2]= (v1[0]*v2[1]) - (v1[1]*v2[0]);
}

//Multiply the vector by a scalar.
void Vector_Scale(float vectorOut[3],float vectorIn[3], float scale2)
{
  for(int c=0; c<3; c++)
  {
   vectorOut[c]=vectorIn[c]*scale2;
  }
}

void Vector_Add(float vectorOut[3],float vectorIn1[3], float vectorIn2[3])
{
  for(int c=0; c<3; c++)
  {
     vectorOut[c]=vectorIn1[c]+vectorIn2[c];
  }
}

//Multiply two 3x3 matrixs.
//This function was developed by Jordi of DIYDrones and is used under the Creative Commons 3.0 License
void Matrix_Multiply(float a[3][3], float b[3][3],float mat[3][3])
{
  float op[3];
  for(int x=0; x<3; x++)
  {
    for(int y=0; y<3; y++)
    {
      for(int w=0; w<3; w++)
      {
       op[w]=a[x][w]*b[w][y];
      }
      mat[x][y]=0;
      mat[x][y]=op[0]+op[1]+op[2];

      float test=mat[x][y];
    }
  }
}

int channel_filter(int ch, int ch_old)
{
  if (ch_old==0)
    return(ch);
  else
    return((ch+ch_old)>>1);     // small filtering (average filter)
}
// Decimal number parser
long parsedecimal(char *str,byte num_car) {
  long d = 0;
  byte i;

  i = num_car;
  while ((str[0] != 0)&&(i>0)) {
     if (str[0]=='-')
       d = -1*d;
     else if ((str[0] > '9') || (str[0] < '0'))
       return d;
     d *= 10;
     d += str[0] - '0';
     str++;
     i--;
     }
  return d;
}
