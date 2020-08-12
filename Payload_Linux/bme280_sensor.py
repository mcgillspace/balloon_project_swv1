import board
import busio
import adafruit_bme280
from time import gmtime, strftime

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c)

# change this to match the launch location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1013.25

# Units: 0 - 100%, hPa, m, celsius
humidity = format(bme280.humidity, ".1f")
pressure = format(bme280.pressure, ".1f")
altitude = format(bme280.altitude, ".1f")
temp_c = bme280.temperature
time_taken = strftime("%d %b %Y %H:%M:%S", gmtime())

# Saving sensor data to file found in raspberry pi
# Creating file if not already made; if made, write to it
data = time_taken + "\t" + f"{humidity}" + "\t" + f"{pressure}"+ "\t"+ f"{temp_c}"+"\t"+ f"{altitude}"+"\n"
file = open("/home/alarm/Desktop/adaSensor.txt", "a")
file.write(line)

# Closes file
file.close()         
