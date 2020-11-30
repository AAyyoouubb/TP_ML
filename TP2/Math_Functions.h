#ifndef TP_ML_MATH_FUNCTIONS_H
#define TP_ML_MATH_FUNCTIONS_H

#include <math.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

double norm(int dim, double *vector) {
    double sum = 0;
    loop(i, 0, dim) sum += pow(vector[i], 2);
    return sum;
}

double dot_product(int dim, double *w, double *x) {
    double sum = 0;
    loop(i, 0, dim)sum += w[i] * x[i];
    return sum;
}

double *scalar_vector(int dim, double scalar, double *vector) {
    static double *res = (double *) malloc(dim * sizeof(double));
    loop(i, 0, dim) res[i] = scalar * vector[i];
    return res;
}

double *diff_vector(int dim, double *vec1, double *vec2) {
    static double *res = (double *) malloc(dim * sizeof(double));
    loop(i, 0, dim) res[i] = vec1[i] - vec2[i];
    return res;
}

#endif //TP_ML_MATH_FUNCTIONS_H
