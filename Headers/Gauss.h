#pragma once

#include "EquationMatrix.h"


class GaussMatrix {
public:
    // ─── Constructors Section ───────────────────────────────────────────────────────
    explicit GaussMatrix(const Matrix & source);

    GaussMatrix(const GaussMatrix &source);

    // ─── Operators ──────────────────────────────────────────────────────────────────
    GaussMatrix &operator=(const GaussMatrix &source);

    [[nodiscard]] std::vector<double80_t> &operator[](const uint64_t &index);

    [[nodiscard]] std::vector<double80_t> const &operator[](const uint64_t &index) const;

    // ─── Public Methods ─────────────────────────────────────────────────────────────
    [[nodiscard]] double80_t GetRoot(const uint64_t &index) const;

    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    void Print() const;

    void PrintRoots() const;

    ~GaussMatrix() = default;

private:
    void ReplaceDiagonalElementWithTheMaxInTheColumn(const uint64_t &currentColumn);

    void NullifyLowerElementsFrom(const uint64_t &currentRow);

    void MakeDiagonalElementOne(const uint64_t &currentRow);

    void FindSolutionFor(const uint64_t &index);

    void StraightforwardStroke();

    void ReverseStroke();

    void SolveSystem();

    void PrepareFirstElement();;

private:
    std::shared_ptr<EquationMatrix> _equationMatrix;

    std::shared_ptr<Matrix> _roots;
};

