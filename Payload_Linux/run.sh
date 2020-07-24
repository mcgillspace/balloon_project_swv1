#!/bin/bash

if [[ ! -f "main" ]]
then 
	`make`
fi

./main $1 $2
rm -r main
rm -r main.o
rm -r cameraLibrary.o
