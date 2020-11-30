#ifndef TP_ML_MULTIREGRESSION_H
#define TP_ML_MULTIREGRESSION_H

#include <stdio.h>
#include "../Math_Functions.h"
#include "../Distributions.h"
#include "../Optimizer.h"

#define loop(i, a, b) for(int i=a;i<b;i++)


int m;
double **x; // TODO: each column is a feature; x should contain 1 at first column;
double *y;
int dim;    // Dimension of w.

double loss(double *w) {
    double l = 0;
    loop(i, 0, m) l += pow(dot_product(dim, w, x[i]) - y[i], 2);
    return l / m;
}

double *gradientLoss(double *w) {
    // No need to allocate the same array for multiple uses unless it changes its size.
    static double *g = (double *) malloc(dim * sizeof(double));
    loop(i, 0, dim) g[i] = 0;
    double tmp;
    loop(i, 0, m) {
        tmp = 2 * (dot_product(dim, w, x[i]) - y[i]);
        loop(j, 0, dim)g[j] += tmp * x[i][j];
    }
    loop(i, 0, dim) g[i] /= m;
    return g;
}

double *fitData() {
    // Initialize W
    double *w = (double *) calloc(dim, sizeof(double));
    // TODO: Initialize from uniform distribution, normal distribution, bernoulli with parameter .4;
     generateUniformly(dim,w);
//     generateUsingStandardNormal(dim,w);
//    generateUsingBernouilli(dim, w);

    // Execute Gradient Descent Algorithm using logistic loss;
    gradientDescent(dim, w, &gradientLoss, &loss, 10.e-5);
    // Print final loss, and optimal parameters;
    printf("\n Set of optimal Parameters: \t");
    loop(i, 0, dim) printf("%lf  ", w[i]);
    printf("\n Final Loss: \t %lf", loss(w));

    return w;
}

void readcsv() {
    FILE *file = fopen("pop.csv", "r");
    if (file == NULL) exit(-1);
    // The file contains 401 rows including the header; and 4 variables, the first one is the label;
    dim = 5;
    m = 53;
    x = (double **) malloc(m * sizeof(double *));
    y = (double *) malloc(m * sizeof(double));
    char line[1024];
    // Read the header:
    fgets(line, sizeof(line), file);
    // Now Read each observation;
    int i = 0;
    double tmp;
    while (!feof(file)) {
        // Allocate memo for observation;
        x[i] = (double *) malloc(dim * sizeof(double));
        // Reading the rest of the variables
        x[i][0] = 1;
        fscanf(file, "%lf", &tmp);
        y[i] = tmp;
        loop(j, 1, dim) {
            fscanf(file, "%c", line);
            fscanf(file, "%lf", &tmp);
            x[i][j] = tmp;

            // Read the comma here.
        }
        i++;
    }


    fclose(file);
}


#endif //TP_ML_MULTIREGRESSION_H
