import matplotlib.pyplot as p 
import numpy as np


File_data = np.loadtxt("output.txt", dtype=float)

time = File_data.shape[0]
spaceInd = File_data.shape[1]
x=0
timearray = []
for t in range(time):
    timearray.append(t)

p.xlabel("Time")
p.ylabel("Temprature")

for i in range (spaceInd):
    column = File_data[:, x]
    p.plot(timearray,column)
    x+=1
p.show()
