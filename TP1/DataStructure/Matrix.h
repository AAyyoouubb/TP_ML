#ifndef TP_ML_MATRIX_H
#define TP_ML_MATRIX_H

#define loop(i, a, b) for(int i=a;i<b;i++)

#include <bits/stdc++.h>

using namespace std;


template<typename T>
class Matrix {
private :
    T *matrix;
    int n = -1, m = -1;

public :
    Matrix() {};

    Matrix(int rows, int cols) {
        setSize(rows, cols);
        matrix = new T[rows * cols];
    }

    void setSize(int rows, int cols) {
        n = rows;
        m = cols;
    }

    int getRows() {
        return n;
    }

    int getCols() {
        return m;
    }

    ~Matrix() {
        //TODO
//        delete[] matrix;
    }

    void randomfill(const function<T(int, int)> &func) {
        loop(i, 0, n)loop(j, 0, m)(*this)(i, j) = func(i, j);
    }

    template<typename TT>
    explicit operator TT() const {
        assert(n == m == 1);
        return TT(matrix[0]);
    }

    Matrix<T> operator()(int i) {
        assert(i >= 0);
        Matrix<T> tmp;
        tmp.setSize(1, 1);
        if (n == 1) {
            assert(i < m);
            tmp.matrix = matrix + i;
            return tmp;
        }
        assert(i < n);
        if (m == 1) {
            tmp.matrix = matrix + i;
            return tmp;
        }
        tmp.setSize(1, m);
        tmp.matrix = matrix + m * i;
        return tmp;
    }

    void print() {
        loop(i, 0, n) {
            loop(j, 0, m)cout << (*this)(i, j) << " ";
            cout << endl;
        }
    }

    T &operator()(int i, int j) {
        assert(i >= 0 and j >= 0 and i < n and j < m);
        return matrix[i * m + j];
    }

    Matrix<T> transpose() {
        Matrix<T> tmp(m, n);
        loop(i, 0, n)loop(j, 0, m) tmp(j, i) = (*this)(i, j);
        return tmp;
    }

    Matrix<T> operator[](pair<int, int> tt) {
        int i = tt.first, j = tt.second;
        if (j < 0) j = n + j;
        assert(0 <= i and i <= j and j < n);
        Matrix<T> tmp;
        tmp.setSize(j - i + 1, m);
        tmp.matrix = matrix + i * m;
        return tmp;
    }

    template<typename TT>
    auto operator-(TT b) {
        assert (is_fundamental<TT>::value);
        auto typ = b + (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) - b;
        return mat;
    }


    template<typename TT>
    auto operator-(Matrix<TT> b) {
        if (b.getRows() == b.getCols() == 1)
            return (*this) + b(0, 0);
        assert(m == b.getCols() and n == b.getRows());
        auto typ = b(0, 0) + (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) - b(i, j);
        return mat;
    }


    template<typename TT>
    auto operator+(TT b) {
        assert (is_fundamental<TT>::value);
        auto typ = b + (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) + b;
        return mat;
    }


    template<typename TT>
    auto operator+(Matrix<TT> b) {
        if (b.getRows() == b.getCols() == 1)
            return (*this) + b(0, 0);
        assert(m == b.getCols() and n == b.getRows());
        auto typ = b(0, 0) + (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) + b(i, j);
        return mat;
    }

    // copy values not reference;
    template<typename U>
    auto &operator=(Matrix<U> b) {
        assert(m == b.getCols() and n == b.getRows());
        loop(i, 0, n) loop(j, 0, m) (*this)(i, j) = b(i, j);
        return *this;
    }

    auto &operator=(Matrix<T> b) {
        if (n == -1 and m == -1) {
            setSize(b.getRows(), b.getCols());
            matrix = new double[n * m];
        }
        assert(m == b.getCols() and n == b.getRows());
        loop(i, 0, n) loop(j, 0, m) (*this)(i, j) = b(i, j);
        return *this;
    }

    template<typename U>
    auto &operator=(U b) {
        assert (is_fundamental<U>::value);
        loop(i, 0, n) loop(j, 0, m) (*this)(i, j) = b;
        return *this;
    }


    // Might produce infinity
    template<typename TT>
    auto operator/(TT b) {
        assert (is_fundamental<TT>::value);
        auto typ = (*this)(0, 0) / b;
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) / b;
        return mat;

    }

    // Unfortunately element wise division
    template<typename TT>
    auto operator/(Matrix<TT> b) {
        assert(b.getRows() == n and b.getCols() == m);
        auto typ = (*this)(0, 0) / b(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m) mat(i, j) = (*this)(i, j) / b(i, j);
        return mat;
    }

    template<typename TT>
    auto operator*(TT b) {
        assert(is_fundamental<TT>::value);
        auto typ = b * (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, m);
        loop(i, 0, n)loop(j, 0, m)mat(i, j) = (*this)(i, j) * b;
        return mat;
    }

    template<typename TT>
    auto operator*(Matrix<TT> b) {
        if (b.getRows() == b.getCols() == 1)
            return (*this) * b(0, 0);
        assert(m == b.getRows());
        auto typ = b(0, 0) * (*this)(0, 0);
        Matrix<typeof(typ)> mat(n, b.getCols());
        loop(i, 0, n) {
            loop(j, 0, b.getCols()) {
                auto sum = (*this)(i, 0) * b(0, j);
                loop(k, 1, m) sum += (*this)(i, k) * b(k, j);
                mat(i, j) = sum;
            }
        }
        return mat;
    }

    template<typename TT>
    auto operator<(TT b) {
        Matrix<bool> tmp(n, m);
        assert(is_fundamental<TT>::value);
        loop(i, 0, n)loop(j, 0, m) tmp(i, j) = (*this)(i, j) < b;
        return tmp;
    }

    template<typename TT>
    auto operator<(Matrix<TT> b) {
        Matrix<bool> tmp(n, m);
        if (b.getRows() == b.getCols() == 1)
            return (*this) < b(0, 0);
        assert(n == b.getRows() and m == b.getCols());
        loop(i, 0, n)loop(j, 0, m) tmp(i, j) = ((*this)(i, j) < b(i, j));
        return tmp;
    }


    bool any() {
        loop(i, 0, n) loop(j, 0, m) if ((*this)(i, j) == true) return true;
        return false;
    }

    bool all() {
        loop(i, 0, n) loop(j, 0, m) if ((*this)(i, j) == false) return false;
        return true;
    }

};


#endif //TP_ML_MATRIX_H
