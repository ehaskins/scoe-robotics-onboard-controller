/*
 * UserCode.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "UserCode.h"
#include <WProgram.h>
#include <FrcComms\FRCCommunication.h>
#include <Servo.h>
#include "Utils.h"
#include <math.h>
#include <inttypes.h>
#include <interrupt.h>
#include <io.h>
#include "libs/ADC.h"
#include "libs/DCM.h"
#include "libs/Sonar.h"

/*
 * Guaranteed to be called after the following have been initialized:
 * Ethernet, configuration, serial, and FRCComms.
 *
 * Place any one time robot specific initialization code here.
 */
void UserRobot::userInit(void) {
	//Initialize user code, robot sensors, etc. here.

	start = 0;
	position = 0;
	direction = 1;
	range = 40;

	autoInitComplete = false;
	teleInitComplete = false;
	disabledInitComplete = false;

	//UAV Init Procedure
	G_Dt = 0.02; // Integration time for the gyros (DCM algorithm)

	COGX = 0; //Course overground X axis
	COGY = 1;

	DCM_Matrix[0][0] = 1;
	DCM_Matrix[1][1] = 1;
	DCM_Matrix[2][2] = 1;

	Update_Matrix[0][0] = 0;
	Update_Matrix[0][1] = 1;
	Update_Matrix[0][2] = 2;
	Update_Matrix[1][0] = 3;
	Update_Matrix[1][1] = 4;
	Update_Matrix[1][2] = 5;
	Update_Matrix[2][0] = 6;
	Update_Matrix[2][1] = 7;
	Update_Matrix[2][2] = 8;

	yaw_I = 0;
	pitch_I = 0;
	roll_I = 0;

	RF_pitch_I = 0;
	RF_roll_I = 0;

	// AutoPilot Mode - Used for debugging - competition set to 3
	// AP_mode : 1=> Position hold  2=>Stabilization assist mode (normal mode)  3=> Automatic flight
	AP_mode = 2;
	//end IMU Variables

	uint8_t num_servos = SERVO_TIMER2_NUMSERVOS;
	// END Servo Timer2 variables

	// ADC variables
	MuxSel;
	analog_reference = DEFAULT;

	int i;
	int j;
	int aux;

	//pinMode(4,INPUT);    // Sonar input
	pinMode(5, OUTPUT); // Red LED
	pinMode(6, OUTPUT); // BLue LED
	pinMode(7, OUTPUT); // Yellow LED
	pinMode(8, OUTPUT); // Servo1  Claw
	pinMode(9, OUTPUT); // Servo2  Right Motor
	pinMode(3, OUTPUT); // Servo3  Left Motor
	pinMode(11, OUTPUT); // Servo4  Front Motor
	pinMode(12, OUTPUT); // Servo5  Back Motor

	//Sonar_Init();

	ch1 = MIN_THROTTLE;
	ch2 = MIN_THROTTLE;
	ch3 = MIN_THROTTLE;
	ch4 = MIN_THROTTLE;

	// Assign pins to servos
	num_servos = 4;
	Servos[0].pin = 9; // Right motor
	Servos[1].pin = 10; // Left motor
	Servos[2].pin = 11; // Front motor
	Servos[3].pin = 12; // Back motor
	Servo_Timer2_set(0, MIN_THROTTLE); // First assign values to servos
	Servo_Timer2_set(1, MIN_THROTTLE);
	Servo_Timer2_set(2, MIN_THROTTLE);
	Servo_Timer2_set(3, MIN_THROTTLE);
	Servo_Timer2_ini(); // Servo Interrupt initialization

	delay(100);
	command_rx_yaw = 0;

	Serial.println();
	Serial.println("SCOE QuadCopter");
	delay(3000);

	// Take neutral radio values...
	for (j = 1; j <= 6; j++)
		Neutro[j] = 1450;

	/*for (i = 0; i < 80; i++) {
		for (j = 1; j <= 6; j++)
			Neutro[j] = (Neutro[j] * 0.8 + RxGetChannelPulseWidth(j) * 0.2);
		delay(25);
	}

	Serial.print("Rx values: ");
	for (i = 1; i <= 6; i++) {
		Serial.print(",");
		Serial.println(Neutro[i]);
	}*/

	// Roll, Pitch and Throttle have fixed neutral values

	Neutro[1] = CHANN_CENTER;
	Neutro[2] = CHANN_CENTER;
	Neutro[3] = MIN_THROTTLE;

	Analog_Reference( EXTERNAL);
	Analog_Init();

	Read_adc_raw();
	delay(20); //changing the adc to external refernce requires some chill time - look it up in the aruino reference

	// Offset values for accels and gyros...
	AN_OFFSET[3] = acc_offset_x;
	AN_OFFSET[4] = acc_offset_y;
	AN_OFFSET[5] = acc_offset_z;
	AN_OFFSET[0] = gyro_offset_roll;
	AN_OFFSET[1] = gyro_offset_pitch;
	AN_OFFSET[2] = gyro_offset_yaw;

	// Take the gyro offset values
	for (i = 0; i < 300; i++) {
		Read_adc_raw();
		for (int y = 0; y <= 2; y++) // Read initial ADC values for offset.
			AN_OFFSET[y] = AN_OFFSET[y] * 0.8 + AN[y] * 0.2;
		delay(20);
	}

	Serial.print("AN:");
	for (i = 0; i < 6; i++) {
		Serial.print(",");
		Serial.println(AN_OFFSET[i]);
	}

	delay(500);

	// Wait until throttle stick is at bottom

	while (RxGetChannelPulseWidth(3) > (MIN_THROTTLE + 50)) {
		Serial.println("Move throttle stick to bottom to start !!!");
	}

	Read_adc_raw(); // Start ADC readings...
	timer = millis();
	delay(20);

	digitalWrite(7, HIGH);

	Serial.println("User init complete.");
}

/*
 * Disabled and enables all outputs. Must be implemented or a disabled robot may behave irratically.
 */
void UserRobot::setOutputsEnabled(bool enabled) {
	if (enabled && !attached) {
		attached = true;
	} else if (!enabled && attached) {
		attached = false;
	}
}

/*
 * Perform any initialization needed before teleop mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::teleopInit() {

}
/*
 * Process teleop control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::teleopLoop() {
	Joystick stick = comm->controlData->joysticks[0];

	int aileron;
	int elevator;
	int throttle;
	int rudder;

	//Deadband to remove the non-centered stick issues. 360 controller requires a big deadband.


	controls[0] = deadband((((stick.axis[0] + 128) * 5.859375) + 750), 25); //Aileron
	controls[1] = deadband((((stick.axis[1] + 128) * 5.859375) + 750), 25); //Elevator
	controls[2] = (((stick.axis[2] + 128) * 5.859375) + 750); //Throttle
	controls[3] = deadband((((stick.axis[3] + 128) * 5.859375) + 750), 25); //Rudder
	//controls[4] = (((stick.buttons[1] + 128) * 5.859375) + 750);				  //ch_aux2
	controls[4] = 1000; //ch_aux2
	controls[5] = (((stick.axis[1] + 128) * 5.859375) + 750); //ch_aux
	radio_status = 1;

	/*ch1 = channel_filter(RxGetChannelPulseWidth(1),ch1);   // Aileron
	 ch2 = channel_filter(RxGetChannelPulseWidth(2),ch2);   // Elevator
	 ch3 = channel_filter(RxGetChannelPulseWidth(3),ch3);   // Throttle
	 ch4 = channel_filter(RxGetChannelPulseWidth(4),ch4);   // Ruder
	 ch_aux = channel_filter(RxGetChannelPulseWidth(6),ch_aux);
	 ch_aux2 = channel_filter(RxGetChannelPulseWidth(5),ch_aux2);
	 */
	teleopCounter++;
}

/*
 * Perform any initialization needed before disabled mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::disabledInit() {

}
/*
 * Process disabled control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::disabledLoop() {

	// abandon all hope ye who enter here
	ch3--; // Descend  (Reduce throttle)
	if (ch3 < MIN_THROTTLE)
		ch3 = MIN_THROTTLE;
	command_rx_roll = 0; // Stabilize to roll=0, pitch=0, yaw not important here
	command_rx_pitch = 0;
	Attitude_control();

	// Quadcopter mix
	Servo_Timer2_set(0, ch3 - control_roll - control_yaw); // Right motor
	Servo_Timer2_set(1, ch3 + control_roll - control_yaw); // Left motor
	Servo_Timer2_set(2, ch3 + control_pitch + control_yaw); // Front motor
	Servo_Timer2_set(3, ch3 - control_pitch + control_yaw); // Back motor
}

/*
 * Perform any initialization needed before autonomous mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::autonomousInit() {

}

/*
 * Process autonomous control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::autonomousLoop() {
	int aux;
	float aux_float;

	if ((millis() - timer) >= 14) // 14ms => 70 Hz loop rate
	{
		counter++;
		loop_counter++;
		timer_old = timer;
		timer = millis();
		G_Dt = (timer - timer_old) / 1000.0; // Real time of loop run
		num_iter++;

		// IMU DCM Algorithm
		Read_adc_raw();
		Matrix_update();
		Normalize();
		Drift_correction();
		Euler_angles();
		// *****************

		// Telemetry data...

		//Serial.print(K_aux);
		//Serial.print(",");
		Serial.print("$"); // Line Begin char
		if ((AP_mode == 1) || (AP_mode == 3))
			Serial.print("P"); // Position Hold mode

		aux = ToDeg(roll);
		Serial.print(aux);
		Serial.print(",");
		aux = ToDeg(pitch);
		Serial.print(aux);
		Serial.print(",");
		aux = ToDeg(yaw);
		Serial.print(aux);

		//Serial.print(",");
		//Serial.print(K_aux*100);

		//Serial.print((int)command_rx_roll);
		//Serial.print(",");
		//Serial.print((int)command_rx_pitch);

		if (sonar_new_data) {
			sonar_new_data = 0;
			sonar_value = Filter(Get_Sonar_Pulse(), sonar_value, 5); // Filtering
			Serial.print(",");
			Serial.print(sonar_value);
		}

		ch1 = channel_filter(RxGetChannelPulseWidth(1), ch1); // Aileron
		ch2 = channel_filter(RxGetChannelPulseWidth(2), ch2); // Elevator
		ch3 = channel_filter(RxGetChannelPulseWidth(3), ch3); // Throttle
		ch4 = channel_filter(RxGetChannelPulseWidth(4), ch4); // Ruder
		ch_aux = channel_filter(RxGetChannelPulseWidth(6), ch_aux);
		ch_aux2 = channel_filter(RxGetChannelPulseWidth(5), ch_aux2);

		// Commands from radio Rx...
		// Stick position defines the desired angle in roll, pitch and yaw
		command_rx_roll_old = command_rx_roll;
		command_rx_roll = (ch1 - CHANN_CENTER) / 13.0;
		command_rx_roll_diff = command_rx_roll - command_rx_roll_old;
		command_rx_pitch_old = command_rx_pitch;
		command_rx_pitch = (ch2 - CHANN_CENTER) / 13.0;
		command_rx_pitch_diff = command_rx_pitch - command_rx_pitch_old;
		aux_float = (ch4 - Neutro[4]) / 200.0;
		command_rx_yaw += aux_float;
		command_rx_yaw_diff = aux_float;
		if (command_rx_yaw > 180) // Normalize yaw to -180,180 degrees
			command_rx_yaw -= 360.0;
		else if (command_rx_yaw < -180)
			command_rx_yaw += 360.0;

		//K_aux = K_aux*0.8 + ((ch_aux-1500)/100.0 + 0.6)*0.2;
		K_aux = K_aux * 0.8 + ((ch_aux - 1500) / 1000.0 + 0.02) * 0.2;
		if (K_aux < 0)
			K_aux = 0;

		// We read the Mode from Channel aux2 (5)
		if (ch_aux2 < 1200) {
			if (AP_mode == 2) {
				if (ch3 < (MIN_THROTTLE + 30)) // If throttle is down => automatic flight
				{
					AP_mode = 3; // Automatic pattern fligth
					digitalWrite(5, HIGH); // Red LED On
					digitalWrite(7, LOW); // Yellow led Off
					//Serial.print("A");
				} else {
					AP_mode = 1; // Position hold mode (RF Position control)
					digitalWrite(5, HIGH); // Red LED On
					digitalWrite(7, HIGH);
					//Serial.print("P");
				}
			}
		} else {
			AP_mode = 2; // Normal mode (Stabilization assist mode)
			digitalWrite(5, LOW); // Red LED off
			digitalWrite(7, HIGH);
		}
	} else if (radio_status == 0) { // Radio_status = 0 Lost radio signal => Descend...
		ch3--; // Descend  (Reduce throttle)
		if (ch3 < MIN_THROTTLE)
			ch3 = MIN_THROTTLE;
		command_rx_roll = 0; // Stabilize to roll=0, pitch=0, yaw not important here
		command_rx_pitch = 0;
		Attitude_control();

		// Quadcopter mix
		Servo_Timer2_set(0, ch3 - control_roll - control_yaw); // Right motor
		Servo_Timer2_set(1, ch3 + control_roll - control_yaw); // Left motor
		Servo_Timer2_set(2, ch3 + control_pitch + control_yaw); // Front motor
		Servo_Timer2_set(3, ch3 - control_pitch + control_yaw); // Back motor
		//Serial.println("NO RADIO!");
	}

	if ((AP_mode == 1) || (AP_mode == 3)) // Position Control
	{

		if (target_position == 0) // If this is the first time we switch to Position control, actual position is our target position
		{
			target_position = 1;

			if (sonar_value < 350) // Maximun 3.5 meters for altitude control
				target_sonar_altitude = sonar_value;
			else
				target_sonar_altitude = 350;
			Initial_Throttle = ch3;
			// Reset I terms
			altitude_I = 0;
			RF_roll_I = 0;
			RF_pitch_I = 0;
			if (AP_mode == 3) // Automatic mode
			{
				command_altitude = MIN_THROTTLE;
				target_sonar_altitude = 150;
				automatic_mode = 0;
			}
		}
		if (RF_new_data) {
			RF_new_data = 0;
			if (target_position) {
				Position_control(RF_Sensor1, RF_Sensor2, RF_Sensor3, RF_Sensor4); // Call Range Finder position control routine
				//Serial.print(";CRF");
				//Serial.print((int)command_RF_roll);
				//Serial.print(",");
				//Serial.print((int)command_RF_pitch);
			} else {
				command_RF_roll = 0;
				command_RF_pitch = 0;
			}
		}

		if (AP_mode == 1) {
			Altitude_control(target_sonar_altitude);
			ch3 = command_altitude;
		} else if (AP_mode == 3) {
			Automatic_flight(target_sonar_altitude, 1000);
			ch3 = command_altitude;
		}
	} else
		target_position = 0;

	// Attitude control (Roll, Pitch, yaw)
	Attitude_control();

	// Quadcopter mix
	if (ch3 > (MIN_THROTTLE + 30)) // Minimun throttle to start control
	{
		Servo_Timer2_set(0, ch3 - control_roll - control_yaw); // Right motor
		Servo_Timer2_set(1, ch3 + control_roll - control_yaw); // Left motor
		Servo_Timer2_set(2, ch3 + control_pitch + control_yaw); // Front motor
		Servo_Timer2_set(3, ch3 - control_pitch + control_yaw); // Back motor
	} else {
		roll_I = 0; // reset I terms...
		pitch_I = 0;
		yaw_I = 0;
		Servo_Timer2_set(0, MIN_THROTTLE); // Motors stoped
		Servo_Timer2_set(1, MIN_THROTTLE);
		Servo_Timer2_set(2, MIN_THROTTLE);
		Servo_Timer2_set(3, MIN_THROTTLE);
		// Initialize yaw command to actual yaw
		command_rx_yaw = ToDeg(yaw);
		command_rx_yaw_diff = 0;
	}

	Serial.println(); // Line END
	//Serial_mode_read();  // get sonar values

	autonomousCounter++;
	update_RF();
	sonar_new_data = 1;

}

/*
 * Will be called at the frequency specified in UserConstants.h.
 * Guaranteed to be accurate over time, but inaccurate in the short term.
 *
 * The delayed argument is the number of milliseconds past the scheduled execution
 * time the loop is being called.
 *
 * The elapsed argument is the number of milliseconds since the last execution.
 */
void UserRobot::fixedLoop(int delayed, int elapsed) {
	/*Serial.print("Fixed loop delayed ");
	 Serial.print(delayed);
	 Serial.println("ms.");*/

}

/*
 * Called as fast as possible. Guaranteed to be called at least once
 * between every call to commLoop.
 */
void UserRobot::fastLoop(void) {
	ControlData *control = comm->controlData;
	//Do fast loop stuff here.

	if (!comm->isConnected) {
		setOutputsEnabled(false);
	}
}
int UserRobot::RxGetChannelPulseWidth( uint8_t channel)
{
  unsigned int result;

    result = controls[channel - 1];

  if ((result > MIN_IN_PULSE_WIDTH)&&(result < MAX_IN_PULSE_WIDTH))  // Out of range?
    return result;
  else
    {
    return Neutro[channel];
    }
}
void UserRobot::Servo_Timer2_ini()
{
  // Servos must have correct values at this moment !! Call First Servo_Timer2_set() function...
  // Variable initialization
  Servo_Channel = 0;
  TIMSK2 = 0;  // Disable interrupts
  TCCR2A = 0;  // normal counting mode
  TCCR2B = _BV(CS20)|_BV(CS22);            // Set prescaler of 128  (8uS resolution at 16Mhz)
  TCNT2 = Servos[Servo_Channel].counter;   // Set the clock counter register for the overflow interrupt
  TIFR2 = _BV(TOV2);  // clear pending interrupts;
  TIMSK2 =  _BV(TOIE2) ; // enable the overflow interrupt
}

void UserRobot::Servo_Timer2_set(uint8_t servo_index, int value)
{
  int aux;

  if (value > SERVO_MAX_PULSE_WIDTH)
    value = SERVO_MAX_PULSE_WIDTH;
  else if (value < SERVO_MIN_PULSE_WIDTH)
    value = SERVO_MIN_PULSE_WIDTH;

  Servos[servo_index].value = value; // Store the desired value on Servo structure

  value = value - 20;  // We reserve 20us for compensation...

  // Calculate the overflow interrupt counter (8uS step)
  aux = value>>3;  // value/8
  Servos[servo_index].counter = 256 - aux;
}
// ROLL, PITCH and YAW PID controls...
void UserRobot::Attitude_control()
{
  // ROLL CONTROL
  if ((AP_mode==3)||(AP_mode==1))
    {
    command_rx_roll += command_RF_roll;     // Add position control term
    command_rx_roll_diff = 0;
    }

  err_roll = command_rx_roll - ToDeg(roll);

  err_roll = constrain(err_roll,-25,25);  // to limit max roll command...

  roll_I += err_roll*G_Dt;
  roll_I = constrain(roll_I,-20,20);
  // D term implementation => two parts: gyro part and command part
  // To have a better (faster) response we can use the Gyro reading directly for the Derivative term...
  // Omega[] is the raw gyro reading plus Omega_I, so it´s bias corrected
  // We also add a part that takes into account the command from user (stick) to make the system more responsive to user inputs
  roll_D = command_rx_roll_diff*KD_QUAD_COMMAND_PART - ToDeg(Omega[0]);  // Take into account Angular velocity of the stick (command)

  // PID control
  control_roll = KP_QUAD_ROLL*err_roll + KD_QUAD_ROLL*roll_D + KI_QUAD_ROLL*roll_I;

  // PITCH CONTROL
  if ((AP_mode==3)||(AP_mode==1))
    {
    command_rx_pitch += command_RF_pitch;     // Add position control term
    command_rx_pitch_diff = 0;
    }

  err_pitch = command_rx_pitch - ToDeg(pitch);

  err_pitch = constrain(err_pitch,-25,25);  // to limit max pitch command...

  pitch_I += err_pitch*G_Dt;
  pitch_I = constrain(pitch_I,-20,20);
  // D term
  pitch_D = command_rx_pitch_diff*KD_QUAD_COMMAND_PART - ToDeg(Omega[1]);

  // PID control
  control_pitch = KP_QUAD_PITCH*err_pitch + KD_QUAD_PITCH*pitch_D + KI_QUAD_PITCH*pitch_I;

  // YAW CONTROL

  err_yaw = command_rx_yaw - ToDeg(yaw);
  if (err_yaw > 180)    // Normalize to -180,180
    err_yaw -= 360;
  else if(err_yaw < -180)
    err_yaw += 360;

  err_yaw = constrain(err_yaw,-60,60);  // to limit max yaw command...

  yaw_I += err_yaw*G_Dt;
  yaw_I = constrain(yaw_I,-50,50);
  yaw_D = command_rx_yaw_diff*KD_QUAD_COMMAND_PART - ToDeg(Omega[2]);

  // PID control
  control_yaw = KP_QUAD_YAW*err_yaw + KD_QUAD_YAW*yaw_D + KI_QUAD_YAW*yaw_I;
}


//*********************************************************************8



/* Obstacle avoidance routine */
void UserRobot::Position_control(int RF_Sensor1, int RF_Sensor2,int RF_Sensor3, int RF_Sensor4)
{
  int RF_pair1;
  int RF_pair2;
  int RF_err_roll;
  int RF_err_pitch;
  long temp;



  RF_pair1 = RF_Sensor3 - RF_Sensor1;  // Back right sensor - Front left sensor
  RF_pair2 = RF_Sensor4 - RF_Sensor2;  // Back left sensor - Front right sensor

  // ROLL
  RF_err_roll_old = RF_err_roll;
  RF_err_roll = RF_pair1 - RF_pair2;

  RF_roll_D = (RF_err_roll-RF_err_roll_old)/0.06;   // RF_IR frequency is 1/60ms

  RF_roll_I += RF_err_roll*0.06;    // RF_IR frequency is 1/60ms
  RF_roll_I = constrain(RF_roll_I,-25,25);

  command_RF_roll = KP_RF_ROLL*RF_err_roll + K_aux*RF_roll_D + KI_RF_ROLL*RF_roll_I;
  command_RF_roll = constrain(command_RF_roll,-RF_MAX_ANGLE,RF_MAX_ANGLE); // Limit max command

  // PITCH
  RF_err_pitch_old = RF_err_pitch;
  RF_err_pitch = RF_pair1 + RF_pair2;

  RF_pitch_D = (RF_err_pitch-RF_err_pitch_old)/0.06;

  RF_pitch_I += RF_err_pitch*0.06;
  RF_pitch_I = constrain(RF_pitch_I,-25,25);

  command_RF_pitch = KP_RF_PITCH*RF_err_pitch + K_aux*RF_pitch_D + KI_RF_PITCH*RF_pitch_I;
  command_RF_pitch = constrain(command_RF_pitch,-RF_MAX_ANGLE,RF_MAX_ANGLE); // Limit max command
}



/* Automatic flight pattern... */
void UserRobot::Automatic_flight(int target_sonar_altitude, long flight_time)
{
  //Serial.print((int)automatic_mode);
  //Serial.print(":");
  //Serial.print(sonar_value);
  //Serial.print(":");
  //Serial.print((int)command_altitude);

  if (automatic_mode==0)   // Auto Take off
    {
    if (sonar_value<37)
      {
      command_altitude+=2;   // Increment throttle until we reach a minimun safe altitude
      }
    else
      {
      automatic_mode=1;
      automatic_mode_time = loop_counter;
      automatic_mode_initial_altitude = sonar_value;
      automatic_ascend = 0;
      err_altitude = 0;
      altitude_I = 0;
      Initial_Throttle = HOVER_THROTTLE;    //command_altitude-45;
      }
    }
  else if (automatic_mode==1)  // Altitude hold
    {
    digitalWrite(7,HIGH);
    if (automatic_mode_altitude < target_sonar_altitude)
      {
      automatic_ascend++;
      automatic_mode_altitude = automatic_mode_initial_altitude + (automatic_ascend>>2);
      }
    Altitude_control(automatic_mode_altitude);
    if (loop_counter > (automatic_mode_time + flight_time))
      {
      automatic_mode = 2;  // Start descending
      automatic_descend = 0;
      }
    }
  else if (automatic_mode==2)    // Controled descend
    {
    digitalWrite(7,LOW);
    automatic_descend++;
    Altitude_control(target_sonar_altitude-(automatic_descend>>2));
    if (sonar_value < 45)
      automatic_mode = 3;
    }
  else if (automatic_mode==3)    // Final Landing
    {
    digitalWrite(7,HIGH);
    command_altitude-=2;
    }
  command_altitude = constrain(command_altitude,MIN_THROTTLE,MAX_THROTTLE);
}
//****************************************8

/* Altitude control based on sonar sensor */
void UserRobot::Altitude_control(int target_sonar_altitude)
{
  //Serial.print(":");
  //Serial.print(target_sonar_altitude);
  //Serial.print(":");
  //Serial.print(err_altitude);
  err_altitude_old = err_altitude;
  err_altitude = target_sonar_altitude - sonar_value;
  err_altitude = constrain(err_altitude,-60,60);
  altitude_D = (float)(err_altitude-err_altitude_old)/G_Dt;
  altitude_I += (float)err_altitude*G_Dt;
  altitude_I = constrain(altitude_I,-150,150);
  command_altitude = Initial_Throttle + KP_ALTITUDE*err_altitude + KD_ALTITUDE*altitude_D + KI_ALTITUDE*altitude_I;
}
//*****************************************************

/*
 * Processes control data here, and calls the appropriate init and/or loop functions.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::commLoop(void) {
	//Serial.println((int)communication.commandData.joysticks[1].axis[1]);
	//Serial.println("Slow loop: Implement me!");
	if (comm->controlData->mode.getEnabled()) {
		setOutputsEnabled(true);
		if (comm->controlData->mode.getAutonomous()) {
			if (!autoInitComplete) {
				autonomousInit();
				autoInitComplete = true;
				teleInitComplete = false;
				disabledInitComplete = false;
			}
			autonomousLoop();
		} else {
			if (!teleInitComplete) {
				teleopInit();
				autoInitComplete = false;
				teleInitComplete = true;
				disabledInitComplete = false;
			}
			teleopLoop();
		}
	} else {
		setOutputsEnabled(false);
		if (!disabledInitComplete) {
			disabledInit();
			autoInitComplete = false;
			teleInitComplete = false;
			disabledInitComplete = true;
		}
		disabledLoop();
	}
}

