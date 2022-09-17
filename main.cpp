#include "Headers/Gauss.h"

int main() {
    Matrix testTaskMatrix(3, 4);
    testTaskMatrix.ReadFromFile("../matrix.txt");
    testTaskMatrix.Print();

    GaussMatrix testMatrix(testTaskMatrix);
    testMatrix.Print();

    testMatrix.SolveSystem();
    testMatrix.Print();

    testMatrix.PrintRoots();
    testTaskMatrix.Print();
    return 0;
}