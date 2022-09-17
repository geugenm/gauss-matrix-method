#pragma once

#include "Gauss.h"


class InconsistencyVector {
public:
    InconsistencyVector(const InconsistencyVector &source);

    explicit InconsistencyVector(const GaussMatrix &gaussMatrix, const Matrix &matrix);

    void Print() const;

    [[nodiscard]] Matrix GetRootsMatrix() const;

    ~InconsistencyVector() = default;

private:
    void FindNorm();

    void FindInconsistency();

    void CalculateInconsistency();

private:
    std::shared_ptr<Matrix> _gaussRoots;

    std::shared_ptr<EquationMatrix> _initialMatrix;

    std::shared_ptr<Matrix> _inconsistencyVector;

    double80_t _maxAbsoluteInconsistency;
};
