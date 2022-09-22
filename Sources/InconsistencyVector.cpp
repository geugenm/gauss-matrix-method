#include "../headers/InconsistencyVector.h"

InconsistencyVector::InconsistencyVector(const GaussMatrix &gaussMatrix, const EquationMatrix &matrix)
        : _maxAbsoluteInconsistency(0.0) {
    this->_gaussRoots = std::make_unique<Matrix>(gaussMatrix.GetRootsMatrix());
    this->_initialMatrix = std::make_shared<EquationMatrix>(matrix);

    this->CalculateInconsistency();
}

InconsistencyVector::InconsistencyVector(const GaussMatrix &gaussMatrix, const Matrix &matrix) : InconsistencyVector(
        gaussMatrix, *std::make_unique<EquationMatrix>(matrix)) {

}

InconsistencyVector::InconsistencyVector(const InconsistencyVector &source) : _maxAbsoluteInconsistency(0.0) {
    this->_gaussRoots = std::make_unique<Matrix>(*source._gaussRoots);
    this->_inconsistencyVector = std::make_unique<Matrix>(*source._gaussRoots);
    this->_initialMatrix = std::make_unique<EquationMatrix>(*source._initialMatrix);

    this->CalculateInconsistency();
}

void InconsistencyVector::FindInconsistency() {
    this->_inconsistencyVector = std::make_unique<Matrix>(
            this->_initialMatrix->GetLeftSide() * (*this->_gaussRoots) - this->_initialMatrix->GetRightSide());
}

void InconsistencyVector::Print() const {
    std::ios oldCoutState(nullptr);
    oldCoutState.copyfmt(std::cout);

    const uint64_t precision = 5;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision) << std::scientific;

    for (uint64_t i = 0; i < this->_gaussRoots->GetRowsNumber(); i++) {
        std::cout << "Inconsistency for x" << i << ": " << std::setw(width)
                  << this->_inconsistencyVector->operator[](i)[0]
                  << std::endl;
    }

    std::cout << "\nNorm: " << this->_maxAbsoluteInconsistency << std::endl;
    std::cout.copyfmt(oldCoutState);
    std::cout << std::endl;
}

void InconsistencyVector::FindNorm() {
    const uint64_t maxInconsistencyIndex = this->_inconsistencyVector->GetMaxColumnElementIndex(0);
    this->_maxAbsoluteInconsistency = std::fabs(this->_inconsistencyVector->operator[](maxInconsistencyIndex)[0]);
}

void InconsistencyVector::CalculateInconsistency() {
    this->FindInconsistency();
    this->FindNorm();
}

Matrix InconsistencyVector::GetRootsMatrix() const {
    return *this->_gaussRoots;
}

double80_t InconsistencyVector::GetMaxAbsoluteInconsistency() const {
    return this->_maxAbsoluteInconsistency;
}
