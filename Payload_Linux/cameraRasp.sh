#!/bin/bash

#To make sure the camera works on the pi. We need to export the 
#raspistill command that is located in /opt/vc/bin. DO NOT 
#PLAY WITH THE CONFIG.TXT FILE AS SUGGESTED ONLINE, THERE IS NO NEED. 

#checks whether the camera modules command have been loaded in 
#the PATH variable or not

echo $PATH | grep -q "/opt/vc/bin"

if [ $? -eq 0 ];
then 
	PATH=$PATH:/opt/vc/bin
	export PATH
else
	export PATH
fi 

raspistill -vf -hf -t 0 -sa 100

