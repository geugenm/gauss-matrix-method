#include "Headers/LdlFactorization.h"

int main() {
    Matrix initialMatrix(3, 4);
    initialMatrix.ReadFromFile("../matrix.prn");
    initialMatrix.Print();

    GaussMatrix solvedGaussMatrix(initialMatrix);
    solvedGaussMatrix.Print();

    InconsistencyVector inconsistencyVector(solvedGaussMatrix, initialMatrix);
    inconsistencyVector.Print();

    RelativeError relativeError(inconsistencyVector, initialMatrix);
    relativeError.Print();

    //LdlMatrix ldlMatrix(initialMatrix);
    //ldlMatrix.Print();

    return 0;
}