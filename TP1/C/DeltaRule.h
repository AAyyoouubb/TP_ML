#ifndef TP_ML_DELTARULE_H
#define TP_ML_DELTARULE_H

#include <malloc.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

int dlt_n, dlt_m;
double *dlt_w;

void dlt_randomW();


double dlt_predict(const double *x) {
    double s = dlt_w[dlt_m];
    loop(i, 0, dlt_m) s += dlt_w[i] * x[i];
    return s;
}

double dlt_loss(double **x, const int *y) {
    double l = 0;
    loop(i, 0, dlt_n) l += pow(y[i] - dlt_predict(x[i]), 2);
    return l / dlt_n;
}

void dlt_updateW(const double *x, double e) {
    dlt_w[dlt_m] += e;
    loop(i, 0, dlt_m) dlt_w[i] += x[i] * e;
}

std::vector<double> dlt_fit(double **x, int *y, int nn, int mm, int iter) {
    std::vector<double> losses;
    dlt_n = nn;
    dlt_m = mm;
    dlt_w = (double *) (malloc(sizeof(double) * (dlt_m + 1)));
    dlt_randomW();
    losses.push_back(dlt_loss(x, y));
    double e;
    loop(t, 0, iter) {
        loop(i, 0, dlt_n) {
            e = y[i] - dlt_predict(x[i]);
            if (e != 0) dlt_updateW(x[i], 2 * e / dlt_n);
        }
        losses.push_back(dlt_loss(x, y));
    }
    return losses;
}

void dlt_randomW() {
    loop(i, 0, dlt_m + 1) dlt_w[i] = rand() % 10;
}


#endif //TP_ML_DELTARULE_H
