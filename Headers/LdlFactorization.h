#pragma once

#include "EquationMatrix.h"

/// Theoretical taken from LiveJournal
/// @see https://nabbla1.livejournal.com/245822.html?ysclid=l86e2zh5w1833261875


class LdlMatrix {
public:
    explicit LdlMatrix(const Matrix & matrix) {
        this->_equation = std::make_shared<Matrix>(matrix);

        this->_bottomTriangle = std::make_shared<Matrix>(matrix);
        this->_diagonal = std::make_shared<Matrix>(matrix);
        this->_upperTriangle = std::make_shared<Matrix>(matrix);
    }

    [[nodiscard]] uint64_t GetRowsNumber() const {
        return this->_equation->GetRowsNumber();
    }
    [[nodiscard]] uint64_t GetColumnsNumber() const {
        return this->_equation->GetColumnsNumber();
    }

    void InitMatrices() {
        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                if (i < j) {
                    this->_upperTriangle->operator[](i)[j] = 0.0;
                    this->_diagonal->operator[](i)[j] = 0.0;
                }

                if (i == j) {
                    this->_upperTriangle->operator[](i)[j] = 1.0;
                    this->_bottomTriangle->operator[](i)[j] = 1.0;
                }

                if (i > j) {
                    this->_diagonal->operator[](i)[j] = 0.0;
                    this->_bottomTriangle->operator[](i)[j] = 0.0;
                }
            }
        }
    }

    [[nodiscard]] Matrix MultiplyResults() {
        const Matrix result = (*this->_bottomTriangle) * (*this->_diagonal) * (*this->_upperTriangle);
        return result;
    }

    [[nodiscard]] Matrix Calculate() {
        Matrix calculatedMultiplication = this->MultiplyResults();
        Matrix result(this->GetRowsNumber(), this->GetColumnsNumber());

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                if (i == j) {
                    result[i][j] = this->_equation->operator[](i)[j];
                }
                if (i < j) {
                    result[i][j] = this->_equation->operator[](i)[j] / calculatedMultiplication[i][i];
                }
            }
        }

        return result;
    }

    void Print() {
        this->InitMatrices();
        this->Calculate().Print();
    }

private:
    std::shared_ptr<Matrix> _bottomTriangle;
    std::shared_ptr<Matrix> _diagonal;
    std::shared_ptr<Matrix> _upperTriangle;

    std::shared_ptr<Matrix> _equation;
};