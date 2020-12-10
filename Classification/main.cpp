//
// Created by ayoub on 20. 12. 8..
//


#include "../Regression/Adaline.h"

int main(int argc, char *argv[]) {
    read_csv("pressure/pressure3.csv", 4, 19);
//     Printing the data.
//    loop(i, 0, m) printf("%.10Lf , %.10Lf  , %.10Lf , , %.10Lf \n", x[i][0], x[i][1],x[i][2], y[i]);
//    shuffle(m,x,y);
    long double *w = fitData();

    return 0;
}
