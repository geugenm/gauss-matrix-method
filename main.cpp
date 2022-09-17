#include "Headers/Gauss.h"

int main() {
    std::unique_ptr<Matrix> testTaskMatrix = std::make_unique<Matrix>(3, 4);
    testTaskMatrix->ReadFromFile("../matrix.txt");
    testTaskMatrix->Print();
    EquationMatrix suka(*testTaskMatrix);
    suka.Print();

    /*GaussMatrix testMatrix(*testTaskMatrix);
    testTaskMatrix->Print();
    testMatrix.Print();

    testMatrix.SolveSystem();
    testMatrix.Print();

    testMatrix.PrintRoots();
    testTaskMatrix->Print();*/
    return 0;
}