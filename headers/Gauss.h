#pragma once

#include "Matrix.h"


class GaussMatrix {
public:
    GaussMatrix();

    explicit GaussMatrix(const Matrix & matrix);

    void PlaceMaxElementOnRow(const uint64_t &columnIndex, const uint64_t &comparedTo, const uint64_t & fromRow);

    void InconsistencyVector() const;

    void NullifyLowerElementsFrom(const uint64_t &currentRow);

    void MakeDiagonalElementOne(const uint64_t &currentRow);

    void FindSolutionFor(const uint64_t &index);

    void StraightforwardStroke();

    void ReverseStroke();

    void Print() const;

    void PrintRoots() const;

    static void FindNorm(const std::vector<double80_t> & inconsistency) ;

    ~GaussMatrix() = default;

private:
    std::unique_ptr<Matrix> _matrix;

    std::vector<double80_t> _roots;
};

