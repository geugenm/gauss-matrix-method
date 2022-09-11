#include "../headers/InconsistencyVector.h"

InconsistencyVector::InconsistencyVector(const GaussMatrix &gaussMatrix) {
    this->_gaussMatrix = std::make_unique<GaussMatrix>(gaussMatrix);
    this->_inconsistencyVector.resize(this->_gaussMatrix->GetRowsNumber());

    this->RecalculateInconsistency();
}

void InconsistencyVector::FindInconsistency() {
    for (uint64_t i = 0; i < this->_gaussMatrix->GetRowsNumber(); i++) {
        const double80_t equationColumnValue = this->_gaussMatrix->operator[](i)[
                this->_gaussMatrix->GetColumnsNumber() - 1];
        this->_inconsistencyVector[i] = this->FindRowSum(i) - equationColumnValue;
    }
}

double80_t InconsistencyVector::FindRowSum(const uint64_t &targetedRow) const {
    double80_t sum = 0.0;
    for (uint64_t j = 0; j < this->_gaussMatrix->GetColumnsNumber() - 1; j++) {
        sum += this->_gaussMatrix->GetRoot(j) * this->_gaussMatrix->operator[](targetedRow)[j];
    }
    return sum;
}

void InconsistencyVector::Print() const {
    const uint64_t precision = 32;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->_gaussMatrix->GetRowsNumber(); i++) {
        std::cout << "Inconsistency for x" << i << ": " << std::setw(width) << this->_inconsistencyVector[i]
                  << std::endl;
    }

    std::cout << "Norm: " << this->_maxError;
}

void InconsistencyVector::FindNorm() {
    this->_maxError = *std::max_element(this->_inconsistencyVector.begin(), this->_inconsistencyVector.end());
}

void InconsistencyVector::RecalculateInconsistency() {
    this->FindInconsistency();
    this->FindNorm();
}
