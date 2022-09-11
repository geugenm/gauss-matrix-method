#pragma once

#include "Matrix.h"


class GaussMatrix {
public:
    explicit GaussMatrix(const Matrix & matrix);

    GaussMatrix(const GaussMatrix & source);

    [[nodiscard]] std::vector<double80_t> & operator[] (const uint64_t & index);

    [[nodiscard]] std::vector<double80_t> const & operator[] (const uint64_t & index) const;

    [[nodiscard]] double80_t GetRoot(const uint64_t & index) const;

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

    ~GaussMatrix() = default;

private:
    std::unique_ptr<Matrix> _matrix;

    std::vector<double80_t> _roots;
};

