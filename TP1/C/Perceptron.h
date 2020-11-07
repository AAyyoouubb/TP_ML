#ifndef TP_ML_PERCEPTRON_H
#define TP_ML_PERCEPTRON_H

#include <malloc.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

int per_n, per_m;
double *per_w;

void per_randomW();

double per_predict(const double *x) {
    double s = per_w[per_m];
    loop(i, 0, per_m) s += per_w[i] * x[i];
    return s;
}

double per_loss(double **x, const int *y) {
    int l = 0;
    loop(i, 0, per_n) if (per_predict(x[i]) * y[i] < 0) l++;
    return (double) l / per_n;
}

void per_updateW(const double *x, int y) {
    per_w[per_m] += y;
    loop(i, 0, per_m) per_w[i] += x[i] * y;
}

static std::vector<double> per_fit(double **x, int *y, int nn, int mm) {
    std::vector<double> losses;
    per_n = nn;
    per_m = mm;
    per_w = (double *) (malloc(sizeof(double) * (per_m + 1)));
    per_randomW();
    double los = per_loss(x, y);
    int iter = 0;
    while (los != 0 and iter < 10e3) {
        iter++;
        loop(i, 0, per_n) if (per_predict(x[i]) * y[i] < 0) per_updateW(x[i], y[i]);
        los = per_loss(x, y);
        losses.push_back(los);
    }
    return losses;
}

void per_randomW() {
    loop(i, 0, per_m + 1) per_w[i] = rand() % 10;
}

#endif //TP_ML_PERCEPTRON_H
