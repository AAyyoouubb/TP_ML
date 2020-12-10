#ifndef TP_ML_MATH_FUNCTIONS_H
#define TP_ML_MATH_FUNCTIONS_H

#include <math.h>

#define loop(i, a, b) for(int i=a;i<b;i++)

long double norm(int dim, long double *vector) {
    long double sum = 0;
    loop(i, 0, dim) sum += abs(vector[i]);
    return sum;
}

long double dot_product(int dim, long double *w, long double *x) {
    long double sum = 0;
    loop(i, 0, dim)sum += w[i] * x[i];
    return sum;
}

long double *scalar_vector(int dim, long double scalar, long double *vector) {
    static long double *res = (long double *) malloc(dim * sizeof(long double));
    loop(i, 0, dim) res[i] = scalar * vector[i];
    return res;
}

long double *diff_vector(int dim, long double *vec1, long double *vec2) {
    static long  double *res = (long double *) malloc(dim * sizeof(long double));
    loop(i, 0, dim) res[i] = vec1[i] - vec2[i];
    return res;
}

#endif //TP_ML_MATH_FUNCTIONS_H
