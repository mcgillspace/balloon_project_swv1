import board
import busio
import time
import adafruit_bme280
from time import gmtime, strftime

NUMTRIALS = 3000
TIME_BETWEEN_TAKES = 10

def takeData(bme280):
	# Units: 0 - 100%, hPa, m, celsius
	humidity = format(bme280.humidity, ".2f")
	pressure = format(bme280.pressure, ".2f")
	altitude = format(bme280.altitude, ".2f")
	temp_c = format(bme280.temperature,".2f")
	time_taken = strftime("%d %b %Y %H:%M:%S", gmtime())
	data = time_taken + "\t" + f"{humidity}" + "\t" + f"{pressure}"+ "\t"+ f"{temp_c}"+"\t"+ f"{altitude}"+"\n"

	return data	

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)

bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, address = 0x77)

# change this to match the launch location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1013.25


#Creates a file called adaSensor if it does not already exist 
#and appends data to it 
file = open("/home/alarm/Desktop/balloon_project_swv1/Payload_Linux/Sensor_Analysis/adaSensor_delay.txt", "a")

for i in range(NUMTRIALS):
	data = takeData(bme280)
	file.write(data)
	time.sleep(TIME_BETWEEN_TAKES)

file.close()
         
