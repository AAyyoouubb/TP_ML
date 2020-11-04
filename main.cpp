
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
    for (auto &t: loss) {
        tmp = PyFloat_FromDouble(t);
        PyList_Append(args, tmp);
        Py_DecRef(tmp);
    }
    tuple = PyTuple_New(1);
    PyTuple_SetItem(tuple, 0, args);
    PyObject_CallObject(pfunc, tuple);

    Py_DECREF(lib);
    Py_DECREF(pfunc);
}

// Command: g++ main.cpp -o main -lpython3.8 -I /usr/include/python3.8
int main(int argc, char *argv[]) {
    PyObject *name, *n, *lib, *printer, *args, *res;

    Py_Initialize();
    if (!(name = PyUnicode_FromString("lib")))
        return -1;

    vector<vector<double>> pts = getPoints("lib", "p");
    plotLoss(pts[0], "lib", "pp");
//
//    n = PyLong_FromLong(10l);
//    args = PyTuple_New(1);
//    PyTuple_SetItem(args, 0, n);
//
//
//    lib = PyImport_Import(name);
//    Py_DECREF(name);
//    printer = PyObject_GetAttrString(lib, "p");
//
//    res = PyObject_CallObject(printer, args);
//    cout << "hhhhh   " << PyLong_AsLong(PyList_GetItem(res, 1)) << endl;


    Py_Finalize();

    return 0;
}
