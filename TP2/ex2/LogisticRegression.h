//
// Created by ayoub on 20. 11. 20..
//

#ifndef TP_ML_LOGISTICREGRESSION_H
#define TP_ML_LOGISTICREGRESSION_H

#include <stdio.h>
#include "../Optimizer.h"
#include "../Distributions.h"

int m;
double **x; // TODO: each column is a feature; x should contain 1 at first column;
int *y;
int dim;    // Dimension of w.


double loss(double *w) {
    double l = 0;
    loop(i, 0, m) l += log(1 + exp(-y[i] * dot_product(dim, w, x[i])));
    return l / m;
}

double *gradientLoss(double *w) {
    // No need to allocate the same array for multiple uses unless it changes it's size.
    static double *g = (double *) malloc(dim * sizeof(double));
    double tmp;
    loop(j, 0, dim) g[j] = 0;
    loop(i, 0, m) {
        tmp = -1 / (1 + exp(y[i] * dot_product(dim, w, x[i])));
        loop(j, 0, dim) g[j] += tmp * x[i][j] * y[i];
    }
    loop(j, 0, dim) g[j] /= m;
    return g;
}

double predict(double *w, double *xx) {
    double sum = 0;
    loop(i, 0, dim) sum += w[i] * xx[i];
    return 1 / (1 + exp(-sum));
}

double *fitData() {
    // Initialize W
    double *w = (double *) calloc(dim, sizeof(double));
    // TODO: Initialize from uniform distribution, normal distribution, bernoulli with parameter .4;
//     generateUniformly(dim,w);
//     generateUsingStandardNormal(dim,w);
//     generateUsingBernouilli(dim,w);

    // Execute Gradient Descent Algorithm using logistic loss;
    gradientDescent(dim, w, &gradientLoss, &loss, 10.e-8);
    // Print final loss, and optimal parameters;
    printf("\n Set of optimal Parameters: \t");
    loop(i, 0, dim) printf("%lf  ", w[i]);
    printf("\n Final Loss: \t %lf", loss(w));
    // TODO: plot the classifier.

    return w;
}

void readcsv() {
    FILE *file = fopen("binary.csv", "r");
    if (file == NULL) exit(-1);
    // The file contains 401 rows including the header; and 4 variables, the first one is the label;
    dim = 3;
    m = 400;
    x = (double **) malloc(m * sizeof(double *));
    y = (int *) malloc(m * sizeof(int));
    char line[1024];
    // Read the header:
    fgets(line, sizeof(line), file);
    // Now Read each observation;
    int i = 0;
    float tmp;
    int itmp;
    while (!feof(file)) {
        // Allocate memo for observation;
        x[i] = (double *) malloc((dim + 1) * sizeof(double));
        x[i][0] = 1;      // Always
        // Now reading the label
        fscanf(file, "%i", &itmp);
        y[i] = itmp;
        // Reading the rest of the variables
        loop(j, 1, dim + 1) {
            // Read the comma here.
            fscanf(file, "%c", line);
            fscanf(file, "%f", &tmp);
            x[i][j] = tmp;
        }
        i++;
    }


    fclose(file);
}

#endif //TP_ML_LOGISTICREGRESSION_H
