/*
 * UserCode.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */
#include <WProgram.h>

#ifndef USERCONSTANTS_H_
#define USERCONSTANTS_H_

const int FIXED_LOOP_FREQUENCY = 1;

// The PWM pins for the motor controllers.
#define PIN_LEFT_MOTOR			5	// PWM Pin 5 (TC3)
#define PIN_RIGHT_MOTOR			6	// PWM Pin 6 (TC4)
#define PIN_REAR_MOTOR			7	// PWM Pin 7 (TC4)

#define PIN_LAUNCH_MOTOR		8	// PWM Pin 8
#define PIN_INTAKE_MOTOR		9	// PWM Pin 9

#define PIN_LEFT_ENCODER_DIR	22	// Digital Pin 22
#define PIN_RIGHT_ENCODER_DIR	24	// Digital Pin 24
#define PIN_REAR_ENCODER_DIR	26	// Digital Pin 26

#define PIN_LEFT_ENCODER_INT	1	// PWM Pin 3
#define PIN_RIGHT_ENCODER_INT	2	// Comm Pin 18 (TX1)
#define PIN_REAR_ENCODER_INT	3	// Comm Pin 19 (RX1)

#define PIN_LOAD_SWITCH			23	// Digital Pin 23
#define PIN_INTAKE_SWITCH		25	// Digital Pin 24

// Whether or not any of the drive directions are inverted.
#define USER_INVERT_FORWARD		false
#define USER_INVERT_STRAFE		false
#define USER_INVERT_YAW			false

// Whether or not any of the motor lines are inverted.
#define USER_INVERT_LEFT_MOTOR		false
#define USER_INVERT_RIGHT_MOTOR		false
#define USER_INVERT_REAR_MOTOR		false
#define USER_INVERT_LAUNCH_MOTOR	false
#define USER_INVERT_INTAKE_MOTOR	false

// The maximum shift in motor speed between timesteps.
#define USER_MAX_SHIFT			15

// The maximum motor speed. TODO Change this!
#define USER_MOTOR_MAX_SPEED	150
#define USER_MOTOR_IDLE_SPEED	0

// The launcher motor max speed.
#define USER_LAUNCHER_MAX_SPEED		100
#define USER_LAUNCHER_IDLE_SPEED	0

// TODO Test this!
#define USER_LAUNCHER_FIRE_SPEED	50

// The intake motor speeds.
#define USER_INTAKE_MAX_SPEED		100
#define USER_INTAKE_IDLE_SPEED		0

// TODO Test this!
#define USER_INTAKE_RUN_SPEED		25

// The pulses per revolution of the encoders.
#define USER_LEFT_ENCODER_PPR		2048
#define USER_RIGHT_ENCODER_PPR		2048
#define USER_REAR_ENCODER_PPR		2048

// The diameter of the wheel.
#define USER_WHEEL_DIAMETER		6

// Are we using PID controllers?
#define USING_PID_CONTROLLERS	true

#endif
