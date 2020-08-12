import time 
import board
import busio
import adafruit_bme280

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

while: True
        # always using metric units
        humidity = format(bme280.humidity, ".1f")
        pressure = format(bme280.pressure, ".1f")
        temp_c = bme280.temperature
       
        # saving sensor data to file found in raspberry pi
        with open("file_location/adaSensor.csv", 'w') as file:
                file.write(temp_c, pressure, humidity) 
        
              
