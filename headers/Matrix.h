#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using double80_t = long double;


class Matrix {
public:
    explicit Matrix(const uint64_t &rows, const uint64_t &columns);

    Matrix(const Matrix &source) = default;

    Matrix &operator=(const Matrix &source) = default;

    ~Matrix() = default;

    [[nodiscard]] std::vector<double80_t> const &operator[](const uint64_t &index) const;

    [[nodiscard]] std::vector<double80_t> &operator[](const uint64_t &index);

    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    void SumRows(const uint64_t &rowToSumIndex, const uint64_t &rowToChangeIndex);

    void SubtractRows(const uint64_t &rowToSubtractIndex, const uint64_t &rowToChangeIndex);

    void MultiplyRowBy(const uint64_t &targetRowIndex, const double80_t &multiplier);

    void SubtractMultipliedRow(const uint64_t &rowToSubtractIndex, const uint64_t &rowToChangeIndex,
                               const double80_t &multiplier);

    [[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t &columnIndex);

    [[nodiscard]] uint64_t GetMaxRowElementIndex(const uint64_t &rowIndex);

    void RandomInit(const double80_t & minRandom, const double80_t & maxRandom);

    void Print();

private:
    std::vector<std::vector<double80_t>> _data;

    uint64_t _rows;
    uint64_t _columns;
};
