#pragma once

#include "Gauss.h"


class InconsistencyVector {
public:
    InconsistencyVector(const InconsistencyVector &source);

    explicit InconsistencyVector(const GaussMatrix &gaussMatrix);

    void RecalculateInconsistency();

    void Print() const;

    [[nodiscard]] double80_t GetRoot(const uint64_t &rowIndex) const;

    [[nodiscard]] double80_t FindRowSum(const uint64_t &targetedRow) const;

    ~InconsistencyVector() = default;

private:
    void FindNorm();

    void FindInconsistency();

private:
    std::unique_ptr<GaussMatrix> _gaussMatrix;

    std::vector<double80_t> _inconsistencyVector;

    double80_t _maxAbsoluteInconsistency;
};
