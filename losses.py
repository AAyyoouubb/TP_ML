import matplotlib.pyplot as plt


def plotLosses(L):
    plt.clf()
    plt.grid(True)
    plt.setp(plt.gca(), autoscale_on=True)
    plt.yscale('symlog')
    plt.xscale('symlog')
    plt.plot(L)
    plt.show()


def show():
    plt.show()
