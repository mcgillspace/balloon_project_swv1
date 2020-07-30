import numpy as np
from scipy.integrate import odeint

"""
The ODE we want to solve has the following form:
	g*V*(p_atm-p_He)-(m_b+m_p)*g+(1/2)*p_atm*y'^2*c_d*S = (m_He+m_b+m_p)*y''
To solve this second order ODE, we can go a change of variable z=y';
	g*V*(p_atm-p_He)-(m_b+m_p)*g+(1/2)*p_atm*z^2*c_d*S = (m_He+m_b+m_p)*z'
"""

#Balloon specs

#Radius of the balloon:
r =1
#Mass of ballon:
m_b=1
#Mass of payload:
m_p=1
#Mass of Helium:
m_He=1


#Physical parameter:

#Gravity of the Earth
g = 9.81
#Volume occupied by the balloon
V = (4/3*np.pi*r**3)
#density of helium
p_He=0.178     #kg/m^3
#density of air:
p_atm=1.2 #kg/m^3


def dU_dx(U,x):
	"""
	Function that takes a derivative of the vector U=[y,z]. Therefore, it should return [y',z']
	"""
	return [U[1], (g*V*(p_atm-p_He)-(m_b+m_p)*g+(1/2)*p_atm*z**2*c_d*S)/(m_He+m_b+m_p)]

#Initial condition
U0=[0,0]
ts = [0,10,200]
Us = odeint(dU_dx,U0,ts)
ys = Us[;,0]
