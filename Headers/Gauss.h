#pragma once

#include "EquationMatrix.h"


class GaussMatrix {
public:
    explicit GaussMatrix(const Matrix & source);

    explicit GaussMatrix(const EquationMatrix &matrix);

    GaussMatrix(const GaussMatrix &source);

    GaussMatrix &operator=(const GaussMatrix &source);

    [[nodiscard]] std::vector<double80_t> &operator[](const uint64_t &index);

    [[nodiscard]] std::vector<double80_t> const &operator[](const uint64_t &index) const;

    [[nodiscard]] double80_t GetRoot(const uint64_t &index) const;

    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    void PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo);

    void NullifyLowerElementsFrom(const uint64_t &currentRow);

    void MakeDiagonalElementOne(const uint64_t &currentRow);

    void FindSolutionFor(const uint64_t &index);

    void StraightforwardStroke();

    void ReverseStroke();

    void Print() const;

    void PrintRoots() const;

    void SolveSystem();

    ~GaussMatrix() = default;

private:
    std::shared_ptr<EquationMatrix> _equationMatrix;

    std::shared_ptr<Matrix> _roots;
};

