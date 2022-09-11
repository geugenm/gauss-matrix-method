#include <iostream>
#include "headers/Matrix.h"
#include "headers/Gauss.h"
#include "headers/InconsistencyVector.h"


int main() {
    Matrix beta(5, 6);
    beta.RandomInit(-10.0, 15.0);
    GaussMatrix testMatrix(beta);
    testMatrix.Print();

    testMatrix.StraightforwardStroke();
    testMatrix.ReverseStroke();
    testMatrix.Print();

    testMatrix.PrintRoots();
    InconsistencyVector test(testMatrix);
    test.Print();

    return 0;
}