from smbus import SMBus
import os 


addr = 0x8

while (True): 

	order = SMBus(1).read_byte(addr)
	if (order==0):
		os.system("./run.sh 1 15")
	elif (order==1):
		os.system("./run.sh 2 15")
	elif (order==2):
		os.system("./run.sh 3 15")
	elif (order==9):
		os.system("reboot")
