#include <stdio.h>
#include "sensor.h"
#include "upm/tsl2561.h"

void* CreateSensor()
{
	upm::TSL2561 *sensor;
	sensor = new upm::TSL2561();
	
	return (void*) sensor;
}

int GetSensorValue(void* sensor_)
{
	upm::TSL2561 *sensor = (upm::TSL2561 *) sensor_;
	if(sensor)
		return sensor->getLux();
	else
		return 0;
}

void DestroySensor(void* sensor_)
{
	upm::TSL2561 *sensor = (upm::TSL2561 *) sensor_;
	if(sensor)
		delete sensor;
}


	