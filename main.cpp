#include "Headers/RelativeError.h"

int main() {
    Matrix initialMatrix(3, 3);
    initialMatrix.ReadFromFile("../matrix.txt");
    initialMatrix.Print();

    std::cout << initialMatrix.IsSymmetric();

    return 0;
}