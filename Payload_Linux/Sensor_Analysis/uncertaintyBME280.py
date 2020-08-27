import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

def linear(x,m,b):
    return m*x+b

FONTISZE=15 
MARKERSIZE = 2

humidity, pressure, temperature, altitude = np.loadtxt("adaSensor.txt", delimiter="\t", unpack=True,usecols=(1,2,3,4))

x=np.linspace(0,3000,3000)

colours = cm.rainbow(np.linspace(0, 1, 4))

fig , [ax0,ax1,ax2,ax3]= plt.subplots(4,1, figsize=(22,20))

<<<<<<< HEAD
ax0.set_ylabel("Humidity (%)",fontsize=FONTISZE)
ax0.plot(humidity,'.',color=colours[0],markersize=MARKERSIZE)
=======
ax0.set_ylabel("Humidity (%)",color=colours[0],fontsize=22)
ax0.plot(humidity,'.')
>>>>>>> cabc3d332df3ccbc31c1b96fdb4baa6f0c079bd0
ax0.xaxis.set_visible(False)
ax0.axhline(np.average(humidity))

<<<<<<< HEAD
ax1.set_ylabel("Pressure (hPa)",fontsize=FONTISZE)
ax1.plot(pressure,'.',color=colours[1],markersize=MARKERSIZE)
=======
ax1.set_ylabel("Pressure (hPa)",color=colours[1],fontsize=22)
ax1.plot(pressure,'.')
>>>>>>> cabc3d332df3ccbc31c1b96fdb4baa6f0c079bd0
ax1.xaxis.set_visible(False)
ax1.axhline(np.average(pressure))

<<<<<<< HEAD
ax2.set_ylabel("Temperature (C)",fontsize=FONTISZE)
ax2.plot(temperature,'.',color=colours[2],markersize=MARKERSIZE)
ax2.axhline(np.average(temperature))
ax2.xaxis.set_visible(False)

ax3.set_ylabel("Altitude (m)",fontsize=FONTISZE)
ax3.axhline(np.average(altitude))
ax3.plot(altitude,'.',color=colours[3],markersize=MARKERSIZE)

plt.show()


fig , [ax0,ax1,ax2,ax3]= plt.subplots(4,1, figsize=(22,20))

ax0.set_ylabel("Humidity (%)",fontsize=FONTISZE)
ax0.plot(humidity-np.average(humidity),'.',color=colours[0],markersize=MARKERSIZE)
ax0.xaxis.set_visible(False)

ax1.set_ylabel("Pressure (hPa)",fontsize=FONTISZE)
ax1.plot(pressure-np.average(pressure),'.',color=colours[1],markersize=MARKERSIZE)
ax1.xaxis.set_visible(False)

ax2.set_ylabel("Temperature (C)",fontsize=FONTISZE)
ax2.plot(temperature-np.average(temperature),'.',color=colours[2],markersize=MARKERSIZE)
ax2.xaxis.set_visible(False)

ax3.set_ylabel("Altitude (m)",fontsize=FONTISZE)
ax3.plot(altitude-np.average(altitude),'.',color=colours[3],markersize=MARKERSIZE)

print (f"Humidity recorded is {np.round(np.average(humidity),3)} with error {np.round(np.std(humidity)/np.sqrt(3000),3)}")
print (f"Pressure recorded is {np.round(np.average(pressure),3)} with error {np.round(np.std(pressure)/np.sqrt(3000),3)}")
print (f"Temperature recorded is {np.round(np.average(temperature),3)} with error {np.round(np.std(temperature)/np.sqrt(3000),3)}")
print (f"Altitude recorded is {np.round(np.average(altitude),3)} with error {np.round(np.std(altitude)/np.sqrt(3000),3)}")



plt.show()


=======
ax2.set_ylabel("Temperature (C)",color=colours[2],fontsize=22)
ax2.plot(temperature,'.')
ax2.xaxis.set_visible(False)

ax3.set_ylabel("Altitude (m)",color=colours[3],fontsize=22)
ax3.plot(altitude,'.')
>>>>>>> cabc3d332df3ccbc31c1b96fdb4baa6f0c079bd0

