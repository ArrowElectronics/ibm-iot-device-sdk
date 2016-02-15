#include <stdio.h>

#define SENSOR_CNT 3
#define SENSOR_DATA_SIZE 100
#define MESSAGE_SIZE (SENSOR_CNT * SENSOR_DATA_SIZE + 200)


static char buf[MESSAGE_SIZE];
static char sensor_buf[SENSOR_DATA_SIZE];


char* GetSensorData1()
{
	sprintf(sensor_buf, "{"   \
		     	 	 	" 	\"sensor\" : \"%s\",		"	\
						"	\"dimension\" : \"%s\",		"	\
						"	\"unit\" : \"%s\",			"	\
						"	\"value\" : %f				"	\
						"}"
						, "sensor1"
						, "Temperature"
						, "Celsius"
						, 32.2
				 );
	return sensor_buf;
}

char* GetSensorData2()
{
	return "";
}

char* GetSensorData3()
{
	return "";
}


char* GetSensorData()
{


	sprintf(buf, "{\"d\" : "	\
				 "       %s, "	\
				 "} "   \
				 , GetSensorData1()
			);

	return buf;
}

/*
char* GetSensorData()
{
	sprintf(buf,
					"{\"d\" :								"	\
					"	{									"	\
					" 	\"sensor data\":					"	\
					"	[									"	\
			        "		{								"	\
					"		\"sensor\" : 	\"Sensor1\"		"	\
			        "		\"dimension\" : \"Temperatur\"	"	\
			        "		\"unit\" : \"Celsius\"			"	\
			        "   	\"value\" : 32.2				"	\
			        "		},								"	\
			        "		{								"	\
					"		\"sensor\" : 	\"Sensor2\"		"	\
			        "		\"dimension\" : \"Temperatur\"	"	\
			        "		\"unit\" : \"Celsius\"			"	\
			        "   	\"value\" : 42.2				"	\
			        "		},								"	\
			        "		{								"	\
					"		\"sensor\" : 	\"Sensor3\"		"	\
			        "		\"dimension\" : \"Temperatur\"	"	\
			        "		\"unit\" : \"Celsius\"			"	\
			        "   	\"value\" : 52.2				"	\
			        "		}								"	\
			        "	]									"	\
			   	    "	}									"	\
					"}										"
				);

}
*/


