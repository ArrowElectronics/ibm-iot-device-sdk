#! /bin/bash

echo "########################################################################"
echo "#                                                                      #"
echo "# This script upgrades your DragonBoard410c's environment to run the   #"
echo "# examples of the IBM-iot-starter-kit.                                 #"
echo "#                                                                      #"
echo "########################################################################"

echo "------------------------------------------------------------------------"
echo "Install prerequisites:                                                  "
echo "------------------------------------------------------------------------"
sudo apt-get update
sudo apt-get install -y git build-essential autoconf libtool swig3.0 \
python-dev nodejs-dev cmake pkg-config libpcre3-dev
sudo apt-get clean

echo "------------------------------------------------------------------------"
echo "Create Project directory:                                               "
echo "------------------------------------------------------------------------"
mkdir ~/Projects

echo "------------------------------------------------------------------------"
echo "Install Arrows ibm-iot-starter-kit repository:                          "
echo "------------------------------------------------------------------------"
cd ~/Projects
git clone https://github.com/ArrowElectronics/ibm-iot-starter-kit 

echo "------------------------------------------------------------------------"
echo "Install IBM-MQTT-Client:                                                "
echo "------------------------------------------------------------------------"
cd ~/Projects
git clone https://github.com/ibm-messaging/iotf-embeddedc.git

echo "------------------------------------------------------------------------"
echo "Install MRAA library:                                                   "
echo "------------------------------------------------------------------------"
#mraa is a development library that provides access to the kernels i2c, gpio 
#and spi interfaces.

cd ~/Projects
git clone https://github.com/intel-iot-devkit/mraa
cd mraa
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig /usr/local/lib/

echo "------------------------------------------------------------------------"
echo "Install UPM library:                                                    "
echo "------------------------------------------------------------------------"
#UPM is an object oriented library of drivers for many Grove I2C devices, such 
#as the Grove RGB backlight LCD module #included in this kit.
#Be patient with this step. UPM takes about 23 minutes to build.
cd ~/Projects
sudo ln -s /usr/bin/swig3.0 /usr/bin/swig
git clone https://github.com/intel-iot-devkit/upm
cd upm
mkdir build
cd build
cmake -DBUILDSWIGNODE=OFF ..
make
sudo make install
sudo ldconfig /usr/local/lib/libupm-*

echo "------------------------------------------------------------------------"
echo "Configure the software:                                                 "
echo "------------------------------------------------------------------------"
#The last step is to install some configuration files so that the development 
#tools know which devices to uses. Fetch #the 96boards-tools package and install
#the provided configuration files:
cd ~/Projects
sudo addgroup linaro i2c  # Allow the normal user to perform i2c operations
git clone https://github.com/96boards/96boards-tools
sudo cp 96boards-tools/70-96boards-common.rules /etc/udev/rules.d/

echo 'export JAVA_TOOL_OPTIONS="-Dgnu.io.rxtx.SerialPorts=/dev/tty96B0" export MONITOR_PORT=/dev/tty96B0 export PYTHONPATH="$PYTHONPATH:/usr/local/lib/python2.7/site-packages"' | sudo tee /etc/profile.d/96boards-sensors.sh
sudo cp /etc/profile.d/96boards-sensors.sh /etc/X11/Xsession.d/96boards-sensors

echo "------------------------------------------------------------------------"
echo "Build the demo                                                          "
echo "------------------------------------------------------------------------"
cd ~/Projects/ibm-iot-starter-kit/demo
make ibm_demo

echo "------------------------------------------------------------------------"
echo "Create a shortcut on the desktop                                        "  
echo "------------------------------------------------------------------------"
cp ~/Projects/ibm-iot-starter-kit/db410c_demo.desktop ~/Desktop
cp ~/Projects/ibm-iot-starter-kit/ibm_iot_explore.desktop ~/Desktop


echo -e "Installation complete. Ready to reboot(recommended)? (y/n):"
read reply
if [ "$reply" == "y" ] ; then
echo "------------------------------------------------------------------------"
echo "Reboot the system:                                                      "
echo "------------------------------------------------------------------------"
#Now reboot the system to pick up all the changes.
sudo reboot
fi