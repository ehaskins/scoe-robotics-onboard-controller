/*
 * UserCode.cpp
 *
 *  Created on: Feb 13, 2011
 *      Author: EHaskins
 */

#include "UserCode.h"
#include <WProgram.h>
#include <FrcComms\FRCCommunication.h>
//#include <Servo.h>
#include "Utils.h"
#include "UserConstants.h"

// Drive motors and PID controllers.
static Motor leftMotor;
static Motor rightMotor;
static Motor rearMotor;

static LimitMotor leftLimitMotor;
static LimitMotor rightLimitMotor;
static LimitMotor rearLimitMotor;

#if USING_PID_CONTROLLER
static PIDMotor leftPIDMotor;
static PIDMotor rightPIDMotor;
static PIDMotor rearPIDMotor;

// Drive encoders.
static Encoder leftEncoder;
static Encoder rightEncoder;
static Encoder rearEncoder;

// Drive speed sensors.
static SpeedSensor leftSpeedSensor;
static SpeedSensor rightSpeedSensor;
static SpeedSensor rearSpeedSensor;
#endif

// Drive system.
static KiwiDrive kiwidrive;

#if USING_LAUNCHER
// Launcher motors and sensors.
static Motor launchMotor;
static Motor intakeMotor;
static DigitalInput loadSensor;
static DigitalInput intakeSensor;

// Launch system.
static BallLauncher launcher;
#endif

/*
 * Guaranteed to be called after the following have been initialized:
 * Ethernet, configuration, serial, and FRCComms.
 *
 * Place any one time robot specific initialization code here.
 */
void UserRobot::userInit(void) {

	comm = FRCCommunication::getInstance();
	//Initialize user code, robot sensors, etc. here.
	autoInitComplete = false;
	teleInitComplete = false;
	disabledInitComplete = false;

	// Initialize the robot parts.
	Serial.println("Initializing robot parts...");
	Serial.println(millis());

	// 137"/s max speed, approx., with gearbox and CIM motors.
	leftMotor.setBounds(-USER_MOTOR_MAX_SPEED, USER_MOTOR_MAX_SPEED);
	rightMotor.setBounds(-USER_MOTOR_MAX_SPEED, USER_MOTOR_MAX_SPEED);
	rearMotor.setBounds(-USER_MOTOR_MAX_SPEED, USER_MOTOR_MAX_SPEED);

	leftMotor.setInverted(USER_INVERT_LEFT_MOTOR);
	rightMotor.setInverted(USER_INVERT_RIGHT_MOTOR);
	rearMotor.setInverted(USER_INVERT_REAR_MOTOR);

	leftMotor.setIdle(USER_MOTOR_IDLE_SPEED);
	rightMotor.setIdle(USER_MOTOR_IDLE_SPEED);
	rearMotor.setIdle(USER_MOTOR_IDLE_SPEED);

	leftMotor.init(PIN_LEFT_MOTOR);
	rightMotor.init(PIN_RIGHT_MOTOR);
	rearMotor.init(PIN_REAR_MOTOR);

	// Set up the limit motors (derivative saturation).
	leftLimitMotor.init(&leftMotor, USER_MAX_SHIFT);
	rightLimitMotor.init(&rightMotor, USER_MAX_SHIFT);
	rearLimitMotor.init(&rearMotor, USER_MAX_SHIFT);

#if USING_PID_CONTROLLERS
	// Set up the encoders.
	leftEncoder.setNumTicksPerCycle(USER_LEFT_ENCODER_PPR);
	rightEncoder.setNumTicksPerCycle(USER_RIGHT_ENCODER_PPR);
	rearEncoder.setNumTicksPerCycle(USER_REAR_ENCODER_PPR);

	leftEncoder.init(PIN_LEFT_ENCODER_DIR, PIN_LEFT_ENCODER_INT);
	rightEncoder.init(PIN_RIGHT_ENCODER_DIR, PIN_RIGHT_ENCODER_INT);
	rearEncoder.init(PIN_REAR_ENCODER_DIR, PIN_REAR_ENCODER_INT);

	// Set up the speed sensors.
	leftSpeedSensor.init(&leftEncoder, USER_WHEEL_DIAMETER);
	rightSpeedSensor.init(&rightEncoder, USER_WHEEL_DIAMETER);
	rearSpeedSensor.init(&rearEncoder, USER_WHEEL_DIAMETER);

	// Set up the PID motors (sensor feedback control).
	leftPIDMotor.init(&leftLimitMotor, &leftSpeedSensor);
	rightPIDMotor.init(&rightLimitMotor, &rightSpeedSensor);
	rearPIDMotor.init(&rearLimitMotor, &rearSpeedSensor);

	// Set up the drive system.
	kiwidrive.init((IMotor*)&leftPIDMotor, (IMotor*)&rightPIDMotor, (IMotor*)&rearPIDMotor);
#else
	kiwidrive.init((IMotor*)&leftLimitMotor, (IMotor*)&rightLimitMotor, (IMotor*)&rearLimitMotor);
#endif
	kiwidrive.invertForward(USER_INVERT_FORWARD);
	kiwidrive.invertStrafe(USER_INVERT_STRAFE);
	kiwidrive.invertYaw(USER_INVERT_YAW);

#if USING_LAUNCHER
	// Launcher stuff.
	launchMotor.setBounds(-USER_LAUNCHER_MAX_SPEED, USER_LAUNCHER_MAX_SPEED);
	launchMotor.setIdle(USER_LAUNCHER_IDLE_SPEED);
	launchMotor.setInverted(USER_INVERT_LAUNCH_MOTOR);
	launchMotor.init(PIN_LAUNCH_MOTOR);

	intakeMotor.setBounds(-USER_INTAKE_MAX_SPEED, USER_INTAKE_MAX_SPEED);
	intakeMotor.setIdle(USER_INTAKE_IDLE_SPEED);
	intakeMotor.setInverted(USER_INVERT_INTAKE_MOTOR);
	intakeMotor.init(PIN_INTAKE_MOTOR);

	loadSensor.init(PIN_LOAD_SWITCH);
	intakeSensor.init(PIN_INTAKE_SWITCH);

	launcher.init((IDigitalInput*)&loadSensor, (IDigitalInput*)&intakeSensor, (IMotor*)&launchMotor, (IMotor*)&intakeMotor);
#endif

	Serial.println("Initialization complete.");
	Serial.println(millis());
}

/*
 * Disabled and enables all outputs. Must be implemented or a disabled robot may behave irratically.
 */
void UserRobot::setOutputsEnabled(bool enabled) {
	if (enabled && !attached) {
		kiwidrive.setEnabled(true);
#if USING_LAUNCHER
		launcher.setEnabled(true);
#endif
		attached = true;
	} else if (!enabled && attached) {
		kiwidrive.setEnabled(false);
#if USING_LAUNCHER
		launcher.setEnabled(false);
#endif
		attached = false;
	}
}

/*
 * Perform any initialization needed before teleop mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::teleopInit(){
	setOutputsEnabled(true);
}

enum XboxJoysticks {
	LEFT_X = 0,
	LEFT_Y = 1,
	LR_ANALOG = 2,
	RIGHT_X = 3,
	RIGHT_Y = 4
};

/*
 * Process teleop control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::teleopLoop() {

	// Get the control stick.
	Joystick stick = comm->controlData->joysticks[0];

	// Re-center the control axes.
	int forward = stick.axis[LEFT_Y];	// 1
	int strafe = stick.axis[LEFT_X];	// 2
	int rotate = stick.axis[RIGHT_X];	// 4

	// Drive the damn robot.
	int controls[] = { forward, strafe, rotate };
	kiwidrive.driveSystem(controls);

	// Launch the ball.
#if USING_LAUNCHER

	bool fire = (stick.axis[LR_ANALOG] > 64);

	if (fire) {
		launcher.driveLauncher(USER_LAUNCHER_FIRE_SPEED);
	} else {
		launcher.driveLauncher(USER_LAUNCHER_IDLE_SPEED);
	}

	// Activate the intake belt.
	if ((launcher.isIntakePrimed() || fire) && !launcher.isLoaded()) {
		// Activate the intake belt.
		launcher.driveIntake(USER_INTAKE_RUN_SPEED);
	} else {
		launcher.driveIntake(USER_INTAKE_IDLE_SPEED);
	}
#endif
}

/*
 * Perform any initialization needed before disabled mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::disabledInit(){
	setOutputsEnabled(false);
}
/*
 * Process disabled control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::disabledLoop(){

}

bool goingUp = false;
int autoSpeed = 0;

/*
 * Perform any initialization needed before autonomous mode.
 *
 * Guaranteed to be called prior to teleopInit's first call after first boot or autoInit or disabledInit have been called.
 */
void UserRobot::autonomousInit(){
#if CALIBRATION_MODE
	setOutputsEnabled(true);

	leftLimitMotor.setSpeed(leftLimitMotor.getIdle());
	rightLimitMotor.setSpeed(rightLimitMotor.getIdle());
	rearLimitMotor.setSpeed(rearLimitMotor.getIdle());
#else
	setOutputsEnabled(false);
#endif
}


int autonomousCounter;
/*
 * Process autonomous control data here.
 * This code is called every time new control data is received.
 * In theory this will be called at 50hz, but due to network losses, etc. the
 * actual rate will be less than 50hz, and not guaranteed.
 */
void UserRobot::autonomousLoop(){
	autonomousCounter++;
#if CALIBRATION_MODE
	if (goingUp) {
		autoSpeed++;
		if (autoSpeed == USER_MOTOR_MAX_SPEED) {
			goingUp = false;
		}
	} else {
		autoSpeed--;
		if (autoSpeed == -USER_MOTOR_MAX_SPEED) {
			goingUp = true;
		}
	}
	leftLimitMotor.setSpeed(autoSpeed);
	rightLimitMotor.setSpeed(autoSpeed);
	rearLimitMotor.setSpeed(autoSpeed);
#endif
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
			if (!autoInitComplete){
				autonomousInit();
				autoInitComplete = true;
				teleInitComplete = false;
				disabledInitComplete = false;
			}
			autonomousLoop();
		} else {
			if (!teleInitComplete){
				teleopInit();
				autoInitComplete = false;
				teleInitComplete = true;
				disabledInitComplete = false;
			}
			teleopLoop();
		}
	}
	else{
		setOutputsEnabled(false);
		if (!disabledInitComplete){
			disabledInit();
			autoInitComplete = false;
			teleInitComplete = false;
			disabledInitComplete = true;
		}
		disabledLoop();
	}
}
