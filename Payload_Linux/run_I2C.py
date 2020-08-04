from smbus import SMBus
import os 


addr = 0x8

while (True): 

	order = SMBus(1).read_byte(addr)
	print (order)
	if order==1:
		os.system("./run.sh 1 30")
		 
	
