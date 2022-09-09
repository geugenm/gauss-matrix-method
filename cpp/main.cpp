#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <ranges>

using double80_t = long double;

class Matrix {
public:
    Matrix() = default;

    explicit Matrix(const uint64_t &rows, const uint64_t &columns) : _rows(rows), _columns(columns) {
        this->_data.resize(rows);

        for (uint64_t i = 0; i < rows; i++) {
            this->_data[i].resize(columns);
        }
    }

    Matrix(const Matrix &source) = default;

    Matrix &operator=(const Matrix &source) = default;

    ~Matrix() = default;

    [[nodiscard]] std::vector<double80_t> const &operator[](const uint64_t &index) const {
        if (index >= _rows) {
            throw (std::out_of_range("Matrix out of range"));
        }
        return this->_data[index];
    }

    [[nodiscard]] std::vector<double80_t> &operator[](const uint64_t &index) {
        if (index >= this->_rows) {
            throw (std::out_of_range("Matrix out of range"));
        }
        return this->_data[index];
    }

    [[nodiscard]] uint64_t GetRowsNumber() const {
        return this->_rows;
    }

    [[nodiscard]] uint64_t GetColumnsNumber() const {
        return this->_columns;
    }

    void SumRows(const uint64_t &rowToSumIndex, const uint64_t &rowToChangeIndex) {
        for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
            this->_data[rowToChangeIndex][i] += this->_data[rowToSumIndex][i];
        }
    }

    void SubstractRows(const uint64_t &rowToSubstractIndex, const uint64_t &rowToChangeIndex) {
        for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
            this->_data[rowToChangeIndex][i] -= this->_data[rowToSubstractIndex][i];
        }
    }

    void MultiplyRowBy(const uint64_t &targetRowIndex, const double80_t &multiplier) {
        for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
            this->_data[targetRowIndex][i] *= multiplier;
        }
    }

    void SubstractMultipliedRow(const uint64_t &rowToSubstractIndex, const uint64_t &rowToChangeIndex,
                                const double80_t &multiplier) {
        for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
            this->_data[rowToChangeIndex][i] -= this->_data[rowToSubstractIndex][i] * multiplier;
        }
    }

    [[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t &columnIndex) {
        uint64_t resultIndex = 0;
        double_t resultMax = 0.0;

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            const double_t currentComparableElement = std::abs(this->_data[i][columnIndex]);

            if (resultMax > currentComparableElement) {
                continue;
            }

            resultMax = currentComparableElement;
            resultIndex = i;
        }

        return resultIndex;
    }

    [[nodiscard]] uint64_t GetMaxRowElementIndex(const uint64_t &rowIndex) {
        const auto maxElementIterator = std::max_element(this->_data[rowIndex].begin(), this->_data[rowIndex].end(),
                                                         [](double_t a, double_t b) {
                                                             return std::abs(a) < std::abs(b);
                                                         });

        return std::distance(this->_data[rowIndex].begin(), maxElementIterator);
    }

    void RandomInit() {
        const double80_t minRandom = 0.0;
        const double80_t maxRandom = 100.0;

        std::random_device randomDevice;
        std::mt19937 generate(randomDevice());
        std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                this->_data[i][j] = distribution(generate);
            }
        }
    }

    void Print() {
        const uint64_t precision = 2;
        const uint64_t width = 7;

        std::cout << std::setprecision(precision);
        std::cout.setf(std::ios::right);
        std::cout.setf(std::ios::fixed);

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                std::cout << std::setw(width) << this->_data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<std::vector<double80_t>> _data{};

    uint64_t _rows = 0;

    uint64_t _columns = 0;
};


class GaussMatrix {
public:
    GaussMatrix() {
        this->_leftSide = std::make_unique<Matrix>(3, 3);
        this->_rightSide = std::make_unique<Matrix>(3, 1);

        this->_leftSide->RandomInit();
        this->_rightSide->RandomInit();
    }

    void FindMaxRowElement(const uint64_t &columnIndex, const uint64_t &comparedTo) {
        const uint64_t maxElementIndex = this->_leftSide->GetMaxColumnElementIndex(columnIndex);
        std::swap(this->_leftSide->operator[](maxElementIndex)[columnIndex],
                  this->_leftSide->operator[](comparedTo)[columnIndex]);
    }

    void Divide() {
        const uint64_t columnsGeneral = this->_leftSide->GetColumnsNumber() + this->_rightSide->GetColumnsNumber();
        const uint64_t rowsGeneral = this->_leftSide->GetRowsNumber();

        this->FindMaxRowElement(0, 0);

        for (uint64_t i = 0; i < rowsGeneral; i++) {
            if (i >= 1) {
                const uint64_t rowToSubstract = i - 1;
                const uint64_t columnToSubstract = i - 1;

                for (uint64_t j = i; j < rowsGeneral; j++) {
                    const double80_t multiplier = this->_leftSide->operator[](j)[columnToSubstract];
                    this->_leftSide->SubstractMultipliedRow(rowToSubstract, j, multiplier);
                    this->_rightSide->SubstractMultipliedRow(rowToSubstract, j, multiplier);
                }
            }

            this->FindMaxRowElement(i, i);

            const double80_t diagonalElement = this->_leftSide->operator[](i)[i];
            this->_leftSide->MultiplyRowBy(i, 1 / diagonalElement);
            this->_rightSide->MultiplyRowBy(i, 1 / diagonalElement);
        }
    }

    void Print() const {
        this->_leftSide->Print();
    }

private:
    std::unique_ptr<Matrix> _leftSide;
    std::unique_ptr<Matrix> _rightSide;
};

int main() {
    GaussMatrix testMatrix;
    testMatrix.Print();

    std::cout << "\n" << std::endl;

    testMatrix.Divide();
    testMatrix.Print();
}