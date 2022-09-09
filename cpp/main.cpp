#include <iostream>
#include "../headers/Matrix.h"
#include "../headers/Gauss.h"


int main() {
    GaussMatrix testMatrix;
    testMatrix.Print();

    testMatrix.StraightforwardStroke();
    testMatrix.ReverseStroke();
    testMatrix.Print();

    testMatrix.PrintRoots();
    testMatrix.InconsistencyVector();

    return 0;
}