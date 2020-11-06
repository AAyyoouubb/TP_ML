#ifndef TP_ML_POCKET_H
#define TP_ML_POCKET_H


#include <malloc.h>
#include <stdlib.h>
#include <bits/stdc++.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

static int n, m;
static double *w;


void randomW();

double predict(const double *ws, const double *x) {
    double s = ws[m];
    loop(i, 0, m) s += ws[i] * x[i];
    return s;
}

double loss(double *ws, double **x, const int *y) {
    int l = 0;
    loop(i, 0, n) if (predict(ws, x[i]) * y[i] < 0) l++;
    return (double) l / n;
}

void updateWs(double *ws, const double *x, int y) {
    ws[m] += y;
    loop(i, 0, m) ws[i] +=  x[i] * y;
}

void updateW(const double *ws) {
    loop(i, 0, m + 1) w[i] = ws[i];
}

static std::vector<double> fit(double **x, int *y, int nn, int mm, int iter) {
    std::vector<double> losses;
    n = nn;
    m = mm;
    w = (double *) (malloc(sizeof(double) * (m + 1)));
    double *ws = (double *) (malloc(sizeof(double) * (m + 1)));
    randomW();
    loop(i, 0, m + 1) ws[i] = w[i];
    double l = loss(w, x, y);
    losses.push_back(l);
    loop(t, 0, iter) {
        loop(i, 0, n)if (predict(ws, x[i]) * y[i] < 0) updateWs(ws, x[i], y[i]);
        if (l > loss(ws, x, y)) updateW(ws);
        l = loss(w, x, y);
        losses.push_back(l);
    }
    free(ws);
    return losses;
}

void randomW() {
    loop(i, 0, m + 1) w[i] = rand() % 10;
}

#endif //TP_ML_POCKET_H
