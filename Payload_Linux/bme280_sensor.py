import board
import busio
import adafruit_bme280
from time import gmtime, strftime

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c)

# change this to match the launch location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1013.25
MINUTES_BETWEEN_READS = 5

# OR create library object using our Bus SPI port
#spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
#bme_cs = digitalio.DigitalInOut(board.D10)
#bme280 = adafruit_bme280.Adafruit_BME280_SPI(spi, bme_cs)


# units: hPa, celsius
humidity = format(bme280.humidity, ".1f")
pressure = format(bme280.pressure, ".1f")
temp_c = bme280.temperature
time_taken = strftime("%d %b %Y %H:%M:%S", gmtime())

# saving sensor data to file found in raspberry pi
# creating file if not already made; if made, write to it
f = open("/home/alarm/Desktop/adaSensor.csv", "a+")
f.write(time_taken, temp_c, pressure, humidity) 
f.close()
        
              
