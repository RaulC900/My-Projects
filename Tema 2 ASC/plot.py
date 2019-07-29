import matplotlib.pyplot as plt
import numpy as np
import sys

# primele 3 valori de la stdin sunt timpii obtinuti
x = [float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3])]
y = [400, 1000, 1600]

plt.plot(x, y, color='black', linewidth = 1, 
			marker='o', markerfacecolor='black', markersize=8)

#limite pentru time (am observat ca timpii <= 60)
plt.xlim(0.0, 60)
plt.xticks(np.arange(0.0, 65, 5.0)) #step

plt.xlabel('TIME') 
plt.ylabel('N')

# ultima este numele graficului
plt.title(sys.argv[4]) 

plt.show()