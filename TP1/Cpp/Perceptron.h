#ifndef TP_ML_PERCEPTRON_H
#define TP_ML_PERCEPTRON_H

#define loop(i, a, b) for(int i=a;i<b;i++)

#include <random>
#include "../DataStructure/Matrix.h"

using namespace std;

double randomGen(int i, int j) {
    return 0.02334 * (double) (random() % 376);
}

class Perceptron {
private:
    Matrix<double> w;

    void updateW(Matrix<double> x, int y) {
        w[{1, -1}] = (x * y).transpose() + w[{1, -1}];
        w(0) = w(0) + y;
    }

public:
    explicit Perceptron(int dim) {
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

    vector<double> fit(Matrix<double> &X, Matrix<int> &y) {
        vector<double> losses;
        double los = 1;
        while (los > 0) {
            los = loss(X, y);
            losses.push_back(los);
            loop(i, 0, X.getRows()) {
                if (double(y(i) * predict(X(i))) < 0)
                    updateW(X(i), (int) y(i));
            }

        }
        return losses;
    }

};


#endif //TP_ML_PERCEPTRON_H
