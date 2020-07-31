#!/bin/bash


#Function to check USB driver of camera in case camera initialization fails
USBcheck() {
	sudo systemctl start ueyeethdrc
	sudo systemctl start ueyeusbdrc
}

if [ $# -ne 2 ] 
then 
	echo "Illegal number of arguments"
	exit 999
fi 

#Checks for the main executable file just in case it is not there
#If it isnt, run the make command that will run the Makefile
if [[ ! -f "main" ]]
then 
	`make`
fi

#Here we run what tha make command outputs and give the c code two inputs:
#		$1: How many cameras to activate
#		#2: how many pictures to take in a burst for the startracker camera

#Here we just do a small if condition to check whether the folder for the first camera exists
#or not
if [ ! -d "/home/alarm/Desktop/IDS_camera" ] 
then
	mkdir /home/alarm/Desktop/IDS_camera
fi 

#The ./main script controls the IDS camera while ./cameraRasp controls the raspberry Camera
if [ $1 -eq 1 ] 
then 
	./main 1 $2
	if [ $? -eq 1 ] 
	then
		USBcheck
		./main 1 $2
	fi
elif [ $1 -eq 2 ] 
then 
	./main 1 $2
	if [ $? -eq 1 ]
	then 
		USBcheck
		./main 1 $2
	fi 
	./cameraRasp.sh
else 
	echo "Inputs are invalid, try again"
	exit 3
fi 

#does a cleanup of the folder after this script has been executed
rm -r main
rm -r main.o
rm -r cameraLibrary.o
rm -r stm32_I2C
