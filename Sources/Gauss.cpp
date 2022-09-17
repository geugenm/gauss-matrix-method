#include "../headers/Gauss.h"

GaussMatrix::GaussMatrix(const EquationMatrix &matrix) {
    if (matrix.IsEmpty()) {
        throw(std::invalid_argument("EquationMatrix matrix for Gauss is empty"));
    }

    this->_equationMatrix = std::make_unique<EquationMatrix>(matrix);

    constexpr uint64_t numberOfRootsColumns = 1;
    this->_roots = std::make_unique<Matrix>(matrix.GetRowsNumber(), numberOfRootsColumns);
}

void
GaussMatrix::PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo) {
    const uint64_t maxElementIndex = this->_equationMatrix->GetMaxColumnElementIndex(columnIndex, columnIndex);
    this->_equationMatrix->SwapRows(maxElementIndex, comparedTo);
}

void GaussMatrix::NullifyLowerElementsFrom(const uint64_t &currentRow) {
    const uint64_t currentColumn = currentRow - 1;
    OperableSet subtractionRowsSet = {0, currentRow - 1};

    for (uint64_t j = currentRow; j < this->_equationMatrix->GetLeftSide().GetRowsNumber(); j++) {
        const double80_t multiplier = this->_equationMatrix->GetLeftSide()[j][currentColumn];

        subtractionRowsSet.modifiableIndex = j;
        this->_equationMatrix->SubtractMultipliedRow(subtractionRowsSet, multiplier);
    }
}

void GaussMatrix::MakeDiagonalElementOne(const uint64_t &currentRow) {
    const double80_t diagonalElement = this->_equationMatrix->GetLeftSide()[currentRow][currentRow];
    this->_equationMatrix->MultiplyRow(currentRow, 1 / diagonalElement);
}

void GaussMatrix::FindSolutionFor(const uint64_t &index) {
    const uint64_t equalMatrixIndex = this->_equationMatrix->GetColumnsNumber() - 1;
    double80_t localRoots = 0;

    for (uint64_t i = 0; i < this->_equationMatrix->GetRightSide().GetColumnsNumber(); i++) {
        localRoots += this->_equationMatrix->GetRightSide()[index][i] * this->_roots->operator[](i)[0];
    }

    this->_roots->operator[](index)[0] = this->_equationMatrix->GetRightSide()[index][0] - localRoots;
}

void GaussMatrix::StraightforwardStroke() {
    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        if (i >= 1) {
            this->NullifyLowerElementsFrom(i);
        }
        this->PlaceMaxElementOnRow(i, i);
        this->MakeDiagonalElementOne(i);
    }
}

void GaussMatrix::ReverseStroke() {
    const uint64_t rowsGeneral = this->_equationMatrix->GetRowsNumber();

    for (uint64_t i = rowsGeneral - 1; i < rowsGeneral; i--) {
        this->FindSolutionFor(i);
    }
}

void GaussMatrix::Print() const {
    this->_equationMatrix->Print();
}

void GaussMatrix::PrintRoots() const {
    const uint64_t precision = 3;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->_equationMatrix->GetRowsNumber(); i++) {
        std::cout << "Root for x" << i << " is: " << std::setw(width) << this->_roots->operator[](i)[0] << std::endl;
    }
}

GaussMatrix::GaussMatrix(const GaussMatrix &source) {
    this->_equationMatrix = std::make_unique<EquationMatrix>(*source._equationMatrix);
    this->_roots = std::make_unique<Matrix>(*source._roots);
}

std::vector<double80_t> &GaussMatrix::operator[](const uint64_t &index) {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_equationMatrix->GetRowByIndex(index);
}

std::vector<double80_t> const &GaussMatrix::operator[](const uint64_t &index) const {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_equationMatrix->GetRowByIndex(index);
}

double80_t GaussMatrix::GetRoot(const uint64_t &index) const {
    if (this->_roots->IsEmpty()) {
        throw (std::out_of_range("Gauss root is empty"));
    }
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Gauss root index out of range"));
    }
    return this->_roots->operator[](index)[0];
}

uint64_t GaussMatrix::GetRowsNumber() const {
    return this->_equationMatrix->GetRowsNumber();
}

uint64_t GaussMatrix::GetColumnsNumber() const {
    return this->_equationMatrix->GetColumnsNumber();
}

GaussMatrix &GaussMatrix::operator=(const GaussMatrix &source) {
    this->_equationMatrix = std::make_unique<EquationMatrix>(*source._equationMatrix);
    this->_roots = std::make_unique<Matrix>(*source._roots);
    return *this;
}

void GaussMatrix::SolveSystem() {
    this->StraightforwardStroke();
    this->ReverseStroke();
}

GaussMatrix::GaussMatrix(const Matrix &source) {
    if (source.IsEmpty()) {
        throw(std::invalid_argument("EquationMatrix matrix for Gauss is empty"));
    }

    this->_equationMatrix = std::make_unique<EquationMatrix>(source);
    source.Print();

    constexpr uint64_t numberOfRootsColumns = 1;
    this->_roots = std::make_unique<Matrix>(source.GetColumnsNumber(), numberOfRootsColumns);
}
