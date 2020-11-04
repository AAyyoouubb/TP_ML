
#include "pocket.h"
#include <iostream>
int main() {
    int rows = 3, cols = 2;
    Matrix<double> X(rows, cols);
    Matrix<int> y(rows, 1);
    loop(i, 0, X.getRows()) {
        y(i, 0) = pow(-1, i);
        X(i, 0) = y(i, 0) * (i + 1);
        X(i, 1) = X(i, 0);
    }

    Pocket p(cols);
    X.print();
    vector<double> loss = p.fit(X, y);
    p.w.print();
    for (auto &t:loss) cout << t << " ";
    cout<<endl;

    return 0;
}
