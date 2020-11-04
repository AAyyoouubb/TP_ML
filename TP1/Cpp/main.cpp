
#include "Perceptron.h"

#include <cstdio>
#include <Python.h>

void run(const char *s) {
    PyRun_SimpleString(s);
}

// Command: g++ main.cpp -o main -lpython3.8 -I /usr/include/python3.8

int main() {
    PyObject *pInt;

    Py_Initialize();

    run("import matplotlib.pyplot as plt\nimport numpy as np");
    run("print('Helloff World from Embedded Python!!!')");

    run("x = np.arange(0, 1, 0.05)\n"
        "y = np.power(x, 2)\n"
        "\n"
        "fig = plt.figure()\n"
        "ax = fig.gca()\n"
        "ax.set_xticks(np.arange(0, 1, 0.1))\n"
        "ax.set_yticks(np.arange(0, 1., 0.1))\n"
        "plt.scatter(x, y)\n"
        "plt.grid()\n"
        "plt.show()");
    Py_Finalize();

    return 0;
}
