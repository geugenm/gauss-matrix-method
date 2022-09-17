#pragma once

#include "EquationMatrix.h"

/// Theoretical taken from LiveJournal
/// @see https://nabbla1.livejournal.com/245822.html?ysclid=l86e2zh5w1833261875


class LdlMatrix {
public:
    explicit LdlMatrix(const EquationMatrix & matrix) {
        this->_equation = std::make_shared<EquationMatrix>(matrix);

        this->_bottomTriangle = std::make_shared<Matrix>(matrix);
        this->_diagonal = std::make_shared<Matrix>(matrix);
        this->_upperTriangle = std::make_shared<Matrix>(matrix);
    }

    explicit LdlMatrix(const Matrix & matrix) : LdlMatrix(*std::make_shared<EquationMatrix>(matrix)) {
        ;
    }

    [[nodiscard]] uint64_t GetRowsNumber() const {
        return this->_equation->GetRowsNumber();
    }
    [[nodiscard]] uint64_t GetColumnsNumber() const {
        return this->_equation->GetColumnsNumber();
    }

    void InitMatrices() {
        auto isBottomTriangle = [](const uint64_t & currentRow, const uint64_t & currentColumn) {
            return (currentColumn < currentRow);
        };

        auto isDiagonal = [](const uint64_t & currentRow, const uint64_t & currentColumn) {
            return (currentColumn == currentRow);
        };

        auto isUpperTriangle = [](const uint64_t & currentRow, const uint64_t & currentColumn) {
            return (currentColumn > currentRow);
        };

        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetColumnsNumber(); j++) {
                if (isBottomTriangle(i, j)) {
                    this->_upperTriangle->operator[](i)[j] = 0.0;
                    this->_diagonal->operator[](i)[j] = 0.0;
                }

                if (isDiagonal(i, j)) {
                    this->_upperTriangle->operator[](i)[j] = 1.0;
                    this->_bottomTriangle->operator[](i)[j] = 1.0;
                }

                if (isUpperTriangle(i, j)) {
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

private:
    std::shared_ptr<Matrix> _bottomTriangle;
    std::shared_ptr<Matrix> _diagonal;
    std::shared_ptr<Matrix> _upperTriangle;

    std::shared_ptr<EquationMatrix> _equation;
};