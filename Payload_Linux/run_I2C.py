import Raspb_I2C
import smbus
import os 


addr = 0x8

while (true): 

	order = SMBus(1).read_byte(addr)
	if order==1:
		os.system("./run.sh 1 30")
		 
	
