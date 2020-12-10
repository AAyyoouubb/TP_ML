#include <math.h>
#include <stdio.h>
#include "Math_Functions.h"

#ifndef TP_ML_OPTIMIZER_H
#define TP_ML_OPTIMIZER_H


///////////////////////////////////////////////////////



///////////////////////////////////////////////////////
long double phi(int dim, long double alpha, long double *gradW, long double *w, long double (*loss)(long double *)) {
    return loss(diff_vector(dim, w, scalar_vector(dim, alpha, gradW)));
}

long double
phiPr(int dim, long double alpha, long double *gradW, long double *w, long double *(*gradientCost)(long double *)) {
    return -dot_product(dim, gradW, gradientCost(diff_vector(dim, w, scalar_vector(dim, alpha, gradW))));
}

long double armijo(int dim, long double *gradW, long double *w, long double (*loss)(long double *)) {
    // Armijo Hyperparameters.
    static long double eps = .1;
    static long double eta = (1.01 + rand() / (long double) RAND_MAX);

    long double alpha = 10e-7;
    long double phiPrZero = -dot_product(dim, gradW, gradW);
    long double phiZero = loss(w);
    while (phi(dim, alpha, gradW, w, loss) > alpha * phiPrZero * eps + phiZero)
        alpha /= eta;
    while (phi(dim, alpha, gradW, w, loss) <= alpha * phiPrZero * eps + phiZero)
        alpha *= eta;
    return alpha / eta;
}

double regula_falsi(int dim, long double *gradW, long double *w, long double *(*gradientCost)(long double *)) {
    long double alpha2 = 10e-20;
    static long double *grad = (long double *) malloc(dim * sizeof(long double));
    // Calculating a new gradient updates the previous value of the gradient. so keep in memory the previous one.
    loop(i, 0, dim) grad[i] = gradW[i];
    double phiPr2 = phiPr(dim, alpha2, grad, w, gradientCost);
    long double tmp2;
    long double perturbation = 2;
    while (phiPr2 < -10e-10) {
        tmp2 = (phiPr(dim, alpha2 * (1 + perturbation), grad, w, gradientCost) -
                phiPr(dim, alpha2 * (1 - perturbation), grad, w, gradientCost)) /
               (alpha2 * (1 + perturbation) - alpha2 * (1 - perturbation));
        alpha2 = alpha2 - phiPr2 / (tmp2 == 0 ? -phiPr2 / (alpha2 * 0.01) : tmp2);
        phiPr2 = phiPr(dim, alpha2, grad, w, gradientCost);
    }
    // retrieve the old value of the gradient.
    loop(i, 0, dim) gradW[i] = grad[i];
    return alpha2;
}

// GRADIENT DESCENT using Armijo.
void
gradientDescent(int dim, long double *w, long double *(*gradient)(long double *), long double (*loss)(long double *),
                double delta) {
    long double *grad = gradient(w);
    long double step;
    printf("\n");
    while (norm(dim, grad) > delta) {
        // Update w
        step = armijo(dim, grad, w, loss);
        loop(i, 0, dim) w[i] = w[i] - step * grad[i];
        grad = gradient(w);
//        printf("%.20lf\n", loss(w));
        printf("Gradient Norm: %.20Lf\t \t Current Cost: %.20Lf\t \t Armijo Step: %.20Lf\n",
               norm(dim, grad), loss(w), step);
    }
    printf("\n");
}


#endif //TP_ML_OPTIMIZER_H
