//
// Created by ayoub on 20. 11. 6..
//

#ifndef TP_ML_PERCEPTRON_H
#define TP_ML_PERCEPTRON_H

#include <malloc.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

int n, m;
double *w;

void randomW();

double predict(const double *x) {
    double s = w[m];
    loop(i, 0, m) s += w[i] * x[i];
    return s;
}

double loss(double **x, const int *y) {
    int l = 0;
    loop(i, 0, n) if (predict(x[i]) * y[i] < 0) l++;
    return (double) l / n;
}

void updateW(const double *x, int y) {
    w[m] += y;
    loop(i, 0, m) w[i] += x[i] * y;
}

std::vector<double> fit(double **x, int *y, int nn, int mm) {
    std::vector<double> losses;
    n = nn;
    m = mm;
    w = (double *) (malloc(sizeof(double) * (m + 1)));
    randomW();
    double los = loss(x, y);
    int iter = 0;
    while (los != 0) {
        loop(i, 0, n) if (predict(x[i]) * y[i] < 0) updateW(x[i], y[i]);
        los = loss(x, y);
        losses.push_back(los);
    }
    return losses;
}

void randomW() {
    loop(i, 0, m + 1) w[i] = rand() % 10;
}

#endif //TP_ML_PERCEPTRON_H
