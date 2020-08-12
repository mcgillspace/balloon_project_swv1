import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

def linear(x,m,b):
    return m*x+b


humidity, pressure, temperature, altitude = np.loadtxt("adaSensor.txt", delimiter="\t", unpack=True,usecols=(1,2,3,4))

x=np.linspace(0,3000,3000)

colours = cm.rainbow(np.linspace(0, 1, 4))

fig , [ax0,ax1,ax2,ax3]= plt.subplots(4,1, figsize=(22,20))

ax0.set_ylabel("Humidity (%)",color=colours[0],fontsize=22)
ax0.plot(humidity)
ax0.xaxis.set_visible(False)

ax1.set_ylabel("Pressure (hPa)",color=colours[1],fontsize=22)
ax1.plot(pressure)
ax1.xaxis.set_visible(False)

ax2.set_ylabel("Temperature (C)",color=colours[2],fontsize=22)
ax2.plot(temperature)
ax2.xaxis.set_visible(False)

ax3.set_ylabel("Altitude (m)",color=colours[3],fontsize=22)
ax3.plot(altitude)

#plt.show()
