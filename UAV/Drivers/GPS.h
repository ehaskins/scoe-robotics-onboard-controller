/*
 * GPS.h
 *
 *  Created on: Apr 11, 2011
 *      Author: Nick
 */

#ifndef GPS_H_
#define GPS_H_

#include "BaseSensor.h"

class GPS: public BaseSensor, public IGPS {
protected:
	bool m_dataReady;

public:
	GPS();
	virtual ~GPS();

	void onInit(int port);
	void onEnable();
	void onDisable();
	void onNewData();

	GPSStatus getStatus() const;

	long getLastTime() const;

	long getLatitude() const;
	long getLongitude() const;
	long getAltitude() const;

	long getGroundSpeed() const;
	long getGroundCourse() const;
	long getSpeed3D() const;

	bool isDataReady() const;
	bool read();
};

#endif /* GPS_H_ */
