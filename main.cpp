
#include "TP1/Cpp/Perceptron.h"

#include <cstdio>
#include <Python.h>

void run(const char *s) {
    PyRun_SimpleString(s);
}

vector<vector<double>> getPoints(char *name, char *func) {
    PyObject *pfunc, *lib, *res, *tmp;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/ayoub/CLionProjects/TP_ML/')");

    PyObject *pname = PyUnicode_FromString(name);
    lib = PyImport_Import(pname);
    Py_DECREF(pname);
    pfunc = PyObject_GetAttrString(lib, func);
    res = PyObject_CallObject(pfunc, nullptr);

    vector<vector<double>> pts;
    loop(i, 0, PyList_Size(res)) {
        vector<double> vect;
        loop(j, 0, PyList_Size(PyList_GetItem(res, i))) {
            tmp = PyList_GetItem(PyList_GetItem(res, i), j);
            vect.push_back(PyFloat_AsDouble(tmp));
            Py_DECREF(tmp);
        }
        pts.push_back(vect);
    }

    Py_DECREF(lib);
    Py_DECREF(pfunc);
    return pts;
}

void plotLoss(const vector<double> &loss, char *name, char *func) {
    PyObject *pfunc, *lib, *res, *tmp, *args, *tuple;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/ayoub/CLionProjects/TP_ML/')");

    PyObject *pname = PyUnicode_FromString(name);
    lib = PyImport_Import(pname);
    Py_DECREF(pname);
    pfunc = PyObject_GetAttrString(lib, func);
    args = PyList_New(loss.size());
    loop(i, 0, loss.size()) {
        tmp = PyFloat_FromDouble(loss[i]);
        PyList_SetItem(args, i, tmp);
    }
    tuple = PyTuple_New(1);
    PyTuple_SetItem(tuple, 0, args);
    PyObject_CallObject(pfunc, tuple);

    Py_DECREF(tuple);
    Py_DECREF(args);
    Py_DECREF(lib);
    Py_DECREF(pfunc);
}

// Command: g++ main.cpp -o main -lpython3.8 -I /usr/include/python3.8
int main(int argc, char *argv[]) {
    PyObject *name, *n, *lib, *printer, *args, *res;

    Py_Initialize();
    if (!(name = PyUnicode_FromString("lib")))
        return -1;

//    vector<vector<double>> pts = getPoints("lib", "p");
    vector<double> pts{1,2,3,4,5,6,7,8,9};
    plotLoss(pts, "losses", "plotLosses");

    Py_Finalize();

    return 0;
}
