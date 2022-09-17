#include "Headers/Gauss.h"
#include "Headers/InconsistencyVector.h"

int main() {
    Matrix initialMatrix(3, 4);
    initialMatrix.ReadFromFile("../matrix.txt");
    initialMatrix.Print();

    GaussMatrix solvedGaussMatrix(initialMatrix);
    solvedGaussMatrix.Print();

    InconsistencyVector testInconsistency(solvedGaussMatrix, initialMatrix);
    testInconsistency.Print();

    return 0;
}