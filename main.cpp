#include <iostream>
#include "headers/Matrix.h"
#include "headers/Gauss.h"
#include "headers/InconsistencyVector.h"
#include "headers/RelativeError.h"

// Todo:
// 1. Write unit tests
// 2. Refactor this trash code


int main() {
    std::vector<std::vector<double80_t>> data{};
    data.resize(3);
    for (uint64_t i = 0; i < 3; i++) {
        data[i].resize(4);
    }

    data[0][0] = 1.0;
    data[0][1] = 2.0;
    data[0][2] = 1.0;
    data[0][3] = 1.0;

    data[1][0] = -1.0;
    data[1][1] = -2.0;
    data[1][2] = 2.0;
    data[1][3] = 1.0;

    data[2][0] = 0.0;
    data[2][1] = 1.0;
    data[2][2] = 1.0;
    data[2][3] = 2.0;

    Matrix testTaskMatrix(data);

    GaussMatrix testMatrix(testTaskMatrix);
    testMatrix.Print();

    testMatrix.SolveSystem();
    testMatrix.Print();

    testMatrix.PrintRoots();
    InconsistencyVector test(testMatrix, testTaskMatrix);
    test.Print();

    RelativeError testError(test, testTaskMatrix);
    testError.SolveInconsistentEquation();
    testError.Print();
    return 0;
}