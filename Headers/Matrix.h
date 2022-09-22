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
    static void PrintInputMessage(const uint64_t &index) {
        std::cout << "Input lambda" << index << ":";
    }
};


class Matrix {
public:
    explicit Matrix(const uint64_t &rows, const uint64_t &columns);

    explicit Matrix();

    Matrix(const Matrix &source);

    explicit Matrix(const std::filesystem::path &filePath) {
        if (!exists(filePath)) {
            throw (std::invalid_argument("Invalid matrix file path given"));
        }
        std::string line;

        std::ifstream inFile(filePath);
        if (inFile.bad()) {
            throw (std::ios_base::failure("Unknown Stream error occurred"));
        }

        this->_rows = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n') + 1;

        inFile.clear();
        inFile.seekg(0, std::ios::beg);
        getline(inFile, line);
        std::cout << line;

        this->_columns = std::count_if( line.begin(), line.end(), []( char c ){return c == ' ';}) + 1;
        inFile.close();

        this->InitVector(this->_rows, this->_columns);
        this->ReadFromFile(filePath);
    }

    void RandomSymmetricInit(const double80_t &minRandom, const double80_t &maxRandom) {
        std::random_device randomDevice;
        std::mt19937 generate(randomDevice());
        std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j <= i; j++) {
                this->_data[i][j] = distribution(generate);
            }
        }

        *this = *this + this->GetTransposed();
    }

    Matrix &operator=(const Matrix &source);

    Matrix operator*(const Matrix &multiplier) const;

    Matrix operator-(const Matrix &matrixToSubtract) const;

    Matrix operator+(const Matrix &matrixToSubtract) const;

    bool operator==(const Matrix &comparedTo) const;

    void Append(const Matrix &appendSource);

    void Nullify() {
        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                this->operator[](i)[j] = 0.0;
            }
        }
    }

    void InitVector(const uint64_t & rows, const uint64_t & columns) {
        this->_data.resize(rows);

        for (uint64_t i = 0; i < rows; i++) {
            this->_data[i].resize(columns);
        }
    }

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
