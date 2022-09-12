#include "../headers/RelativeError.h"

RelativeError::RelativeError(const InconsistencyVector &inconsistencyVector, const Matrix & initialMatrix) {
    this->_inconsistencyVector = std::make_unique<InconsistencyVector>(inconsistencyVector);
    this->_initialMatrixEquation = std::make_unique<GaussMatrix>(initialMatrix);
}
