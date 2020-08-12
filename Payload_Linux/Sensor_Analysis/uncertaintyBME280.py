import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import spinmob as s

def linear(x,m,b):
    return m*x+b


humidity, pressure, temperature, altitude = np.loadtxt("adaSensor.txt", delimiter="\t", unpack=True,usecols=(1,2,3,4))

x=np.linspace(0,1000,1000)

f = s.data.fitter()
f.set_functions('m*x+b','m,b')
f.set_data(x,pressure)
f.fit()


#print (humidity)


#fig , [ax0,ax1,ax2,ax3]= plt.subplots(4,1, figsize=(20,18))

#ax0.set_ylabel("Humidity (%)")
#ax0.plot(humidity)

#ax1.set_ylabel("Pressure (hPa)")
#ax1.plot(pressure)

#ax2.set_ylabel("Temperature (C)")
#ax2.plot(temperature)

#ax3.set_ylabel("Altitude (m)")
#ax3.plot(altitude)

#plt.show()
