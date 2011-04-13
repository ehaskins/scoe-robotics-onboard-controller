/*
 * ICamera.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef ICAMERA_H_
#define ICAMERA_H_

typedef enum {
	CH_RED = 0,
	CH_GREEN = 1,
	CH_BLUE = 2
} CameraChannel;

class ICamera {
public:
	virtual ~ICamera() = 0;

	virtual void setBufferMode(bool singleFrame) = 0;

	virtual bool setCameraRegister(int addr, int val) = 0;

	virtual void setCameraPower(bool power) = 0;

	virtual void setFrameSize(int x, int y, int w, int h) = 0;

	virtual void setCameraType(bool type) = 0;

	virtual void setDiffChannel(CameraChannel ch) = 0;

	virtual void setDelayMode()

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getXOffset() = 0;
	virtual int getYOffset() = 0;

	virtual void setDownSampling(int xfact, int yfact) = 0;
	virtual int getXFactor() = 0;
	virtual int getYFactor() = 0;

	virtual bool setCameraPower()
};

#endif /* ICAMERA_H_ */
