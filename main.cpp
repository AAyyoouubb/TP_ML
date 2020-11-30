
#include "TP1/C/Perceptron.h"
#include "TP1/C/Pocket.h"
#include "TP1/C/DeltaRule.h"

#include <cstdio>
#include <Python.h>
#include <bits/stdc++.h>

using namespace std;

void run(const char *s) {
    PyRun_SimpleString(s);
}

vector<vector<double>> getPoints(char *name, char *func) {
    PyObject *pfunc, *lib, *res, *tmp;

    run("import sys");
    // TODO: put the path to your current working directory
    run("sys.path.append('/home/ayoub/CLionProjects/TP_ML/')");

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

void plotLoss(const vector<double> &loss, const vector<double> &loss2, const vector<double> &loss3, char *name, char *func) {
    PyObject *pfunc, *lib, *res, *tmp, *args, *args2, *args3, *tuple;

    PyRun_SimpleString("import sys");
    // TODO: put the path to your current working directory
    PyRun_SimpleString("sys.path.append('/home/ayoub/CLionProjects/TP_ML/')");

    PyObject *pname = PyUnicode_FromString(name);
    lib = PyImport_Import(pname);
    pfunc = PyObject_GetAttrString(lib, func);
    tuple = PyTuple_New(3);
    //////////////////
    args = PyList_New(loss.size());
    loop(i, 0, loss.size()) {
        tmp = PyFloat_FromDouble(loss[i]);
        PyList_SetItem(args, i, tmp);
    }
    PyTuple_SetItem(tuple, 0, args);

    ////////////////
    args2 = PyList_New(loss2.size());
    loop(i, 0, loss2.size()) {
        tmp = PyFloat_FromDouble(loss2[i]);
        PyList_SetItem(args2, i, tmp);
    }
    PyTuple_SetItem(tuple, 1, args2);

    ///////////////
    args3 = PyList_New(loss3.size());
    loop(i, 0, loss3.size()) {
        tmp = PyFloat_FromDouble(loss3[i]);
        PyList_SetItem(args3, i, tmp);
    }
    PyTuple_SetItem(tuple, 2, args3);

    ////////////////////
    PyObject_CallObject(pfunc, tuple);

    Py_DECREF(pname);
    Py_DECREF(tuple);
    Py_DECREF(args);
    Py_DECREF(lib);
    Py_DECREF(pfunc);
}

// Command: g++ main.cpp -o main -lpython3.8 -I /usr/include/python3.8

int main(int argc, char *argv[]) {

    Py_Initialize();

    //  Create the X matrix and y and model to use.
    //  TODO: check this to know how to add points: https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.ginput.html
    vector<vector<double>> pts = getPoints("getPoints", "points");
    int nn = pts.size(), mm = pts[0].size() - 1;
    double **x = (double **) malloc(sizeof(double) * nn);
    int *y = (int *) malloc(sizeof(int) * nn);
    for (int i = 0; i < nn; i++) {
        x[i] = (double *) malloc(sizeof(double) * mm);
        y[i] = pts[i][mm];
        for (int j = 0; j < mm; j++) x[i][j] = pts[i][j];
    }

    // Optimize and get the loss's evolution
    vector<double> percep = per_fit(x, y, nn, mm);
    vector<double> pocket = poc_fit(x, y, nn, mm, 100);
    vector<double> delta = dlt_fit(x, y, nn, mm, 100);

    // Plotting the error.
    // Beware the order of the algorithms losses!
    plotLoss(percep, pocket, delta, "losses", "plotLosses");

    Py_Finalize();

    return 0;
}
