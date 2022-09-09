#include "Matrix.h"

Matrix::Matrix(const uint64_t &rows, const uint64_t &columns) : _rows(rows), _columns(columns) {
    this->_data.resize(rows);

    for (uint64_t i = 0; i < rows; i++) {
        this->_data[i].resize(columns);
    }
}

std::vector<double80_t> const &Matrix::operator[](const uint64_t &index) const {
    if (index >= _rows) {
        throw (std::out_of_range("Matrix out of range"));
    }
    return this->_data[index];
}

std::vector<double80_t> &Matrix::operator[](const uint64_t &index) {
    if (index >= this->_rows) {
        throw (std::out_of_range("Matrix out of range"));
    }
    return this->_data[index];
}

uint64_t Matrix::GetRowsNumber() const {
    return this->_rows;
}

uint64_t Matrix::GetColumnsNumber() const {
    return this->_columns;
}

void Matrix::SumRows(const uint64_t &rowToSumIndex, const uint64_t &rowToChangeIndex) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[rowToChangeIndex][i] += this->_data[rowToSumIndex][i];
    }
}

void Matrix::SubtractRows(const uint64_t &rowToSubtractIndex, const uint64_t &rowToChangeIndex) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[rowToChangeIndex][i] -= this->_data[rowToSubtractIndex][i];
    }
}

void Matrix::MultiplyRowBy(const uint64_t &targetRowIndex, const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[targetRowIndex][i] *= multiplier;
    }
}

void Matrix::SubtractMultipliedRow(const uint64_t &rowToSubtractIndex, const uint64_t &rowToChangeIndex,
                                   const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[rowToChangeIndex][i] -= this->_data[rowToSubtractIndex][i] * multiplier;
    }
}

uint64_t Matrix::GetMaxColumnElementIndex(const uint64_t &columnIndex) {
    uint64_t resultIndex = 0;
    double80_t resultMax = 0.0;

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        const double80_t currentComparableElement = std::fabs(this->_data[i][columnIndex]);

        if (resultMax > currentComparableElement) {
            continue;
        }

        resultMax = currentComparableElement;
        resultIndex = i;
    }

    return resultIndex;
}

uint64_t Matrix::GetMaxRowElementIndex(const uint64_t &rowIndex) {
    const auto maxElementIterator = std::max_element(this->_data[rowIndex].begin(), this->_data[rowIndex].end(),
                                                     [](double80_t a, double80_t b) {
                                                         return std::fabs(a) < std::fabs(b);
                                                     });

    return std::distance(this->_data[rowIndex].begin(), maxElementIterator);
}

void Matrix::RandomInit(const double80_t & minRandom, const double80_t & maxRandom) {
    std::random_device randomDevice;
    std::mt19937 generate(randomDevice());
    std::uniform_real_distribution<double80_t> distribution(minRandom, maxRandom);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
            this->_data[i][j] = distribution(generate);
        }
    }
}

void Matrix::Print() {
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

    std::cout << std::endl;
}
