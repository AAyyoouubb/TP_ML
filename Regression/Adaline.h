#ifndef TP_ML_ADALINE_H
#define TP_ML_ADALINE_H

#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "../new/Math_Functions.h"
#include "../new/Distributions.h"
#include "../new/Optimizer.h"

#define loop(i, a, b) for(int i=a;i<b;i++)

int m;
long double **x; // Note: each column is a feature; x should contain 1 'bias' at last column;
long double *y;
int dim;    // Dimension of w.

long double predict(long double *w, long double *xx) {
    return dot_product(dim, w, xx);
}

long double costFunction(long double *w) {
    long  double l = 0;
    loop(i, 0, m)l += pow(y[i] - predict(w, x[i]), 2);
    return l / m;
}


long double *gradientCost(long double *w) {
    // No need to allocate the same array for multiple uses unless it changes it's size.
    static long double *g = (long double *) malloc(dim * sizeof(long double));
    long  double tmp;
    loop(j, 0, dim) g[j] = 0;
    loop(i, 0, m) {
        tmp = -2 * (y[i] - predict(w, x[i]));
        loop(j, 0, dim) g[j] += tmp * x[i][j];
    }
    loop(j, 0, dim) g[j] /= m;
    return g;
}

long double *fitData() {
    // Initialize W
    long double *w = (long double *) malloc(dim * sizeof(long double));
    generateUniformly(dim, w);

    // Execute Gradient Descent Algorithm using logistic loss;
    gradientDescent(dim, w, &gradientCost, &costFunction, 1200);
    // Print final loss, and optimal parameters;
    printf("\n Set of optimal Parameters: \t");
    loop(i, 0, dim) printf("%.20Lf  ", w[i]);
    printf("\n Final Loss: \t %.12Lf", costFunction(w));

    return w;
}

void read_csv(char *filename, int dimm, int mm) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) exit(-1);
    dim = dimm;
    m = mm;
    x = (long double **) malloc(m * sizeof(long double *));
    y = (long double *) malloc(m * sizeof(long double));
    char line[100];
    // Now Read each observation;
    double tmp;
    loop(i, 0, m) {
        // Allocate memo for observation;
        x[i] = (long double *) malloc(dim * sizeof(long double));
        // Reading the rest of the variables
        loop(j, 0, dim ) {
            // Read the comma here.
            fscanf(file, "%lf", &tmp);
            x[i][j] = tmp;
            fscanf(file, "%c", line);
        }
        // Now reading the label
        fscanf(file, "%lf", &tmp);
        y[i] = tmp;
        fscanf(file, "%c", line);

    }
    fclose(file);
}


#endif //TP_ML_ADALINE_H
