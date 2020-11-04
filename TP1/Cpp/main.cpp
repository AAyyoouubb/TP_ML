
#include "Perceptron.h"

#include <cstdio>
#include <Python.h>

void run(const char *s) {
    PyRun_SimpleString(s);
}

int main() {
    PyObject *pInt;

    Py_Initialize();

    run("import matplotlib.pylot as plt");
    run("print('Hello World from Embedded Python!!!')");

    Py_Finalize();

    return 0;
}
