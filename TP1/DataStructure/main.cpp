
#include "Matrix.h"
#include <iostream>

double randomm(int i, int j) {
    return 0.02334 * (double) (random() % 376);
}

int main() {

    const int n = 4, m = 3;
    Matrix<int> A(n, m), B(n, m);
    A.randomfill(&randomm);
    B.randomfill(&randomm);

    B.print();
    cout << endl;

    A.print();
    cout << endl;

    cout << (B < A).any() << endl;
    cout << (B < A+100).all() << endl;




//    loop(i, 0, n) {
//        loop(j, 0, m) cout << A(i, j) << " ";
//        cout << endl;
//    }
//    A = A * B;
//    loop(i, 0, n) {
//        loop(j, 0, m) cout << A(i, j) << " ";
//        cout << endl;
//    }
//    BaseMatrix<double> *B = A(i);
//    loop(i, 0, n) {}


    return 0;
}
