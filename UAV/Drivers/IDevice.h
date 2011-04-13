/*
 * IDevice.h
 *
 *  Created on: Apr 5, 2011
 *      Author: Nick Iannone
 */

#ifndef IDEVICE_H_
#define IDEVICE_H_

// Define an invalid port.
#ifndef NO_PORT
	#define NO_PORT	-1
#endif

class IDevice {
public:
	virtual ~IDevice() = 0;

	/**
	 * Initializes the device. Subsequent calls to isActive() should return <b>true</b>.
	 */
	virtual void init() = 0;

	/**
	 * Tells whether the device has been initialized, via a call to init().
	 * @return <b>true</b> if the device has been initialized, <b>false</b> otherwise.
	 */
	virtual bool isActive() const = 0;

	/**
	 * Gets the number of the port to which the device has been attached.
	 * @return The port of the device, or -1 if the device is not active.
	 */
	virtual int getPort() const = 0;

	/**
	 * Tells whether the device has been enabled, via a call to setEnabled().
	 * @return <b>true</b> if the device has been enabled, <b>false</b> otherwise.
	 */
	virtual bool isEnabled() const = 0;

	/**
	 * Enables or disables the device.
	 * @param enable If <b>true</b>, enables the device; otherwise, disables the device.
	 * @param quick If <b>true</b>, quickly enables/disables the device. Used for emergency stops or unexpected fast-resets.
	 */
	virtual void setEnabled(bool enable, bool quick) = 0;
};

#endif /* IDEVICE_H_ */
