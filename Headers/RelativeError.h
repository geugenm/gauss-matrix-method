#pragma once

#include "InconsistencyVector.h"


class RelativeError {
public:
    explicit RelativeError(const InconsistencyVector &inconsistencyVector, const EquationMatrix &initialMatrix) {
        this->_initialMatrix = std::make_shared<EquationMatrix>(initialMatrix);
        this->_inconsistencyVector = std::make_shared<InconsistencyVector>(inconsistencyVector);

        this->CreateSystem();
        this->SolveTheSystem();
        this->Calculate();
    }

    explicit RelativeError(const InconsistencyVector &inconsistencyVector, const Matrix &initialMatrix) : RelativeError(
            inconsistencyVector, *std::make_unique<EquationMatrix>(initialMatrix)) {

    }

    void CreateSystem() {
        Matrix temp = this->_initialMatrix->GetLeftSide() * this->_inconsistencyVector->GetRootsMatrix();
        std::swap(this->_initialMatrix->GetRightSide(), temp);

    }

    void SolveTheSystem() {
        this->_gaussMatrix = std::make_shared<GaussMatrix>(*this->_initialMatrix);
    }

    [[nodiscard]] static double80_t GetMaxAbsoluteElement(const Matrix &matrix) {
        const uint64_t maxDifferenceIndex = matrix.GetMaxColumnElementIndex(0);
        return std::fabs(matrix[maxDifferenceIndex][0]);
    }

    void Calculate() {
        const Matrix rootsDifference =
                this->_gaussMatrix->GetRootsMatrix() - this->_inconsistencyVector->GetRootsMatrix();

        const double80_t maxAbsoluteDifference = RelativeError::GetMaxAbsoluteElement(rootsDifference);

        const double80_t maxAbsoluteFirstAttemptRootIndex = RelativeError::GetMaxAbsoluteElement(
                this->_inconsistencyVector->GetRootsMatrix());

        this->_relativeError = maxAbsoluteDifference / maxAbsoluteFirstAttemptRootIndex;
    }

    void Print() const {
        std::cout << std::scientific;
        std::cout << "\nMax relative error is: " << this->_relativeError << std::endl;
    }

    ~RelativeError() = default;

private:
    std::shared_ptr<EquationMatrix> _initialMatrix;

    std::shared_ptr<InconsistencyVector> _inconsistencyVector;

    std::shared_ptr<GaussMatrix> _gaussMatrix;

    double80_t _relativeError;
};