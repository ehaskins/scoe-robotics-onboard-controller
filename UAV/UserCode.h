/*
 * UserCode.h
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#ifndef USERCODE_H_
#define USERCODE_H_
#include <Servo.h>
#include <FrcComms\Configuration.h>
#include <FrcComms\FRCCommunication.h>
//Declared and initialized in main.

//UAV Defines

//----------------------------------------
//*********Config Parameters**************
//----------------------------------------

// QuadCopter Attitude control PID GAINS
#define KP_QUAD_ROLL 2.0  //1.4
#define KD_QUAD_ROLL 0.4  //0.33
#define KI_QUAD_ROLL 0.6   //0.32
#define KP_QUAD_PITCH 2.0 //1.75 //1.8 // 2.2   //1.75
#define KD_QUAD_PITCH 0.4 //0.4 //0.42 // 0.54  //0.45
#define KI_QUAD_PITCH 0.6 //0.42 // 0.45  //0.5
#define KP_QUAD_YAW 3.6 //3.4// 4.6  //3.2 //2.6
#define KD_QUAD_YAW 0.85 //0.8// 0.7  //0.8 //0.4
#define KI_QUAD_YAW 0.15 // 0.2  //0.15

#define KD_QUAD_COMMAND_PART 0.0  //13 // for special KD implementation (in two parts). Higher values makes the quadcopter more responsive to user inputs

// Range Finder (RF) Position control PID GAINS
#define KP_RF_ROLL 0.09
#define KD_RF_ROLL 0.06
#define KI_RF_ROLL 0.025
#define KP_RF_PITCH 0.09
#define KD_RF_PITCH 0.06
#define KI_RF_PITCH 0.025

#define RF_MAX_ANGLE 5  // Maximun command roll and pitch angle from position control

// Altitude control PID GAINS
#define KP_ALTITUDE 0.9
#define KD_ALTITUDE 0.5
#define KI_ALTITUDE 0.25

// The IMU should be correctly adjusted : Gyro Gains and also initial IMU offsets:
// We have to take this values with the IMU flat
#define acc_offset_x 508
#define acc_offset_y 504
#define acc_offset_z 501         // We need to rotate the IMU exactly 90 to take this value
#define gyro_offset_roll 370
#define gyro_offset_pitch 373
#define gyro_offset_yaw 380

//sonar and rf pin defines
#define sonar_pin 2
#define RF1_pin 3
#define RF2_pin 4
#define RF3_pin 5
#define RF4_pin 6

//---------------------------------------
//*********End Config Parameters*********
//---------------------------------------

//---------------------------------------
//*********IMU Pin Mapping***************
//---------------------------------------
// uint8_t sensors[6] = {1,0,2,4,5,3};  // For Razor 6DOF // Sensor: GYROX, GYROY, GYROZ, ACCELX, ACCELY, ACCELZ - arduino uno
 uint8_t sensors[6] = {9,8,10,12,13,11};  // For Razor 6DOF // Sensor: GYROX, GYROY, GYROZ, ACCELX, ACCELY, ACCELZ - arudino mega
 int SENSOR_SIGN[] = {1,1,-1,-1,1,1,-1,-1,-1};  // array to invert the raw adc value of the sensors // GYROX, GYROY, GYROZ, ACCELX, ACCELY, ACCELZ, X, Y, Z

// ADC : Voltage reference 3.3v / 10bits(1024 steps) => 3.22mV/ADC step
// ADXL335 Sensitivity(from datasheet) => 330mV/g, 3.22mV/ADC step => 330/3.22 = 102.48
// Tested value : 101
#define GRAVITY 101 //this equivalent to 1G in the raw data coming from the accelerometer
#define Accel_Scale(x) x*(GRAVITY/9.81)//Scaling the raw data of the accel to actual acceleration in meters for seconds square

#define ToRad(x) (x*0.01745329252)  // *pi/180
#define ToDeg(x) (x*57.2957795131)  // *180/pi

// LPR530 & LY530 Sensitivity (from datasheet) => 3.33mV/º/s, 3.22mV/ADC step => 1.03
// Tested values : 0.96,0.96,0.94
#define Gyro_Gain_X 0.92 //X axis Gyro gain
#define Gyro_Gain_Y 0.92 //Y axis Gyro gain
#define Gyro_Gain_Z 0.94 //Z axis Gyro gain
#define Gyro_Scaled_X(x) x*ToRad(Gyro_Gain_X) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Y(x) x*ToRad(Gyro_Gain_Y) //Return the scaled ADC raw data of the gyro in radians for second
#define Gyro_Scaled_Z(x) x*ToRad(Gyro_Gain_Z) //Return the scaled ADC raw data of the gyro in radians for second

#define Kp_ROLLPITCH 0.008  //0.0125 //0.010 // Pitch&Roll Proportional Gain
#define Ki_ROLLPITCH 0.000010 // Pitch&Roll Integrator Gain
#define Kp_YAW 1.0 // Yaw Porportional Gain
#define Ki_YAW 0.00005 // Yaw Integrator Gain

//Min Speed Filter for Yaw drift Correction
#define SPEEDFILT 3 // >1 use min speed filter for yaw drift cancellation, 0=do not use

//For debugging purposes
#define OUTPUTMODE 1  //If value = 1 will print the corrected data, 0 will print uncorrected data of the gyros (with drift), 2 Accel only data

 //PWM ESC output defines
#define SERVO_MAX_PULSE_WIDTH 2000
#define SERVO_MIN_PULSE_WIDTH 900
#define SERVO_TIMER2_NUMSERVOS 4         // Put the number of servos outs here. In this case 4 ESC´s

 //END UAV Defines

#define MIN_THROTTLE 900
#define MAX_THROTTLE 2250
#define HOVER_THROTTLE 1450
#define CHANN_CENTER 625

#define MIN_IN_PULSE_WIDTH 900
#define MAX_IN_PULSE_WIDTH 2250

 //Data From Groundstation
 int controls[6] = {0,0,0,0,0,0};



class UserRobot
{
public:
	int teleopCounter;

	int start;
	int position;
	int direction;
	int range;
	int autonomousCounter;

	bool autoInitComplete;
	bool teleInitComplete;
	bool disabledInitComplete;

	bool attached;

	Configuration *config;
	FRCCommunication *comm;

	//*******UAV Dedicated Stuff**********

	//IMU variables
	float AN[6]; //array that store the 6 ADC filtered data
	float AN_OFFSET[6]; //Array that stores the Offset of the gyros

	float G_Dt;    // Integration time for the gyros (DCM algorithm)

	float Accel_Vector[3]; //Store the acceleration in a vector
	float Accel_Vector_unfiltered[3]; //Store the acceleration in a vector
	float Accel_magnitude;
	float Accel_weight;
	float Gyro_Vector[3];//Store the gyros rutn rate in a vector
	float Omega_Vector[3]; //Corrected Gyro_Vector data
	float Omega_P[3];//Omega Proportional correction
	float Omega_I[3];//Omega Integrator
	float Omega[3];

	float errorRollPitch[3];
	float errorYaw[3];
	float errorCourse;
	float COGX; //Course overground X axis
	float COGY;

	float roll;
	float pitch;
	float yaw;

	unsigned int counter;
	long loop_counter;

	float DCM_Matrix[3][3];
	float Update_Matrix[3][3];

	float Temporary_Matrix[3][3];
	//end IMU Variables

	//Radio Variables
	byte radio_status; // radio_status = 1 => OK, 0 => No Radio signal
	byte RF_new_data;
	int ch1;    // Channel values
	int ch2;
	int ch3;
	int ch4;
	int ch_aux;
	int ch_aux2;


	//END Radio Variables

	int Neutro[6];

	// Servo Timer2 variables (Servo Timer2)
		//defines above
	typedef struct {
	  uint8_t pin;
	  int value;
	  uint8_t counter;
	}  servo_t;
	uint8_t num_servos;
	servo_t Servos[SERVO_TIMER2_NUMSERVOS];
	static volatile uint8_t Servo_Channel;
	static volatile uint8_t ISRCount;
	static volatile unsigned int Servo_Timer2_timer1_start;
	static volatile unsigned int Servo_Timer2_timer1_stop;
	static volatile unsigned int Servo_Timer2_pulse_length;
	// END Servo Timer2 variables

	// ADC variables
	volatile uint8_t MuxSel;
	volatile uint8_t analog_reference;
	volatile uint16_t analog_buffer[8];
	volatile uint8_t analog_count[8];
	int an_count;

	long timer; //general purpose timer
	long timer_old;

	// Sonar variables
	static volatile unsigned long sonar_start_ms;
	static volatile unsigned char sonar_start_t0;
	static volatile unsigned long sonar_pulse_start_ms;
	static volatile unsigned char sonar_pulse_start_t0;
	static volatile unsigned long sonar_pulse_end_ms;
	static volatile unsigned char sonar_pulse_end_t0;
	static volatile byte sonar_status;
	static volatile byte sonar_new_data;
	int sonar_value;

	// Attitude control variables
	float command_rx_roll;
	float command_rx_roll_old;
	float command_rx_roll_diff;
	float command_rx_pitch;
	float command_rx_pitch_old;
	float command_rx_pitch_diff;
	float command_rx_yaw;
	float command_rx_yaw_diff;
	int control_roll;
	int control_pitch;
	int control_yaw;
	float K_aux;

	// Attitude control
	float roll_I;
	float roll_D;
	float err_roll;
	float pitch_I;
	float pitch_D;
	float err_pitch;
	float yaw_I;
	float yaw_D;
	float err_yaw;

	//Position control
	long target_longitude;
	long target_lattitude;
	byte target_position;
	float RF_err_roll;
	float RF_err_roll_old;
	float RF_roll_D;
	float RF_roll_I;
	float RF_err_pitch;
	float RF_err_pitch_old;
	float RF_pitch_D;
	float RF_pitch_I;
	float command_RF_roll;
	float command_RF_pitch;

	//Altitude control
	int Initial_Throttle;
	int target_sonar_altitude;
	int err_altitude;
	int err_altitude_old;
	float command_altitude;
	float altitude_I;
	float altitude_D;

	// AutoPilot Mode - Used for debugging - competition set to 3
	// AP_mode : 1=> Position hold  2=>Stabilization assist mode (normal mode)  3=> Automatic flight
	byte AP_mode;

	long t0;
	int num_iter;
	float aux_debug;

	// Variables for automatic flight
	byte automatic_mode;
	long automatic_mode_time;
	int automatic_mode_initial_altitude;
	int automatic_mode_altitude;
	int automatic_ascend;
	int automatic_descend;

	//Variables for side firing sonar (RangeFinders)
	int RF_Sensor1;
	int RF_Sensor2;
	int RF_Sensor3;
	int RF_Sensor4;

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

	int RxGetChannelPulseWidth( uint8_t channel);
	void Servo_Timer2_ini();
	void Servo_Timer2_set(uint8_t servo_index, int value);
	void Automatic_flight(int target_sonar_altitude, long flight_time);
	void Altitude_control(int target_sonar_altitude);
	void Attitude_control();
	int channel_filter(int ch, int ch_old);
	void update_RF();
	void Position_control(int RF_Sensor1, int RF_Sensor2,int RF_Sensor3, int RF_Sensor4);
};

#endif /* USERCODE_H_ */
