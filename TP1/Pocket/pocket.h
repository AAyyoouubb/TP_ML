#define loop(i, a, b) for(int i=a;i<b;i++)
#include <bits/stdc++.h>
#include "../DataStructure/Matrix.h"
using namespace std;

double randomGen(int i, int j) {
    return 0.02334 * (double) (random() % 376);
}

class Pocket
{
public:
    Matrix<double> w;
    Matrix<double> X;
    Matrix<int> y;
    int n;

    Pocket(int n)
    {
        w = Matrix<double>(n + 1, 1);
        w.randomfill(&randomGen);
    }

    double predict(Matrix<double> x)
    {
        return double(x * w[ {1, -1}] + w(0));
    }

    double loss(Matrix<double> w, Matrix<double> &X, Matrix<int> &y)
    {
        double loss = 0;
        auto t = X * w[ {1, -1}] + w(0);
        loop(i, 0, t.getRows())
        {
            if (y(i) * t(i) < 0)
                loss++;
        }
        return loss / X.getRows();
    }

    vector<double> fit(Matrix<double> &X, Matrix<int> &y)
    {
        vector<double> losses;
        double los = 1;
        int Tmax = 10000;
        Matrix<double> ws = w;

        loop(i, 0, Tmax)
        {
            auto t = X * w[ {1, -1}] + w(0);
            loop(i, 0, n)
            {
                if (y(i) * t(i) < 0)
                {
                    w[i] = w[i] + X[i] * y[i];
                    break;
                }
            }

            if(loss(w, X, y) < loss(ws, X, y))
                ws = w;

            losses.push_back(loss(ws, X, y));
        }
        return losses;
    }

};