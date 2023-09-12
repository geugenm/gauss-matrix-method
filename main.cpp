#include "Headers/LdlFactorization.h"

int main(int argc, char ** argv, char ** env) {
    std::cout << "Running main() from " << __FILE__ << std::endl;

    std::cout << "Arguments: " << argc - 1 << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << " " << argv[i];
    }
    std::cout << std::endl;

    std::cout << "Environment: " << env << std::endl;

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

    std::cin.get();

    return std::cout.good() ? EXIT_SUCCESS : EXIT_FAILURE;
}