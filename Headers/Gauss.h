#pragma once

#include "EquationMatrix.h"


class GaussMatrix {
public:
    // ─── Constructors Section ───────────────────────────────────────────────────────
    explicit GaussMatrix(const Matrix & source);

    explicit GaussMatrix(const EquationMatrix & source);

    GaussMatrix(const GaussMatrix &source);

    // ─── Operators ──────────────────────────────────────────────────────────────────
    GaussMatrix &operator=(const GaussMatrix &source);

    [[nodiscard]] std::vector<double80_t> &operator[](uint64_t index);

    [[nodiscard]] std::vector<double80_t> const &operator[](uint64_t index) const;

    // ─── Public Methods ─────────────────────────────────────────────────────────────
    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    [[nodiscard]] EquationMatrix GetEquationMatrix() const;

    void Print() const;

    [[nodiscard]] Matrix & GetRootsMatrix() const;

    ~GaussMatrix() = default;

private:
    void SwapRowToMaxInTheColumn(uint64_t currentColumn);

    void NullifyLowerElementsFrom(uint64_t currentRow);

    void MakeDiagonalElementOne(uint64_t currentRow);

    void FindSolutionFor(uint64_t index);

    void StraightforwardStroke();

    void ReverseStroke();

    void SolveSystem();

    void PrintRoots() const;

private:
    std::shared_ptr<EquationMatrix> _equationMatrix;

    std::shared_ptr<Matrix> _roots;
};

