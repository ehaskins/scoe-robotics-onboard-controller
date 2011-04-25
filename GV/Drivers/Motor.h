/*
 * Motor.h
 *
 *  Created on: Apr 13, 2011
 *      Author: Nick
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <Servo.h>
#include "IMotor.h"
#include <WProgram.h>
#include "..\UserConstants.h"

// Declare the motor pulse width calculation function.
long calcDriveMotorPulseWidth(int speed, long minWidth, long maxWidth);

/**
#include <wiring_private.h>
#include <pins_arduino.h>

// TODO - Determine the proper hardware PWM configuration!
// Phase and Frequency Correct Mode
// TOP = ICRn
// 

#define CASE_SETUP_TIMER_N_A(n)\
  case TIMER##n##A : \
    ICR##n = 20000; \
    TCCR##n##A = 0; \
    TCCR##n##B = (1<<CS##n##1)|(1<<WGM##n##3); \
    break;

#define CASE_SETUP_TIMER_N_B(n)\
  case TIMER##n##B : \
    ICR##n = 20000; \
    TCCR##n##A = 0; \
    TCCR##n##B = (1<<CS##n##1)|(1<<WGM##n##3); \
    break;
    
#define CASE_SETUP_TIMER_N_C(n)\
  case TIMER##n##C : \
    ICR##n = 20000; \
    TCCR##n##A = 0; \
    TCCR##n##B = (1<<CS##n##1)|(1<<WGM##n##3); \
    break;
    
static void setupServoPWM(int pin) {
  pinMode(pin, OUTPUT);
  switch (digitalPinToTimer(pin)) {
#if defined(TCCR1A) && defined(COM1A1)
    CASE_SETUP_TIMER_N_A(1)
#endif
#if defined(TCCR1A) && defined(COM1B1)
    CASE_SETUP_TIMER_N_B(1)
#endif
#if defined(TCCR3A) && defined(COM3A1)
    CASE_SETUP_TIMER_N_A(3)
#endif
#if defined(TCCR3A) && defined(COM3B1)
    CASE_SETUP_TIMER_N_B(3)
#endif
#if defined(TCCR3A) && defined(COM3C1)
    CASE_SETUP_TIMER_N_C(3)
#endif
#if defined(TCCR4A) && defined(COM4A1)
    CASE_SETUP_TIMER_N_A(4)
#endif
#if defined(TCCR4A) && defined(COM4B1)
    CASE_SETUP_TIMER_N_B(4)
#endif
#if defined(TCCR4A) && defined(COM4C1)
    CASE_SETUP_TIMER_N_C(4)
#endif
#if defined(TCCR5A) && defined(COM5A1)
    CASE_SETUP_TIMER_N_A(5)
#endif
#if defined(TCCR5A) && defined(COM5B1)
    CASE_SETUP_TIMER_N_B(5)
#endif
#if defined(TCCR5A) && defined(COM5C1)
    CASE_SETUP_TIMER_N_C(5)
#endif
    case NOT_ON_TIMER:
    default:
      pinMode(pin, OUTPUT);
   };
}

#define CASE_WRITE_TIMER_N_A(n)\
  case TIMER##n##A : \
    sbi(TCCR##n##A, COM##n##A1); \
    OCR##n##A = ocrVal; \
    break;
    
#define CASE_WRITE_TIMER_N_B(n)\
  case TIMER##n##B : \
    sbi(TCCR##n##B, COM##n##B1); \
    OCR##n##B = ocrVal; \
    break;
    
#define CASE_WRITE_TIMER_N_C(n)\
  case TIMER##n##C : \
    sbi(TCCR##n##C, COM##n##C1); \
    OCR##n##C = ocrVal; \
    break;


static void writeServoPWM(int pin, int ocrVal) {
  switch (digitalPinToTimer(pin)) {
#if defined(TCCR0A) && defined(COM0A1)
    CASE_WRITE_TIMER_N_A(0)
#endif
#if defined(TCCR0A) && defined(COM0B1)
    CASE_WRITE_TIMER_N_B(0)
#endif
#if defined(TCCR1A) && defined(COM1A1)
    CASE_WRITE_TIMER_N_A(1)
#endif
#if defined(TCCR1A) && defined(COM1B1)
    CASE_WRITE_TIMER_N_B(1)
#endif
#if defined(TCCR2A) && defined(COM2A1)
    CASE_WRITE_TIMER_N_A(2)
#endif
#if defined(TCCR2A) && defined(COM2B1)
    CASE_WRITE_TIMER_N_B(2)
#endif
#if defined(TCCR3A) && defined(COM3A1)
    CASE_WRITE_TIMER_N_A(3)
#endif
#if defined(TCCR3A) && defined(COM3B1)
    CASE_WRITE_TIMER_N_B(3)
#endif
#if defined(TCCR3A) && defined(COM3C1)
    CASE_WRITE_TIMER_N_C(3)
#endif
#if defined(TCCR4A) && defined(COM4A1)
    CASE_WRITE_TIMER_N_A(4)
#endif
#if defined(TCCR4A) && defined(COM4B1)
    CASE_WRITE_TIMER_N_B(4)
#endif
#if defined(TCCR4A) && defined(COM4C1)
    CASE_WRITE_TIMER_N_C(4)
#endif
#if defined(TCCR5A) && defined(COM5A1)
    CASE_WRITE_TIMER_N_A(5)
#endif
#if defined(TCCR5A) && defined(COM5B1)
    CASE_WRITE_TIMER_N_B(5)
#endif
#if defined(TCCR5A) && defined(COM5C1)
    CASE_WRITE_TIMER_N_C(5)
#endif
    case NOT_ON_TIMER:
    default:
      if (ocrVal < 128) {
        digitalWrite(pin, LOW);
      } else {
        digitalWrite(pin, HIGH);
      }
   };
}
*/

class Motor : public IMotor {
private:
  int m_pwmPort;
  Servo m_servo;
  bool m_enabled;

  int m_idle;
  int m_minBound;
  int m_maxBound;

  bool m_inverted;

public:
  Motor() : m_pwmPort(NO_PORT), m_enabled(false), m_idle(0), m_minBound(-128), m_maxBound(127), m_inverted(false) {
	  if (m_servo.attached()) {
		  m_servo.detach();
	  }
  }

  void setIdle(int idle) {
    m_idle = idle;
  }

  int getIdle() const {
    return m_idle;
  }

  void setInverted(bool invert) {
    m_inverted = invert;
  }

  void init(int port) {
    m_pwmPort = port;
    pinMode(m_pwmPort, OUTPUT);
  }

  void setEnabled(bool enable) {
    m_enabled = enable;
    if (!enable && m_servo.attached()) {
    	m_servo.detach();
    } else if (enable && !m_servo.attached()){
    	m_servo.attach(m_pwmPort, 1000, 2000);
    }
  }

  bool isEnabled() const {
    return m_enabled;
  }

  bool setBounds(int min, int max) {
    if (max < min) {
      return false;
    }
    m_minBound = min;
    m_maxBound = max;
    return true;
  }

  int getMinBound() const {
    return m_minBound;
  }

  int getMaxBound() const {
    return m_maxBound;
  }

  void setSpeed(int speed) {

    // Only set us to our idle speed if disabled.
    if (!m_enabled) {
      speed = m_idle;
    }

    // Constrain to the given bounds.
    speed = constrain(speed, m_minBound, m_maxBound);

    // Convert from speed bounds to microseconds value.
#if USING_TRUE_SPEED
    long output = calcDriveMotorPulseWidth(speed, 1000, 2000);
#else
    long output = map(speed, m_minBound, m_maxBound, 1000, 2000);
#endif

    // Invert if necessary.
    if (m_inverted) {
      output = 3000 - output;
    }

#ifdef DEBUG
    Serial.print("Motor on pin ");
    Serial.print(m_pwmPort);
    Serial.print(" at pulse width ");
    Serial.print(output);
    Serial.println(".");
#endif

    // Output the PWM signal.
    m_servo.write(output);
  }
};

#endif /* MOTOR_H_ */

