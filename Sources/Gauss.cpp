#include "../headers/Gauss.h"


// ─── Constructors Section ───────────────────────────────────────────────────────

GaussMatrix::GaussMatrix(const GaussMatrix &source) {
    this->_equationMatrix = std::make_shared<EquationMatrix>(*source._equationMatrix);
    this->_roots = std::make_shared<Matrix>(*source._roots);
    this->SolveSystem();
}

GaussMatrix::GaussMatrix(const EquationMatrix &source) {
    if (source.IsEmpty()) {
        throw (std::invalid_argument("EquationMatrix matrix for Gauss is empty"));
    }

    this->_equationMatrix = std::make_shared<EquationMatrix>(source);

    constexpr uint64_t numberOfRootsColumns = 1;
    this->_roots = std::make_shared<Matrix>(source.GetColumnsNumber() - 1, numberOfRootsColumns);
    this->SolveSystem();
}

GaussMatrix::GaussMatrix(const Matrix &source) : GaussMatrix(*std::make_shared<EquationMatrix>(source)) {

}


// ─── Operators ──────────────────────────────────────────────────────────────────

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

GaussMatrix &GaussMatrix::operator=(const GaussMatrix &source) {
    this->_equationMatrix = std::make_shared<EquationMatrix>(*source._equationMatrix);
    this->_roots = std::make_shared<Matrix>(*source._roots);
    return *this;
}


// ─── Public Methods ─────────────────────────────────────────────────────────────

void GaussMatrix::Print() const {
    this->_equationMatrix->Print();

    this->PrintRoots();
}

uint64_t GaussMatrix::GetRowsNumber() const {
    return this->_equationMatrix->GetRowsNumber();
}

uint64_t GaussMatrix::GetColumnsNumber() const {
    return this->_equationMatrix->GetColumnsNumber();
}


// ─── Private Methods ────────────────────────────────────────────────────────────

void GaussMatrix::PrintRoots() const {
    const uint64_t precision = 4;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        std::cout << "Root for x" << i << " is: ";
        std::cout << std::setw(width) << this->_roots->operator[](i)[0] << std::endl;
    }

    std::cout << std::endl;
}

void
GaussMatrix::ReplaceDiagonalElementWithTheMaxInTheColumn(const uint64_t &currentColumn) {
    const uint64_t maxElementIndex = this->_equationMatrix->GetMaxColumnElementIndex(currentColumn);
    if (maxElementIndex == 0) {
        throw (std::logic_error("This matrix is degenerate"));
    }
    this->_equationMatrix->SwapRows(maxElementIndex, currentColumn);
}

void GaussMatrix::NullifyLowerElementsFrom(const uint64_t &currentRow) {
    const uint64_t currentColumn = currentRow - 1;
    OperableSet subtractionRowsSet = {0, currentRow - 1};

    for (uint64_t j = currentRow; j < this->GetRowsNumber(); j++) {
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
    double80_t localRoots = 0;

    for (uint64_t i = 0; i < this->_equationMatrix->GetLeftSide().GetColumnsNumber(); i++) {
        localRoots += this->_equationMatrix->GetLeftSide()[index][i] * this->_roots->operator[](i)[0];
    }

    this->_roots->operator[](index)[0] = this->_equationMatrix->GetRightSide()[index][0] - localRoots;
}

void GaussMatrix::StraightforwardStroke() {
    this->PrepareFirstElement();

    for (uint64_t i = 1; i < this->GetRowsNumber(); i++) {
        this->NullifyLowerElementsFrom(i);
        this->ReplaceDiagonalElementWithTheMaxInTheColumn(i);
        this->MakeDiagonalElementOne(i);
    }
}

void GaussMatrix::ReverseStroke() {
    for (uint64_t i = this->GetRowsNumber() - 1; i < this->GetRowsNumber(); i--) {
        this->FindSolutionFor(i);
    }
}

void GaussMatrix::SolveSystem() {
    this->StraightforwardStroke();
    this->ReverseStroke();
}

void GaussMatrix::PrepareFirstElement() {
    this->ReplaceDiagonalElementWithTheMaxInTheColumn(1);
    this->MakeDiagonalElementOne(1);
}

Matrix &GaussMatrix::GetRootsMatrix() const {
    return *this->_roots;
}
