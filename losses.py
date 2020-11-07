import matplotlib.pyplot as plt


def plotLosses(l1, l2, l3):
    titles = ["Perceptron", 'Pocket', 'Adaline']
    plt.clf()
    plt.grid(True)
    # plt.setp(plt.gca(), autoscale_on=True)
    plt.yscale('symlog')
    plt.xscale('log')
    plt.plot(l1)
    plt.plot(l2)
    plt.plot(l3)
    plt.legend(titles)
    plt.show()
