
#include "TP1/Cpp/Perceptron.h"

#include <cstdio>
#include <Python.h>

void run(const char *s) {
    PyRun_SimpleString(s);
}

// Command: g++ main.cpp -o main -lpython3.8 -I /usr/include/python3.8
int main(int argc, char *argv[]) {
    PyObject *name, *n, *lib, *printer, *args;

    Py_Initialize();
    if (!(name = PyUnicode_FromString("lib")))
        return -1;


    n = PyLong_FromLong(10l);
    args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, n);

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/ayoub/CLionProjects/TP_ML/')");

    lib = PyImport_Import(name);
    Py_DECREF(name);
    printer = PyObject_GetAttrString(lib, "p");

    PyObject_CallObject(printer, args);


    Py_Finalize();

    return 0;
}
