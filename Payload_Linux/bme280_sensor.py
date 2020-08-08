import time 
import board
import busio
import adafruit_bme280
from ISStreamer.Streamer import Streamer

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c)
 
# --------- User Settings ---------
SENSOR_LOCATION_NAME = "ANSERIS-I"
BUCKET_NAME = ":partly_sunny: Room Temperature"
BUCKET_KEY = "temp1"
ACCESS_KEY = "YOUR ACCESS KEY HERE"
# change this to match the launch location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1013.25
MINUTES_BETWEEN_READS = 5
METRIC_UNITS = True
# ---------------------------------

# OR create library object using our Bus SPI port
#spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
#bme_cs = digitalio.DigitalInOut(board.D10)
#bme280 = adafruit_bme280.Adafruit_BME280_SPI(spi, bme_cs)

streamer = Streamer(bucket_name=BUCKET_NAME, bucket_key=BUCKET_KEY, access_key=ACCESS_KEY)
while True:
        humidity = format(bme280.humidity, ".1f")
        pressure = format(bme280.pressure, ".1f")
        temp_c = bme280.temperature
        if METRIC_UNITS:
                streamer.log(SENSOR_LOCATION_NAME + "Temperature(C)", temp_c)
        else:
                temp_f = format(temp_c * 9.0 / 5.0 + 32.0, ".1f")
                streamer.log(SENSOR_LOCATION_NAME + " Temperature(F)", temp_f)
        streamer.log(SENSOR_LOCATION_NAME + "Humidity(%)", humidity)
        streamer.log(SENSOR_LOCATION_NAME + "Pressure(hPA)", pressure)
        streamer.flush()
        time.sleep(60*MINUTES_BETWEEN_READS)
