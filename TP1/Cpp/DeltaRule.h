//
// Created by ayoub on 20. 10. 26..
//

#ifndef TP_ML_DELTARULE_H
#define TP_ML_DELTARULE_H

#include <random>
#include "../DataStructure/Matrix.h"

using namespace std;


double randomGen(int i, int j) {
    return 0.02334 * (double) (random() % 376);
}

class DeltaRule {
private:
    Matrix<double> w;

    void updateW(Matrix<double> x, int y, double tmp) {
        w[{1, -1}] = x * 2 * tmp;
        w(0) = w(0) + 2 * tmp;
    }

public:
    explicit DeltaRule(int dim) {
        w = Matrix<double>(dim + 1, 1);
        w.randomfill(&randomGen);
    }

    double predict(Matrix<double> x) {
        return double(x * w[{1, -1}] + w(0));
    }

    double loss(Matrix<double> &X, Matrix<int> &y) {
        double loss = 0;
        auto t = X * w[{1, -1}] + w(0);
        loop(i, 0, t.getRows()) {
            if (y(i) * t(i) < 0)
                loss++;
        }
        return loss / X.getRows();
    }

    vector<double> fit(Matrix<double> &X, Matrix<int> &y, int iter) {
        vector<double> losses;
        double tmp;
        loop(t, 0, iter) {
            losses.push_back(loss(X, y));
            loop(i, 0, X.getRows()) {
                tmp = double(y(i) - predict(X(i)));
                if (tmp != 0)
                    updateW(X(i), (int) y(i), tmp);
            }

        }
        return losses;
    }

};

#endif //TP_ML_DELTARULE_H
