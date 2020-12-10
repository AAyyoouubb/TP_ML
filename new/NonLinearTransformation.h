//
// Created by ayoub on 20. 12. 8..
//

#ifndef TP_ML_NONLINEARTRANSFORMATION_H
#define TP_ML_NONLINEARTRANSFORMATION_H

#include <malloc.h>

double **mapFeatures(int dim, int degree, double **x) {
    // Valid only when dim=3;
    double **c = (double **) malloc((degree * (degree + 3)) / 2 * sizeof(double *));
    loop()
}

#endif //TP_ML_NONLINEARTRANSFORMATION_H
