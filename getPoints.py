import matplotlib.pyplot as plt


def points():
    plt.clf()
    plt.setp(plt.gca(), autoscale_on=False)
    plt.title('Class 1')
    p = plt.ginput(-1, timeout=0)
    plt.title('Class -1')
    plt.plot([t[0] for t in p],[t[1] for t in p],'go')
    p2 = plt.ginput(-1, timeout=0)
    res = [list(t) + [1] for t in p]
    res += [list(t) + [-1] for t in p2]
    return res