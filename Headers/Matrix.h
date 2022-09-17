#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>

using double80_t = long double;

struct OperableSet {
    uint64_t modifiableIndex;
    uint64_t operableIndex;
};

class Matrix {
public:
    explicit Matrix(const uint64_t &rows, const uint64_t &columns);

    Matrix(const Matrix &source);

    Matrix &operator=(const Matrix &source);

    Matrix operator*(const Matrix &multiplier) const;

    Matrix operator-(const Matrix &matrixToSubtract) const;

    Matrix operator+(const Matrix &matrixToSubtract) const;

    void Append(const Matrix &appendSource);

    void ReadFromFile(const std::filesystem::path &filePath);

    [[nodiscard]] bool IsEmpty() const;

    ~Matrix() = default;

    [[nodiscard]] std::vector<double80_t> const &operator[](const uint64_t &index) const;

    [[nodiscard]] std::vector<double80_t> &operator[](const uint64_t &index);

    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    void SumRows(const OperableSet &sumSet);

    void SubtractRows(const OperableSet &subtractionSet);

    void MultiplyRow(const uint64_t &targetRowIndex, const double80_t &multiplier);

    void SubtractMultipliedRow(const OperableSet &subtractionSet, const double80_t &multiplier);

    [[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t &columnIndex) const;

    void RandomInit(const double80_t &minRandom, const double80_t &maxRandom);

    void Print() const;

private:
    void CheckOperableSet(const OperableSet &operableSet) const;

private:
    std::vector<std::vector<double80_t>> _data;

    uint64_t _rows;
    uint64_t _columns;
};
