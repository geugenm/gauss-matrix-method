#include "Headers/LdlFactorization.h"

int main() {
    Matrix initialMatrix("../matrix.prn");
    initialMatrix.Print();

    EquationMatrix equationMatrix(initialMatrix);

    GaussMatrix solvedGaussMatrix(equationMatrix);
    solvedGaussMatrix.Print();

    InconsistencyVector inconsistencyVector(solvedGaussMatrix, initialMatrix);
    inconsistencyVector.Print();

    RelativeError relativeError(inconsistencyVector, initialMatrix);
    relativeError.Print();

    if (equationMatrix.GetLeftSide().IsSymmetric()) {
        std::cout << "\n======LDL AVAILABLE======\n" << std::endl;
        LdlMatrix ldlMatrix(initialMatrix);
        ldlMatrix.Print();
    }

    return 0;
}