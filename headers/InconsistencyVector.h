#pragma once

#include "Gauss.h"


class InconsistencyVector {
public:
    explicit InconsistencyVector(const GaussMatrix &gaussMatrix);

    void RecalculateInconsistency();

    void Print() const;

private:
    [[nodiscard]] double80_t FindRowSum(const uint64_t &targetedRow) const;

    void FindNorm();

    void FindInconsistency();

private:
    std::unique_ptr<GaussMatrix> _gaussMatrix;

    std::vector<double80_t> _inconsistencyVector;

    double80_t _maxError;
};
