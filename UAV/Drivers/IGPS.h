/*
 * IGPS.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef IGPS_H_
#define IGPS_H_

#include "Drivers.h"

typedef enum {
	NO_GPS,
	NO_FIX,
	GPS_OK
} GPSStatus;

class IGPS {
public:
	virtual ~IGPS() = 0;

	/**
	 * Gets the status of the GPS unit.
	 * @return "NO_GPS" if the gps is off, "NO_FIX" if a fix is not acquired, or "GPS_OK" if a fix is determined.
	 */
	virtual GPSStatus getStatus() const = 0;

	/**
	 * Gets the time of the last data sampling.
	 * @return The time since the last data sampling.
	 */
	virtual long getLastTime() const = 0;

	/**
	 * Gets the latitude, in "units".
	 * @return The latitude, in "units".
	 */
	virtual long getLatitude() const = 0;

	/**
	 * Gets the longitude, in "units".
	 * @return The longitude, in "units".
	 */
	virtual long getLongitude() const = 0;

	/**
	 * Gets the altitude, in "units".
	 * @return The altitude, in "units".
	 */
	virtual long getAltitude() const = 0;

	/**
	 * Gets the ground speed (in the XY-plane), in "velocity units".
	 * @return The ground speed, in "velocity units".
	 */
	virtual long getGroundSpeed() const = 0;

	/**
	 * Gets the ground-relative heading, in radians CCW from due East.
	 * @return The ground-relative heading.
	 */
	virtual float getGroundCourse() const = 0;

	/**
	 * Gets the approximate 3D speed, in "velocity units".
	 * @return The 3D speed, in "velocity units".
	 */
	virtual long getSpeed3D() const = 0;

	/**
	 * Tells whether there is data ready from the IMU or not.
	 * @return <b>true</b> if new data is available, <b>false</b> otherwise.
	 */
	virtual bool isDataReady() const = 0;

	/**
	 * Reads data from the unit.
	 * @return <b>true</b> if data was read successfully, <b>false</b> otherwise.
	 */
	virtual bool read() = 0;
};

#endif /* IGPS_H_ */
