#!/bin/bash

#Checks for the main executable file just in case it is not there
#If it isnt, run the make command that will run the Makefile
if [[ ! -f "main" ]]
then 
	`make`
fi

#Here we run what tha make command outputs and give the c code two inputs:
#		$1: which mode the camera is operating in (right now either 
#		0 for singleCapture and 1 for BurstCapture)
#		#2: how many pictures to take in a burst
./main $1 $2

#does a cleanup of the folder after this script has been executed
rm -r main
rm -r main.o
rm -r cameraLibrary.o
