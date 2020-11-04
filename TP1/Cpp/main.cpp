
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

    run("import matplotlib.pyplot as plt");
    run("print('Hello World from Embedded Python!!!')");

    Py_Finalize();

    return 0;
}
