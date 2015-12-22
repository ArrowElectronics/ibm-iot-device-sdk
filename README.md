# ibm-iot-device-sdk

# Introduction
The folowing guide takes you through the steps to get your DragonBoard410c connected to the IBM IoT Foundation service.

(You can also find this guide on IBM's recipe website [here](https://developer.ibm.com/recipes/tutorials/dragonboard410c-recipe/))


## Step1: Prepare the IoT Cloud Service
### Signing up with IBM Bluemix:
Go to [IBM Bluemix](https://console.ng.bluemix.net/home/). If you are an existing Bluemix user, log in as usual.
If you are new to Bluemix you can sign up for their free 30 day trial.

### Create an Internet of Things Foundation Service instance:
Once logged into the IBM Bluemix account, open the IBM Bluemix Catalog and select the Internet of Things Foundation Service.
![Image of IBM Bluemix Catalog](https://raw.githubusercontent.com/ArrowElectronics/ibm-iot-device-sdk/master/images/ibm_bluemix_catalog.png)
Create and start an instance of the Internet of Things Foundation Service.

### Create an Organization:
The first time you start the Internet of Things Foundation Service you will be asked to setup an organization. Just follow the onscreen instructions.

### Add your device:
Once you created an organization through Bluemix, you can register and add a your device.

* Select the IoTF organization dashboard and click 'Add a new device’.
* Follow the on screen instructions

During the device registration process you will get the following information:

* Organization ID
* Device Type ID
* Device ID
* Authentication Method
* Authentication Token

! Please keep note of this information as you will need it at a later step !

## Step2: Prepare your device
### Download the MQTT-client app:
To install the Internet of Things Foundation client library and MQTT-clientapp for Embedded C on your device, follow the instructions below.
* To install the latest version of the library, enter the following code in your command line.
```sh
[root@localhost ~]# git clone https://github.com/ibm-messaging/iotf-embeddedc.git
```
* Extract the downloaded compressed file:
```sh
cd iotf-embeddedc
tar xvzf org.eclipse.paho.mqtt.embedded-c-1.0.0.tar.gz
```
* The extracted client app has the following file structure:
```sh
|-lib - contains all the dependent files
|-samples - contains the helloWorld and sampleDevice samples
 |-sample device.c - sample device implementation
 |-helloworld.c - quickstart application
 |-README.md
 |-Makefile
 |-build.sh
|-iotfclient.c - Main client file
|-iotfclient.h - Header file for the client
```

### Build the MQTT-client app:
Before you can run the sample MQTT-client app you need to build it from source:
Switch to the samples folder and execute Make:
```sh
cd iotf-embeddedcsamples
make
```
You should see the following output on the screen:
```sh
cc sampleDevice.c -I ./../ -I ./../lib ./../iotfclient.c ./../lib/MQTTClient.c ./../lib/MQTTLinux.c ./../lib/MQTTFormat.c ./../lib/MQTTPacket.c ./../lib/MQTTDeserializePublish.c ./../lib/MQTTConnectClient.c ./../lib/MQTTSubscribeClient.c ./../lib/MQTTSerializePublish.c ./../lib/MQTTConnectServer.c ./../lib/MQTTSubscribeServer.c ./../lib/MQTTUnsubscribeServer.c ./../lib/MQTTUnsubscribeClient.c -o sampleDevice
strip sampleDevice
```

### Configure the MQTT-client app connection parameters:
In order for the MQTT-client app to connect to the IoT Foundation service it needs the correct connectionpoarameters you received during step1.
The connection parameters can be passsed through the commandline or simply passed in through a device configuration file:

Open the device configuration file in your favorite file-editor : iotf-embeddedcsamples/device.cfg
```sh
nano device.cfg
```

Add the configuration parameters you retrieved during Step1.
```sh
org=$orgId
type=$myDeviceType
id=$myDeviceId
auth-method=$token
auth-token=$token
```

### Start the sample MQTT-client app:
To start the client app simply type:
```sh
./sampleDevice
```

Once started the client app should connect to the service and you should see the following output on the screen:
```sh
Connecting to registered service with org <your org>
Publishing the event stat with rc 0
Publishing the event stat with rc 0
Publishing the event stat with rc 0
...
```
The sample MQTT-Client app is now connected to the IoT foundation service and produces sample data.


## Step3: Verify connection in the IoT Foundation Dashboard
Once the Client-app is started we can verify the connection and incoming data on the IoT Foundation Dashboard:
* Log into your IBM bluemix account and start the IOT Foundation Dashboard
* You should see the incoming JSON messages from the client app on your board:
![Image of iot dashboard](https://raw.githubusercontent.com/ArrowElectronics/ibm-iot-device-sdk/master/images/iot_foundation_dashboard.png)

# Where to go from here...
This recipe showed the basic steps required to establish a connection between the MQTT-client app on your device with the IoT Foundation service in the cloud.

Now it`s up to you to expand on this example and build your own IoT application using the DragonBoard 410c and IBM's IoT Foundation service.

Also check out the other recipes for inspiration and don't forget to post your recipes to inspire others.

For instance:  

* Expand the sample MQTT client app to access the DragonBoard hardware:
 * Read DragonBoard410c hardware state
 * Read values of connected sensors
 * Controll connected actors (lights, motors, etc...)
* Expand the cloud service by combining the IoT Foundation Service with other Bluemix applications to work on the data from the device :
 * Data Visualization
 * Data storage
 * Data analytics


For details regarding the DragonBoard410c see:
http://arrow.com/dragonboard410c

# Purchase the DragonBoard410c
You can purchase the DragonBoard410c directly from Arrow's website: https://www.arrow.com/en/products/dragonboard410c/arrow-development-tools#page-1
