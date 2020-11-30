//
// Created by ayoub on 20. 11. 20..
//

#ifndef TP_ML_DISTRIBUTIONS_H
#define TP_ML_DISTRIBUTIONS_H

#include <stdlib.h>
#include <math.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

void generateUniformly(int dim,double *w) {
    loop(i, 0, dim) w[i] = rand() / (double) RAND_MAX;
}

double sampleNormal() {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}

void generateUsingStandardNormal(int dim,double *w) {
    loop(i, 0, dim) w[i] = sampleNormal();
}

void generateUsingBernouilli(int dim,double *w) {
    loop(i, 0, dim) w[i] = (rand() / (double) RAND_MAX < .4) ? 1 : 0;
}

#endif //TP_ML_DISTRIBUTIONS_H
