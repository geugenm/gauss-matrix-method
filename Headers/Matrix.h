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

struct QualitativeNumbers {
    double80_t lambda1;
    double80_t lambda2;
    double80_t lambda3;

    void ObtainData() {
        PrintInputMessage(1);
        std::cin >> lambda1;

        PrintInputMessage(2);
        std::cin >> lambda2;

        PrintInputMessage(3);
        std::cin >> lambda3;

        std::cout << std::endl;
    }

private:
    static void PrintInputMessage(const uint64_t & index) {
        std::cout << "Input lambda" << index << ":";
    }
};


class Matrix {
public:
    explicit Matrix(const uint64_t &rows, const uint64_t &columns);

    Matrix(const Matrix &source);

    explicit Matrix() : Matrix(3, 4) {
        QualitativeNumbers qualitativeNumbers;
        qualitativeNumbers.ObtainData();

        const double80_t patternAlpha = 2.0 * qualitativeNumbers.lambda1 + qualitativeNumbers.lambda2;
        const double80_t patternBeta = 2.0 * (qualitativeNumbers.lambda1 - qualitativeNumbers.lambda2);

        const double80_t patternGamma = 3.0 * qualitativeNumbers.lambda3;
        const double80_t patternPhi = - 4.0 * qualitativeNumbers.lambda1 + qualitativeNumbers.lambda2;

        const double80_t patternOmega = patternGamma * patternGamma;

        this->_data[0][0] = 2.0 * qualitativeNumbers.lambda1 + 4.0 * qualitativeNumbers.lambda2;
        this->_data[1][0] = patternBeta;
        this->_data[2][0] = patternBeta;

        this->_data[1][0] = patternBeta;
        this->_data[1][1] = patternAlpha + patternGamma;
        this->_data[1][2] = patternAlpha - patternGamma;

        this->_data[2][0] = patternBeta;
        this->_data[2][1] = patternAlpha - patternGamma;
        this->_data[2][2] = patternAlpha + patternGamma;

        this->_data[2][0] = - 2.0 * patternBeta;
        this->_data[2][1] = patternPhi + patternOmega;
        this->_data[2][2] = patternPhi - patternOmega;
    }

    Matrix &operator=(const Matrix &source);

    Matrix operator*(const Matrix &multiplier) const;

    Matrix operator-(const Matrix &matrixToSubtract) const;

    Matrix operator+(const Matrix &matrixToSubtract) const;

    bool operator==(const Matrix & comparedTo);

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

    [[nodiscard]] Matrix GetTransposed() const;

    [[nodiscard]] bool IsSymmetric() const;

private:
    void CheckOperableSet(const OperableSet &operableSet) const;

private:
    std::vector<std::vector<double80_t>> _data;

    uint64_t _rows;
    uint64_t _columns;
};
