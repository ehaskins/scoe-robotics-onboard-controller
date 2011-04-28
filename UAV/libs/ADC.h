/*
 * ADC.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Ryan
 */

#ifndef ADC_H_
#define ADC_H_

void Read_adc_raw(void);
float read_adc(int select);
void Analog_Init(void);
void Analog_Reference(uint8_t mode);
ISR(ADC_vect);
ISR(TIMER1_CAPT_vect);
ISR(TIMER1_OVF_vect);
ISR (TIMER2_OVF_vect);


#endif /* ADC_H_ */
