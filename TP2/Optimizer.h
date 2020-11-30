#include <math.h>
#include "Math_Functions.h"

#ifndef TP_ML_OPTIMIZER_H
#define TP_ML_OPTIMIZER_H


///////////////////////////////////////////////////////



///////////////////////////////////////////////////////
double phi(int dim, double alpha, double *gradW, double *w, double (*loss)(double *)) {
    return loss(diff_vector(dim, w, scalar_vector(dim, alpha, gradW)));
}

double armijo(int dim, double *gradW, double *w, double (*loss)(double *)) {
    // Armijo Hyperparameters.
    static double eps = .001;
    static double eta = 10;

    double alpha = 10.e-15;
    double phiPrZero = -dot_product(dim, gradW, gradW);
    double phiZero = loss(w);
    while (phi(dim, alpha, gradW, w, loss) <= alpha * phiPrZero * eps + phiZero)
        alpha *= eta;

    return alpha / eta;
}

// GRADIENT DESCENT using Armijo.
void gradientDescent(int dim, double *w, double *(*gradient)(double *), double (*loss)(double *), double delta) {
    double *grad = gradient(w);
    double step;
    while (norm(dim, grad) > delta) {
        // Update w
        step = armijo(dim, grad, w, loss);
        loop(i, 0, dim) w[i] = w[i] - step * grad[i];
        grad = gradient(w);
        printf("%lf\t%lf\t%.20f\n", norm(dim, grad), loss(w), step);
    }
}

//
//double phiSec();

#endif //TP_ML_OPTIMIZER_H
