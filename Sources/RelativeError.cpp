#include "../headers/RelativeError.h"

/**
 * A constructor for the class RelativeError.
 *
 * @param inconsistencyVector The vector of inconsistencies in the system of equations.
 * @param initialMatrix The matrix that was used to solve the system of equations.
 */
RelativeError::RelativeError(const InconsistencyVector &inconsistencyVector, const EquationMatrix &initialMatrix) {
    this->_initialMatrix = std::make_shared<EquationMatrix>(initialMatrix);
    this->_inconsistencyVector = std::make_shared<InconsistencyVector>(inconsistencyVector);

    this->CreateSystem();
    this->SolveTheSystem();
    this->Calculate();
}

RelativeError::RelativeError(const InconsistencyVector &inconsistencyVector, const Matrix &initialMatrix) : RelativeError(
        inconsistencyVector, *std::make_unique<EquationMatrix>(initialMatrix)) {

}

void RelativeError::CreateSystem() {
    Matrix temporary = this->_initialMatrix->GetLeftSide() * this->_inconsistencyVector->GetRootsMatrix();
    std::swap(this->_initialMatrix->GetRightSide(), temporary);
}

void RelativeError::SolveTheSystem() {
    this->_gaussMatrix = std::make_shared<GaussMatrix>(*this->_initialMatrix);
}

/**
 * It returns the maximum absolute element of a matrix.
 *
 * @param matrix The matrix to get the max absolute element from.
 */
double80_t RelativeError::GetMaxAbsoluteElement(const Matrix &matrix) {
    const uint64_t maxDifferenceIndex = matrix.GetMaxColumnElementIndex(0);
    return std::fabs(matrix[maxDifferenceIndex][0]);
}

void RelativeError::Calculate() {
    const Matrix rootsDifference =
            this->_gaussMatrix->GetRootsMatrix() - this->_inconsistencyVector->GetRootsMatrix();

    const double80_t maxAbsoluteDifference = RelativeError::GetMaxAbsoluteElement(rootsDifference);

    const double80_t maxAbsoluteFirstAttemptRootIndex = RelativeError::GetMaxAbsoluteElement(
            this->_inconsistencyVector->GetRootsMatrix());

    this->_relativeError = maxAbsoluteDifference / maxAbsoluteFirstAttemptRootIndex;
}

/**
 * It prints the relative error in scientific form.
 */
void RelativeError::Print() const {
    std::cout << std::scientific;
    std::cout << "\nMax relative error is: " << this->_relativeError << std::endl;
}
