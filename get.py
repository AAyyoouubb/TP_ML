import numpy as np
import matplotlib.pyplot as plt

n = 10

x = np.arange(-10, 10)
y = x ** 2

fig = plt.figure()
ax = fig.add_subplot(111)
# ax.plot(x,y)
plt.xlim(0, 500)
plt.ylim(0, 500)
coords = []

scat = ax.scatter([0, 1, 2], [3, 4, 5], cmap=plt.cm.spring, c=[0, 2, 1])


def addPoint(scat, new_point, c='red'):
    old_off = scat.get_offsets()
    new_off = np.concatenate([old_off, np.array(new_point, ndmin=2)])
    old_c = scat.get_facecolors()
    # new_c = np.concatenate([old_c, np.array(plt.colors.to_rgba(c), ndmin=2)])

    scat.set_offsets(new_off)
    # scat.set_facecolors(new_c)

    scat.axes.figure.canvas.draw_idle()


def onclick(event):
    global ix, iy, n
    ix, iy = event.xdata, event.ydata
    print('x = %d, y = %d' % (
        ix, iy))
    global coords
    coords.append([ix, iy])
    addPoint(scat, [ix, iy], 'c')

    if len(coords) == n:
        fig.canvas.mpl_disconnect(cid)
    return coords


cid = fig.canvas.mpl_connect('button_press_event', onclick)
plt.show()
