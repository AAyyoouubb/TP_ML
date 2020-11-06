import matplotlib.pyplot as plt


def plotLosses(L):
    plt.clf()
    plt.setp(plt.gca(), autoscale_on=False)
    plt.plot(L)


def show():
    plt.show()
