#ifndef TP_ML_DELTARULE_H
#define TP_ML_DELTARULE_H

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
    double l = 0;
    loop(i, 0, n) l += pow(y[i] - predict(x[i]), 2);
    return l / n;
}

void updateW(const double *x, double e) {
    w[m] += e;
    loop(i, 0, m) w[i] += x[i] * e;
}

std::vector<double> fit(double **x, int *y, int nn, int mm, int iter) {
    std::vector<double> losses;
    n = nn;
    m = mm;
    w = (double *) (malloc(sizeof(double) * (m + 1)));
    randomW();
    losses.push_back(loss(x, y));
    double e;
    loop(t, 0, iter) {
        loop(i, 0, n) {
            e = y[i] - predict(x[i]);
            if (e != 0) updateW(x[i], 2 * e / n);
        }
        losses.push_back(loss(x, y));
    }
    return losses;
}

void randomW() {
    loop(i, 0, m + 1) w[i] = rand() % 10;
}


#endif //TP_ML_DELTARULE_H
