#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cmath>
#include "../headers/Matrix.h"



class GaussMatrix {
public:
    GaussMatrix() {
        this->_matrix = std::make_unique<Matrix>(5, 6);

        this->_matrix->RandomInit(-100.0, 100.0);

        this->_roots.resize(this->_matrix->GetRowsNumber());
    }

    void PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo) {
        const uint64_t maxElementIndex = this->_matrix->GetMaxColumnElementIndex(columnIndex);
        std::swap(this->_matrix->operator[](maxElementIndex)[columnIndex],
                  this->_matrix->operator[](comparedTo)[columnIndex]);
    }

    void NullifyLowerElementsFrom(const uint64_t & currentRow) {
        const uint64_t rowsGeneral = this->_matrix->GetRowsNumber();
        const uint64_t rowToSubtract = currentRow - 1;
        const uint64_t columnToSubtract = currentRow - 1;

        for (uint64_t j = currentRow; j < rowsGeneral; j++) {
            const double80_t multiplier = this->_matrix->operator[](j)[columnToSubtract];
            this->_matrix->SubtractMultipliedRow(rowToSubtract, j, multiplier);
        }
    }

    void MakeDiagonalElementOne(const uint64_t & currentRow) {
        const double80_t diagonalElement = this->_matrix->operator[](currentRow)[currentRow];
        this->_matrix->MultiplyRowBy(currentRow, 1 / diagonalElement);
    }

    void FindSolutionFor(const uint64_t & index) {
        const uint64_t equalMatrixIndex = this->_matrix->GetColumnsNumber() - 1;
        double80_t localRoots = 0;

        for (uint64_t i = index + 1; i < this->_matrix->GetColumnsNumber(); i++) {
            localRoots += this->_matrix->operator[](index)[i] * this->_roots[i];
        }

        this->_roots[index] = this->_matrix->operator[](index)[equalMatrixIndex] - localRoots;
    }

    void StraightforwardStroke() {
        const uint64_t rowsGeneral = this->_matrix->GetRowsNumber();

        this->PlaceMaxElementOnRow(0, 0);

        for (uint64_t i = 0; i < rowsGeneral; i++) {
            if (i >= 1) {
                this->NullifyLowerElementsFrom(i);
            }

            this->PlaceMaxElementOnRow(i, i);
            this->MakeDiagonalElementOne(i);
        }

        for (uint64_t i = rowsGeneral - 1; i < rowsGeneral; i--) {
            this->FindSolutionFor(i);
        }
    }

    void Print() const {
        this->_matrix->Print();
    }

    void PrintRoots() const {
        for (uint64_t i = 0; i < this->_matrix->GetRowsNumber(); i++) {
            std::cout << "Root for x" << i << " is: " << this->_roots[i] << std::endl;
        }
    }

    ~GaussMatrix() = default;

private:
    std::unique_ptr<Matrix> _matrix;

    std::vector<double80_t> _roots;
};

int main() {
    GaussMatrix testMatrix;
    testMatrix.Print();

    std::cout << "\n" << std::endl;

    testMatrix.StraightforwardStroke();
    testMatrix.Print();

    testMatrix.PrintRoots();
}