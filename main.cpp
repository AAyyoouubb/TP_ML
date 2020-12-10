
#include "Classification/Perceptron.h"
#include "Classification/Pocket.h"
#include "Regression/Adaline.h"
#include "new/DataGenerator.h"

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

void
plotLoss(const vector<double> &loss, const vector<double> &loss2, const vector<double> &loss3, char *name, char *func) {
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

int label(int d, double *x) {
    // w=[10.55,-1.00153,394.004059]: last one is the bias.
    double w[] = {171.09095, -.109901, 0.10012};
    double sum = 0;
    loop(i, 0, d) sum += w[i] * x[i];
    return sum > 0 ? 1 : -1;
}

int main(int argc, char *argv[]) {

//    Py_Initialize();

    // Fix H & epsilon & delta & target function to predict;
    double eps = .05;
    double delta = .01;
    int d = 2;
    long sample_complexity = minimumSampleComplexity(d + 1, eps, delta);
    printf("Sample Complexity: %li\n", sample_complexity);
    double **x = generateInputs(sample_complexity, d,1000);
    int *y = labelInputs(sample_complexity, d + 1, x, &label);

    per_fit(x, y, sample_complexity, d);

//    Py_Finalize();

    return 0;
}
