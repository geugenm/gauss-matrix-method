#include "Matrix.h"

Matrix::Matrix(const uint64_t &rows, const uint64_t &columns) : _rows(rows), _columns(columns) {
    this->_data.resize(rows);

    for (uint64_t i = 0; i < rows; i++) {
        this->_data[i].resize(columns);
    }
}

std::vector<double80_t> const &Matrix::operator[](const uint64_t &index) const {
    if (index >= this->GetRowsNumber()) {
        throw (std::out_of_range("Matrix out of range"));
    }
    return this->_data[index];
}

std::vector<double80_t> &Matrix::operator[](const uint64_t &index) {
    if (index >= this->GetRowsNumber()) {
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

void Matrix::SumRows(const OperableSet &sumSet) {
    this->CheckOperableSet(sumSet);

    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[sumSet.modifiableIndex][i] += this->_data[sumSet.operableIndex][i];
    }
}

void Matrix::SubtractRows(const OperableSet &subtractionSet) {
    this->CheckOperableSet(subtractionSet);

    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[subtractionSet.modifiableIndex][i] -= this->_data[subtractionSet.operableIndex][i];
    }
}

void Matrix::MultiplyRow(const uint64_t &targetRowIndex, const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[targetRowIndex][i] *= multiplier;
    }
}

void Matrix::SubtractMultipliedRow(const OperableSet &subtractionSet, const double80_t &multiplier) {
    for (uint64_t i = 0; i < this->GetColumnsNumber(); i++) {
        this->_data[subtractionSet.modifiableIndex][i] -= this->_data[subtractionSet.operableIndex][i] * multiplier;
    }
}

uint64_t Matrix::GetMaxColumnElementIndex(const uint64_t &columnIndex, const uint64_t & fromRow) {
    uint64_t resultIndex = 0;
    double80_t resultMax = 0.0;

    for (uint64_t i = fromRow; i < this->GetRowsNumber(); i++) {
        const double80_t currentComparableElement = std::abs(this->_data[i][columnIndex]);

        if (resultMax > currentComparableElement) {
            continue;
        }

        resultMax = currentComparableElement;
        resultIndex = i;
    }

    return resultIndex;
}

void Matrix::RandomInit(const double80_t &minRandom, const double80_t &maxRandom) {
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

void Matrix::CheckOperableSet(const OperableSet &operableSet) const {
    if (operableSet.operableIndex >= this->GetRowsNumber() || operableSet.modifiableIndex >= this->GetRowsNumber()) {
        throw (std::out_of_range("Given index set is out of Matrix range"));
    }
}

Matrix &Matrix::operator*(const Matrix & multiplier) {
    Matrix result(this->GetRowsNumber(), multiplier.GetColumnsNumber());

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < multiplier.GetColumnsNumber(); j++) {
            for(uint64_t k = 0; k < multiplier.GetRowsNumber(); k++) {
                result[i][j] += this->operator[](i)[k] * multiplier[k][j];
            }
        }
    }
}
