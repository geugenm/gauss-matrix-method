#pragma once

#include "InconsistencyVector.h"


class RelativeError {
public:
    // ─── Constructors Section ───────────────────────────────────────────────────────
    explicit RelativeError(const InconsistencyVector &inconsistencyVector, const EquationMatrix &initialMatrix);

    explicit RelativeError(const InconsistencyVector &inconsistencyVector, const Matrix &initialMatrix);

    // ─── Public Methods ─────────────────────────────────────────────────────────────
    void CreateSystem();

    void SolveTheSystem();

    [[nodiscard]] static double80_t GetMaxAbsoluteElement(const Matrix &matrix);

    void Calculate();

    void Print() const;

    ~RelativeError() = default;

private:
    std::shared_ptr<EquationMatrix> _initialMatrix;

    std::shared_ptr<InconsistencyVector> _inconsistencyVector;

    std::shared_ptr<GaussMatrix> _gaussMatrix;

    double80_t _relativeError{};
};