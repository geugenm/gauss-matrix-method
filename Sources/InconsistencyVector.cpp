#include "../headers/InconsistencyVector.h"

InconsistencyVector::InconsistencyVector(const GaussMatrix &gaussMatrix, const Matrix & matrix) {
    this->_gaussMatrix = std::make_unique<GaussMatrix>(gaussMatrix);
    this->_initialMatrix = std::make_shared<EquationMatrix>(matrix);

    this->_inconsistencyVector.resize(this->_gaussMatrix->GetRowsNumber());

    this->RecalculateInconsistency();
}

void InconsistencyVector::FindInconsistency() {
    this->_gaussMatrix->GetRootsMatrix().Print();
    std::unique_ptr<Matrix> wow = std::make_unique<Matrix>(this->_initialMatrix->GetLeftSide() * this->_gaussMatrix->GetRootsMatrix() - this->_initialMatrix->GetRightSide());
    wow->Print();
    /*for (uint64_t i = 0; i < this->_gaussMatrix->GetRowsNumber(); i++) {
        const double80_t equationColumnValue = this->_initialMatrix->operator[](i)[
                this->_gaussMatrix->GetColumnsNumber() - 1];
        this->_inconsistencyVector[i] = this->FindRowSum(i) - equationColumnValue;
    }*/
}

double80_t InconsistencyVector::FindRowSum(const uint64_t &targetedRow) const {
    double80_t sum = 0.0;
    /*for (uint64_t j = 0; j < this->_gaussMatrix->GetColumnsNumber() - 1; j++) {
        sum += this->_gaussMatrix->GetRoot(j) * this->_initialMatrix->operator[](targetedRow)[j];
    }*/
    return sum;
}

void InconsistencyVector::Print() const {
    const uint64_t precision = 64;
    const uint64_t width = 7;

    std::cout << std::setprecision(precision);

    for (uint64_t i = 0; i < this->_gaussMatrix->GetRowsNumber(); i++) {
        std::cout << "Inconsistency for x" << i << ": " << std::setw(width) << this->_inconsistencyVector[i]
                  << std::endl;
    }

    std::cout << "Norm: " << this->_maxAbsoluteInconsistency;
}

void InconsistencyVector::FindNorm() {
    const double80_t maxInconsistencyValue = *std::max_element(this->_inconsistencyVector.begin(),
                                                               this->_inconsistencyVector.end(),
                                                               [](double80_t a, double80_t b) {
                                                                   return std::fabs(a) < std::fabs(b);
                                                               });
    this->_maxAbsoluteInconsistency = std::fabs(maxInconsistencyValue);
}

void InconsistencyVector::RecalculateInconsistency() {
    this->FindInconsistency();
    this->FindNorm();
}

InconsistencyVector::InconsistencyVector(const InconsistencyVector &source) {
    this->_gaussMatrix = std::make_unique<GaussMatrix>(*source._gaussMatrix);
    this->_inconsistencyVector.resize(source._gaussMatrix->GetRowsNumber());
    this->_initialMatrix = std::make_unique<EquationMatrix>(*source._initialMatrix);

    this->RecalculateInconsistency();
}
