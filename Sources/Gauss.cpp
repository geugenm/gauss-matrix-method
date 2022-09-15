#include "../headers/Gauss.h"

GaussMatrix::GaussMatrix(const Matrix &matrix) {
    this->_matrix = std::make_unique<Matrix>(matrix);

    this->_roots.resize(this->_matrix->GetRowsNumber() + 1);
}

void
GaussMatrix::PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo) {
    const uint64_t maxElementIndex = this->_matrix->GetMaxColumnElementIndex(columnIndex, columnIndex);
    std::swap(this->_matrix->operator[](maxElementIndex), this->_matrix->operator[](comparedTo));
}

void GaussMatrix::NullifyLowerElementsFrom(const uint64_t &currentRow) {
    const uint64_t currentColumn = currentRow - 1;
    OperableSet subtractionRowsSet = {0, currentRow - 1};

    for (uint64_t j = currentRow; j < this->_matrix->GetRowsNumber(); j++) {
        const double80_t multiplier = this->_matrix->operator[](j)[currentColumn];

        subtractionRowsSet.modifiableIndex = j;
        this->_matrix->SubtractMultipliedRow(subtractionRowsSet, multiplier);
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
    auto IsFirstRow = [](const uint64_t &targetedRow) {
        return (targetedRow >= 1);
    };

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        if (IsFirstRow(i)) {
            this->NullifyLowerElementsFrom(i);
        }
        this->PlaceMaxElementOnRow(i, i);
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

GaussMatrix::GaussMatrix(const GaussMatrix &source) : _roots(source._roots) {
    this->_matrix = std::make_unique<Matrix>(*source._matrix);
}

std::vector<double80_t> &GaussMatrix::operator[](const uint64_t &index) {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_matrix->operator[](index);
}

std::vector<double80_t> const &GaussMatrix::operator[](const uint64_t &index) const {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_matrix->operator[](index);
}

double80_t GaussMatrix::GetRoot(const uint64_t &index) const {
    if (this->_roots.empty()) {
        throw (std::out_of_range("Gauss root is empty"));
    }
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_roots[index];
}

uint64_t GaussMatrix::GetRowsNumber() const {
    return this->_matrix->GetRowsNumber();
}

uint64_t GaussMatrix::GetColumnsNumber() const {
    return this->_matrix->GetColumnsNumber();
}

GaussMatrix &GaussMatrix::operator=(const GaussMatrix &source) {
    this->_matrix = std::make_unique<Matrix>(*source._matrix);
    this->_roots = source._roots;
    return *this;
}

void GaussMatrix::SolveSystem() {
    this->StraightforwardStroke();
    this->ReverseStroke();
}
