from smbus import SMBus
import os 
import time

# stm32 address
addr = 0x8

# opening the i2c bus
bus=SMBus(1)

# let the connection occur
time.sleep(1)

i = 0
while (i<200): 
	try:	
		# read byte from the specified address
		#order= bus.read_byte(addr)
		order = 2
		# update user on the i2c command sent
		# each value corresponds to a unique camera operation
		print ("The command order is: ", order)	

		if (order==0):
			# IDS camera operation
			os.system("./run.sh 1 15")
		elif (order==1):
			# Raspberry Pi camera operation
			os.system("./run.sh 2 15")
		elif (order==2):
			# both cameras deployed
			os.system("./run.sh 3 15")
		elif (order==9):
			# something went wrong, reboot
			#os.system("reboot")
			print ("i will reboot but actually not")
		i=i+1
		time.sleep(1)
	except:
		continue

# close the i2c bus to allow for other uses
bus.close()
