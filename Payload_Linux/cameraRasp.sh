#!/bin/bash

#To make sure the camera works on the pi. We need to export the 
#raspistill command that is located in /opt/vc/bin. DO NOT 
#PLAY WITH THE CONFIG.TXT FILE AS SUGGESTED ONLINE, THERE IS NO NEED. 

#checks whether the camera modules command have been loaded in 
#the PATH variable or not

echo $PATH | grep -q "/opt/vc/bin"

if [ $? -eq 1 ];
then 
	PATH=$PATH:/opt/vc/bin
	export PATH
else
	export PATH
fi 
DATE=$(date +"%H_%M_%S")

if [ ! -d "/home/alarm/Desktop/Raspb_camera" ]
then 
	mkdir /home/alarm/Desktop/Raspb_camera
fi

raspistill -vf -hf -sa 100 -md 1 -o /home/alarm/Desktop/Raspb_camera/ImagePi_$DATE.jpg

