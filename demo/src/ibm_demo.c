
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "iotfclient.h"
#include "logging.h"
#include "sensor.h"
#include "util.h"

#define MAX_PAYLOAD_SIZE 100
#define MAX_STRING 20

volatile int interrupt = 0;
static char *configFilePath = "./demo/cfg/device.cfg";
static char *deviceID = ""; 
static char *orgID = "quickstart";
static char *deviceType = "DB410c";
static char *authMethod = "token";
static char *authToken = "";
static int demo = 1;

// Handle signal interrupt
void sigHandler(int signo) {
	printf("SigINT received.\n");
	interrupt = 1;
}

/*******************************************************************************
*	parseInputArgsForConnectParams
*
********************************************************************************/
void parseInputArgsForConnectParams(int argc, char** argv) {
	int opt;

	while (-1 != (opt = getopt(argc, argv, "c:d:o:t:m:k:"))) {
		switch (opt) {
		case 'c':
			configFilePath = (char*) optarg;
			DEBUG("DeviceConfig file: %s\n", (char*) optarg);
			break;
		case 'd':
			deviceID = (char*) optarg;
			break;
		case 'o':
			orgID = (char*) optarg;
			break;
		case 't':
			deviceType = (char*) optarg;
			break;
		case 'm':
			authMethod = (char*) optarg;
			break;
		case 'k':
			authToken = (char*) optarg;
			break;
		case '?':
			if (optopt == 'c') {
				ERROR("Option -%c requires an argument.\n", optopt);
			}
			else if (isprint(optopt)) {
				WARN("Unknown option `-%c'.\n", optopt);
			}
			else {
				WARN("Unknown option character `\\x%x'.\n", optopt);
			}
			break;
		default:
			ERROR("Error in command line argument parsing\n");
			break;
		}
	}

}


void myCallback (char* commandName, char* format, void* payload)
{
	printf("------------------------------------\n" );
	printf("The command received :: %s\n", commandName);
	printf("format : %s\n", format);
	printf("Payload is : %s\n", (char *)payload);

	printf("------------------------------------\n" );
}

int main(int argc, char *argv[])
{
	int rc = -1;
	char buf[MAX_PAYLOAD_SIZE];
	char *addr; 
	char id[MAX_STRING];
	
	//
	//Parse Input-parameters
	//
	parseInputArgsForConnectParams(argc, argv);

	Iotfclient client;

	//catch interrupt signal
	signal(SIGINT, sigHandler);
	signal(SIGTERM, sigHandler);

	struct stat reqFileStat;

	if(demo)
    	{
		

		addr = GetMACAddress();
		Strip(addr, id, ':' );
		deviceID = id;
		orgID = "quickstart";

		printf(	"##########################################\n"
			"# DeviceID: %s\n"
			"##########################################\n",deviceID);
    		
		printf(	"Configuring client with demo parameters:\n"
			"OrgID=%s\n"
			"DeviceType=%s\n"
			"DeviceID=%s\n"
			"AuthMethod=%s\n"
			"AuthToken=%s\n"
			,orgID
   			,deviceType
    			,deviceID
    			,authMethod
    			,authToken
			);
    		rc = initialize( &client,
    					 orgID,
    					 deviceType,
    					 deviceID,
    					 authMethod,
    					 authToken);
    		if(rc != SUCCESS){
    		printf("initialize failed and returned rc = %d.\n Quitting..", rc);
    		return -1;
    		}
    	}
	else if (stat(configFilePath, &reqFileStat) == 0)	//check if config-file is available
	{
		printf("Configuring client via ConfigFile: %s\n", configFilePath);
		rc = initialize_configfile(&client, configFilePath);
		if(rc != SUCCESS){
			printf("initialize failed and returned rc = %d.\n Quitting..", rc);
			return -1;
		}
	}
	else
	{
		printf(	"Configuring client via cmdline:\n"
			"OrgID=%s\n"
			"DeviceType=%s\n"
			"DeviceID=%s\n"
			"AuthMethod=%s\n"
			"AuthToken=%s\n"
			,orgID
   			,deviceType
    			,deviceID
    			,authMethod
    			,authToken
			);
		rc = initialize( &client, 
				 orgID, 
				 deviceType, 	
				 deviceID, 
				 authMethod, 
				 authToken);
		if(rc != SUCCESS){
			printf("initialize failed and returned rc = %d.\n Quitting..", rc);
			return -1;
		}	
	}

	

	rc = connectiotf(&client);
	if(rc != SUCCESS){
		printf("Connection failed and returned rc = %d.\n Quitting..", rc);
		return 0;
	}

	setCommandHandler(&client, myCallback);

	void* sensor = CreateSensor();

	while(!interrupt) 
	{
		int value = GetSensorValue(sensor);
		printf("Lux = %d\n", value);
		sprintf(buf, "{\"d\" : {\"light_sensor\" : %d }}", value );
		
		printf("Publishing the event stat with rc ");
		rc= publishEvent(&client, "data","json", buf, QOS0);

		printf(" %d\n", rc);
		yield(&client, 1000);
		sleep(2);
	}

	printf("Quitting!!\n");

	disconnect(&client);

	return 0;
}
