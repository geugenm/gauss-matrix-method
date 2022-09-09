#include "Gauss.h"

GaussMatrix::GaussMatrix() {
    this->_matrix = std::make_unique<Matrix>(5, 6);

    this->_matrix->RandomInit(-100.0, 100.0);

    this->_roots.reserve(this->_matrix->GetRowsNumber());
}

GaussMatrix::GaussMatrix(const Matrix &matrix) {
    this->_matrix = std::make_unique<Matrix>(matrix);
}

void GaussMatrix::PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo, const uint64_t & fromRow) {
    const uint64_t maxElementIndex = this->_matrix->GetMaxColumnElementIndex(columnIndex, fromRow);
    if (maxElementIndex == comparedTo) {
        return;
    }
    std::swap(this->_matrix->operator[](maxElementIndex), this->_matrix->operator[](comparedTo));
}

void GaussMatrix::NullifyLowerElementsFrom(const uint64_t &currentRow) {
    OperableSet subtractionSet = {0, currentRow - 1};
    const uint64_t currentColumn = currentRow - 1;

    for (uint64_t j = currentRow; j < this->_matrix->GetRowsNumber(); j++) {
        const double80_t multiplier = this->_matrix->operator[](j)[currentColumn];

        subtractionSet.modifiableIndex = j;
        this->_matrix->SubtractMultipliedRow(subtractionSet, multiplier);
    }
}

void GaussMatrix::MakeDiagonalElementOne(const uint64_t &currentRow) {
    const double80_t diagonalElement = this->_matrix->operator[](currentRow)[currentRow];
    this->_matrix->MultiplyRow(currentRow, 1 / diagonalElement);
}

void GaussMatrix::FindSolutionFor(const uint64_t &index) {
    const uint64_t equalMatrixIndex = this->_matrix->GetColumnsNumber() - 1;
    double80_t localRoots = 0;

    for (uint64_t i = index + 1; i < this->_matrix->GetColumnsNumber(); i++) {
        localRoots += this->_matrix->operator[](index)[i] * this->_roots[i];
    }

    this->_roots[index] = this->_matrix->operator[](index)[equalMatrixIndex] - localRoots;
}

void GaussMatrix::StraightforwardStroke() {
    const uint64_t rowsGeneral = this->_matrix->GetRowsNumber();

    for (uint64_t i = 0; i < rowsGeneral; i++) {
        if (i >= 1) {
            this->NullifyLowerElementsFrom(i);
        }

        std::cout << "i is:" << i << std::endl;
        this->_matrix->Print();
        this->PlaceMaxElementOnRow(i, i, i);
        this->_matrix->Print();
        std::cout << "==========================="<< std::endl;
        this->MakeDiagonalElementOne(i);
    }
}

void GaussMatrix::ReverseStroke() {
    const uint64_t rowsGeneral = this->_matrix->GetRowsNumber();

    for (uint64_t i = rowsGeneral - 1; i < rowsGeneral; i--) {
        this->FindSolutionFor(i);
    }
}

void GaussMatrix::Print() const {
    this->_matrix->Print();
}

void GaussMatrix::PrintRoots() const {
    const uint64_t precision = 3;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->_matrix->GetRowsNumber(); i++) {
        std::cout << "Root for x" << i << " is: " << std::setw(width) << this->_roots[i] << std::endl;
    }
}

void GaussMatrix::InconsistencyVector() const {
    std::vector<double80_t> inconsistencyVector;
    inconsistencyVector.reserve(this->_matrix->GetRowsNumber());

    const uint64_t precision = 32;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->_matrix->GetRowsNumber(); i++) {
        const double80_t equationColumnValue = this->_matrix->operator[](i)[this->_matrix->GetColumnsNumber() - 1];
        double80_t sum = 0.0;
        for (uint64_t j = 0; j < this->_matrix->GetColumnsNumber() - 1; j++) {
            sum += this->_roots[j] * this->_matrix->operator[](i)[j];
        }
        inconsistencyVector[i] = sum - equationColumnValue;
        std::cout << "Element " << i << ": " << std::setw(width) << inconsistencyVector[i] << std::endl;
    }
}
