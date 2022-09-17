#include "../Headers/EquationMatrix.h"

EquationMatrix::EquationMatrix(const Matrix &matrix) {
    if (matrix.IsEmpty()) {
        throw (std::invalid_argument("Source matrix is empty"));
    }

    constexpr uint64_t rowsAndColumnsDifference = 1;
    if (matrix.GetColumnsNumber() != matrix.GetRowsNumber() + rowsAndColumnsDifference) {
        throw (std::invalid_argument(
                "Matrix columns and rows should differ by " + std::to_string(rowsAndColumnsDifference)));
    }

    this->_leftSide = std::make_unique<Matrix>(matrix.GetRowsNumber(),
                                               matrix.GetColumnsNumber() - 1);
    this->_rightSide = std::make_unique<Matrix>(matrix.GetRowsNumber(), 1);

    for (uint64_t i = 0; i < this->_leftSide->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->_leftSide->GetColumnsNumber(); j++) {
            this->_leftSide->operator[](i)[j] = matrix[i][j];
        }
        this->_rightSide->operator[](
                i)[0] = matrix[i][matrix.GetColumnsNumber() - 1];
    }
}

EquationMatrix::EquationMatrix(const EquationMatrix &source) {
    if (source.IsEmpty()) {
        throw (std::invalid_argument("EquationMatrix source is empty"));
    }
    this->_leftSide = std::make_unique<Matrix>(*source._leftSide);
    this->_rightSide = std::make_unique<Matrix>(*source._rightSide);
}

EquationMatrix &EquationMatrix::operator=(const EquationMatrix &source) {
    this->_leftSide = std::make_unique<Matrix>(*source._leftSide);
    this->_rightSide = std::make_unique<Matrix>(*source._rightSide);
    return *this;
}

void EquationMatrix::SumRows(const OperableSet &sumSet) {
    this->_leftSide->SumRows(sumSet);
    this->_rightSide->SumRows(sumSet);
}

void EquationMatrix::SubtractRows(const OperableSet &subtractionSet) {
    this->_leftSide->SubtractRows(subtractionSet);
    this->_rightSide->SubtractRows(subtractionSet);
}

void EquationMatrix::MultiplyRow(const uint64_t &targetRowIndex, const double80_t &multiplier) {
    this->_leftSide->MultiplyRow(targetRowIndex, multiplier);
    this->_rightSide->MultiplyRow(targetRowIndex, multiplier);
}

void EquationMatrix::SubtractMultipliedRow(const OperableSet &subtractionSet, const double80_t &multiplier) {
    this->_leftSide->SubtractMultipliedRow(subtractionSet, multiplier);
    this->_rightSide->SubtractMultipliedRow(subtractionSet, multiplier);
}

uint64_t EquationMatrix::GetMaxColumnElementIndex(const uint64_t &columnIndex) const {
    if (columnIndex >= this->_leftSide->GetColumnsNumber() + this->_rightSide->GetColumnsNumber()) {
        throw (std::out_of_range("Out of column range"));
    }

    if (columnIndex >= this->_leftSide->GetRowsNumber()) {
        throw (std::out_of_range("Out of row range"));
    }

    if (columnIndex >= this->_leftSide->GetColumnsNumber()) {
        return this->_rightSide->GetMaxColumnElementIndex(0);
    }

    if (columnIndex < this->_leftSide->GetColumnsNumber()) {
        return this->_leftSide->GetMaxColumnElementIndex(columnIndex);
    }

    throw (std::logic_error("GetMaxColumnElementIndex : Unknown error in equation"));
}

void EquationMatrix::SwapRows(const uint64_t &firstRow, const uint64_t &secondRow) {
    if (firstRow >= this->_leftSide->GetRowsNumber() || secondRow >= this->_rightSide->GetRowsNumber()) {
        throw (std::out_of_range("Given rows to swap are out of matrix range"));
    }
    std::swap(this->_leftSide->operator[](firstRow), this->_leftSide->operator[](secondRow));
    std::swap(this->_rightSide->operator[](firstRow), this->_rightSide->operator[](secondRow));
}

uint64_t EquationMatrix::GetRowsNumber() const {
    return this->_leftSide->GetRowsNumber();
}

uint64_t EquationMatrix::GetColumnsNumber() const {
    return this->_leftSide->GetColumnsNumber() + this->_rightSide->GetColumnsNumber();
}

Matrix &EquationMatrix::GetLeftSide() const {
    return *this->_leftSide;
}

Matrix &EquationMatrix::GetRightSide() const {
    return *this->_rightSide;
}

void EquationMatrix::Print() const {
    const uint64_t precision = 2;
    const uint64_t width = 7;

    std::cout.setf(std::ios::right);
    std::cout.setf(std::ios::fixed);

    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        for (uint64_t j = 0; j < this->_leftSide->GetColumnsNumber(); j++) {
            std::cout << std::setw(width) << this->_leftSide->operator[](i)[j] << " ";
        }
        std::cout << " =" << std::setw(width) << this->_rightSide->operator[](i)[0] << std::endl;
    }

    std::cout << std::endl;
}

std::vector<double80_t> const &EquationMatrix::GetRowByIndex(const uint64_t &rowIndex) const {
    if (rowIndex >= this->GetColumnsNumber()) {
        throw (std::out_of_range("Out of range row given"));
    }

    if (rowIndex >= this->_leftSide->GetRowsNumber()) {
        return this->_rightSide->operator[](rowIndex);
    }

    if (rowIndex < this->_leftSide->GetRowsNumber()) {
        return this->_leftSide->operator[](rowIndex);
    }

    throw (std::logic_error("Unknown EquationMatrix GetRowByIndex error"));
}

std::vector<double80_t> &EquationMatrix::GetRowByIndex(const uint64_t &rowIndex) {
    if (rowIndex >= this->GetColumnsNumber()) {
        throw (std::out_of_range("Out of range row given"));
    }

    if (rowIndex >= this->_leftSide->GetRowsNumber()) {
        return this->_rightSide->operator[](rowIndex);
    }

    if (rowIndex < this->_leftSide->GetRowsNumber()) {
        return this->_leftSide->operator[](rowIndex);
    }

    throw (std::logic_error("Unknown EquationMatrix GetRowByIndex error"));
}

bool EquationMatrix::IsEmpty() const {
    return this->_leftSide->IsEmpty() || this->_rightSide->IsEmpty();
}
