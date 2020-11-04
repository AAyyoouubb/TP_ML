import matplotlib.pyplot as plt
import math
def plotLesses(L):
	plt.plot(L)
	plt.show()


x=[i for i in range(20)]
y=list(map(math.sqrt,x))
plotLesses(y)