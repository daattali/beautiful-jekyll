import numpy as np
import matplotlib.pyplot as plt


x = np.linspace(0,4,10001)
y = 0*x
y[np.logical_and(1<x,x<=2)] = x[np.logical_and(1<x,x<=2)]-1
y[np.logical_and(2<x,x<=3)] = 1 - np.sqrt(.3-.25) + np.sqrt(0.3 - (x[np.logical_and(2<x,x<=3)]-2.5)**2)
y[x>3] = 1

fig = plt.figure(figsize=(4, 3))
plt.plot(x,y, linewidth=2.0)
# plt.gca().set_aspect('equal', adjustable='box')
plt.xticks([0,1,2,3,4])
plt.tick_params(labelsize=14, left="off", labelleft="off")
plt.xlabel("time", fontsize=14)
plt.ylabel("distance", fontsize=14)
fig.set_tight_layout(True)
plt.savefig("calcQ.pdf")



fig = plt.figure(figsize=(4, 3))
# plt.plot(x[1:],np.diff(y), linewidth=2.0)
x = x[1:]
dydx = np.diff(y)
d1 = x<1
d2 = np.logical_and(1<x,x<2)
d3 = np.logical_and(2<x,x<3)
d4 = x>3
plt.plot(x[d1],dydx[d1], 'b', linewidth=2.0)
plt.plot(x[d2],dydx[d2], 'b', linewidth=2.0)
plt.plot(x[d3],dydx[d3], 'b', linewidth=2.0)
plt.plot(x[d4],dydx[d4], 'b', linewidth=2.0)

plt.xticks([0,1,2,3,4])
plt.yticks([0])
plt.tick_params(labelsize=14)
plt.xlabel("time", fontsize=14)
plt.ylabel("velocity", fontsize=14)
fig.set_tight_layout(True)
plt.savefig("calcA.pdf")
