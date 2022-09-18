#include "Headers/RelativeError.h"
#include "Headers/LdlFactorization.h"

int main() {
    Matrix testManualInputMatrix;
    testManualInputMatrix.Print();

    Matrix initialMatrix(3, 3);
    initialMatrix.ReadFromFile("../matrix.txt");
    initialMatrix.Print();

    /*GaussMatrix solvedGaussMatrix(initialMatrix);
    solvedGaussMatrix.Print();

    InconsistencyVector inconsistencyVector(solvedGaussMatrix, initialMatrix);
    inconsistencyVector.Print();

    RelativeError relativeError(inconsistencyVector, initialMatrix);
    relativeError.Print();*/

    LdlMatrix test(initialMatrix);
    test.Print();

    return 0;
}