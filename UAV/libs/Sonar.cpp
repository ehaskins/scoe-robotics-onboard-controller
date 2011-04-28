/*
 * Sonar.cpp
 *
 *  Created on: Apr 26, 2011
 *      Author: Ryan
 */

/* ********************************************************* */
/* Code to read Sonar LV-EZ4                                 */
/* 															 */
/* ********************************************************* */


int Get_Sonar_Pulse()
{
  int temp;
  temp = analogread(sonar_pin);

  return (temp);
}

// This filter limits the max difference between readings and also aply an average filter
int Filter(int new_value, int old_value, int max_diff)
{
  int diff_values;
  int result;

  if (old_value==0)     // Filter is not initialized (no old value)
    return(new_value);
  diff_values = new_value - old_value;      // Difference with old reading
  if (diff_values>max_diff)
    result = old_value+max_diff;    // We limit the max difference between readings
  else
    {
    if (diff_values<-max_diff)
      result = old_value-max_diff;        // We limit the max difference between readings
    else
      result = (new_value+old_value)>>1;  // Small filtering (average filter)
    }
  return(result);
}
