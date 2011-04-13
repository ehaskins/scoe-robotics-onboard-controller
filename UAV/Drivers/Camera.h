/*
 * Camera.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Drivers.h"

#include "ICamera.h"
#include "BaseSensor.h"

typedef enum {
	CMU_BM,			// Buffer Mode
	CMU_CR,			// Camera Register
	CMU_CP,			// Camera Power
	CMU_CT,			// Camera Type
	CMU_DC,			// Differencing Channel
	CMU_DM,			// Delay Mode
	CMU_DS,			// Down Sampling
	CMU_FD,			// Frame Differencing
	CMU_FS,			// Frame Streaming
	CMU_GB,			// Get Button
	CMU_GH,			// Get Histogram
	CMU_GI,			// Get Input
	CMU_GM,			// Get Mean
	CMU_GS,			// Get Servo
	CMU_GT,			// Get Track
	CMU_GV,			// Get Version
	CMU_GW,			// Get Window
	CMU_HC,			// Histogram Config
	CMU_HD,			// Hi-res Differencing
	CMU_HR,			// Hi-Res mode
	CMU_HT,			// Histogram Tracking
	CMU_L0,			// LED 0
	CMU_L1,			// LED 1
	CMU_LF,			// Load Frame
	CMU_LM,			// Line Mode
	CMU_MD,			// Masked Differencing
	CMU_NF,			// Noise Filter
	CMU_OM,			// Output Mask
	CMU_PD,			// Pixel Differencing
	CMU_PF,			// Packet Filtering
	CMU_PM,			// Poll Mode
	CMU_PS,			// Packet Skip
	CMU_RF,			// Read Frame
	CMU_RM,			// Raw Mode
	CMU_RS,			// Reset
	CMU_SD,			// Sleep Deeply
	CMU_SF,			// Send Frame
	CMU_SL,			// Sleep
	CMU_SM,			// Servo Mask
	CMU_SO,			// Servo Output
	CMU_SP,			// Servo Parameters
	CMU_ST,			// Set Tracking
	CMU_SV,			// Servo Value (position)
	CMU_TC,			// Track Color
	CMU_TI,			// Track Inverted
	CMU_TW,			// Track Windowed
	CMU_UD,			// Upload Difference
	CMU_VW			// Virtual Window
} CMUCAM_CMDS;

class Camera : public BaseSensor, public ICamera {
public:
	Camera();
	virtual ~Camera();
};

#endif /* CAMERA_H_ */
