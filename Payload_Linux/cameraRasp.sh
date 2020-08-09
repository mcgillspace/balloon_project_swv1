#!/bin/bash

#To make sure the camera works on the pi. We need to export the 
#raspistill command that is located in /opt/vc/bin. DO NOT 
#PLAY WITH THE CONFIG.TXT FILE AS SUGGESTED ONLINE, THERE IS NO NEED. 

#Checks whether the camera modules command have been loaded in 
#the PATH variable or not

echo $PATH | grep -q "/opt/vc/bin"

if [ $? -eq 1 ]
then 
	PATH=$PATH:/opt/vc/bin
	export PATH
else
	export PATH
fi 

#Checks whether the folder in which images are going to saved is present or not.
#If it isnt, create this folder and name it Rasp_camera
if [ ! -d "/home/alarm/Desktop/Raspb_camera" ]
then 
	mkdir /home/alarm/Desktop/Raspb_camera
fi

#Take a burts of size equal to the first argument when running this script. The interval between images 
#is 1 second and it timestamps the images based on the time of acquisition
cond="0"
while [[ "$cond" -lt "$1" ]]
do 
	DATE=$(date +"%H_%M_%S")
	raspistill -vf -hf -sa 100 -md 1 -o /home/alarm/Desktop/Raspb_camera/ImagePi_$DATE.jpg --nopreview --timeout 1
	sleep 1s
	cond=$(($cond+1))
done
