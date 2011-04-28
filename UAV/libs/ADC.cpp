/*
 * ADC.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: Ryan
 */

#include <interrupt.h>
#incldue "ADC.h"

// We are using an oversampling and averaging method to increase the ADC resolution
// The theorical ADC resolution is now 11.7 bits. Now we store the ADC readings in float format
void Read_adc_raw(void)
{
  int i;
  int temp1;
  int temp2;

  // ADC readings...
  for (i=0;i<6;i++)
    {
    temp1= analog_buffer[sensors[i]];   // sensors[] maps sensors to correct order
    temp2= analog_count[sensors[i]];
    if (temp1 != analog_buffer[sensors[i]])  // Check if there was an ADC interrupt during readings...
      {
      temp1= analog_buffer[sensors[i]];      // Take a new reading
      temp2= analog_count[sensors[i]];
      }
    AN[i] = float(temp1)/float(temp2);
    }

  // Initialization for the next readings...
  for (int i=0;i<8;i++){
    analog_buffer[i]=0;
    analog_count[i]=0;
    if (analog_buffer[i]!=0) // Check if there was an ADC interrupt during initialization...
      {
      analog_buffer[i]=0;    // We do it again...
      analog_count[i]=0;
      }
  }
}

float read_adc(int select)
{
  if (SENSOR_SIGN[select]<0)
    return (AN_OFFSET[select]-AN[select]);
  else
    return (AN[select]-AN_OFFSET[select]);
}

//Activating the ADC interrupts.
void Analog_Init(void)
{
 ADCSRA|=(1<<ADIE)|(1<<ADEN);
 ADCSRA|= (1<<ADSC);
}

//
void Analog_Reference(uint8_t mode)
{
  analog_reference = mode;
}

//ADC interrupt vector, this piece of code
//is executed everytime a convertion is done.
ISR(ADC_vect)
{
  volatile uint8_t low, high;
  low = ADCL;
  high = ADCH;
  analog_buffer[MuxSel] += (high << 8) | low;   // cumulate analog values
  analog_count[MuxSel]++;
  MuxSel++;
  MuxSel &= 0x07;   //if(MuxSel >=8) MuxSel=0;
  ADMUX = (analog_reference << 6) | MuxSel;
  // start the conversion
  ADCSRA|= (1<<ADSC);
}

ISR (TIMER2_OVF_vect)
{
  int us;
  int aux;

  if (Servo_Channel < num_servos){
    Servo_Timer2_timer1_stop = TCNT1;       // take the timer1 value at this moment

    // Now we are going to calculate the time we need to wait until pulse end
    if (Servo_Timer2_timer1_stop>Servo_Timer2_timer1_start)   // Timer1 reset during the pulse?
      Servo_Timer2_pulse_length = Servo_Timer2_timer1_stop-Servo_Timer2_timer1_start;
    else
      Servo_Timer2_pulse_length = ((long)Servo_Timer2_timer1_stop + Timer1_last_value) - (long)Servo_Timer2_timer1_start;
    us = (Servos[Servo_Channel].value) - (Servo_Timer2_pulse_length>>1);
    us -= 2;  // Adjust for the time of this code
    if (us>1)
      {
      us <<= 2; // Translate us to the 4 cyles loop (1/4 us)
      __asm__ __volatile__ (  // 4 cycles loop = 1/4 us  (taken from delayMicroSeconds function)
	"1: sbiw %0,1" "\n\t"            // 2 cycles
	"brne 1b" : "=w" (us) : "0" (us) // 2 cycles
	);
      }
    digitalWrite( Servos[Servo_Channel].pin,LOW);    // pulse this channel low
    Servo_Channel++;                                 // increment to the next channel
    }
  else
    Servo_Channel = 0;                // SYNC pulse end => Start again on first channel

  if (Servo_Channel == num_servos){           // This is the SYNC PULSE
    TCCR2B = _BV(CS20)|_BV(CS21)|_BV(CS22);   // set prescaler of 1024 => 64us resolution (overflow = 16384uS)
    TCNT2 = 0x04;   //64usx4 = 256us
    }
  else{
    TCCR2B = _BV(CS20)|_BV(CS22);                  // Set prescaler of 128  (8uS resolution at 16Mhz)
    TCNT2 = Servos[Servo_Channel].counter;         // Set the clock counter register for the overflow interrupt
    Servo_Timer2_timer1_start = TCNT1;             // we take the value of Timer1 at the start of the pulse
    digitalWrite(Servos[Servo_Channel].pin,HIGH);  // Pulse start. Let´s go...
    }
}

ISR(TIMER1_OVF_vect){

  //TCNT1 = 20000;        // at 16Mhz (0.5us) (65535-20000) = 22 ms (45Hz)
  //OCR1A = 20000 + (Servo1<<1);  // Output for servos...
  //OCR1B = 20000 + (Servo2<<1);

  //TCCR1A = 0xF0;        // Set OC1A/OC1B on Compare Match
  //TCCR1C = 0xC0;        // Force Output Compare A/B (Start Servo pulse)
  //TCCR1C = 0x00;
  //TCCR1A = 0xA0;  	// Clear OC1A/OC1B on Compare Match

  TCNT1 = 0;
  Timer1_last_value=0xFFFF;  // Last value before overflow...

  // Radio signal lost...
  radio_status = 0;
}

ISR(TIMER1_CAPT_vect)
{
   if(!bit_is_set(TCCR1B ,ICES1)){	    // falling edge?
	 if(Rx_ch == MAX_CHANNELS) {        // This should be the last pulse...
	     Pulses[Rx_ch++] = ICR1;
             radio_status = 1;              // Rx channels ready...
	  }
         TCCR1B = 0x42;              // Next time : rising edge
         Timer1_last_value = TCNT1;  // Take last value before reset
         TCNT1 = 0;                  // Clear counter

         // Servo Output on OC1A/OC1B... (syncronised with radio pulse train)
         //TCCR1A = 0xF0;        // Set OC1A/OC1B on Compare Match
         //TCCR1C = 0xC0;        // Force Output Compare A/B (Start Servo pulse)
         //TCCR1C = 0x00;
         //TCCR1A = 0xA0;  	// Clear OC1A/OC1B on Compare Match
   }
   else {				  // Rise edge
	  if ((ICR1-ICR1_old) >= SYNC_GAP_LEN){   // SYNC pulse?
		Rx_ch = 1;	          // Channel = 1
                Pulses[0] = ICR1;
	    }
          else {
            if(Rx_ch <= MAX_CHANNELS)
	       Pulses[Rx_ch++] = ICR1;    // Store pulse length
            if(Rx_ch == MAX_CHANNELS)
               TCCR1B = 0x02;             // Next time : falling edge
            }
   }
   ICR1_old = ICR1;
}
