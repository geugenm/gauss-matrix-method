#include <iostream>
#include "headers/Matrix.h"
#include "headers/Gauss.h"
#include "headers/InconsistencyVector.h"
#include "headers/RelativeError.h"

// Todo:
// 1. Write unit tests
// 2. Refactor this trash code


int main() {
    Matrix beta(5, 6);
    beta.RandomInit(-10.0, 15.0);
    GaussMatrix testMatrix(beta);
    testMatrix.Print();

    testMatrix.SolveSystem();
    testMatrix.Print();

    testMatrix.PrintRoots();
    InconsistencyVector test(testMatrix);
    test.Print();

    RelativeError testError(test, beta);
    testError.SolveInconsistentEquation();
    testError.Print();

    return 0;
}