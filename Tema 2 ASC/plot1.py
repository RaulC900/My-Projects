import matplotlib.pyplot as plt
import numpy as np
import sys

x1 = [1, 3, 5, 7]
y1 = [float(sys.argv[1]), float(sys.argv[2]), float(sys.argv[3]), float(sys.argv[4])]

#limite pentru time (am observat ca timpii <= 60)
plt.xlim(0, 60)
plt.xlim(0, 9)

plt.ylabel('TIME')
tick_label = ['tema2_blas', 'tema2_neopt', 'tema2_opt_f', 'tema2_opt_m']

plt.bar(x1, y1, tick_label = tick_label, 
        width = 1.5, color = ['red', 'green', 'blue', 'yellow'])

# ultima este numele graficului
plt.title(sys.argv[5]) 

plt.show()