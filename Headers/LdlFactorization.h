#pragma once

#include "Gauss.h"

/// Theoretical taken from LiveJournal
/// @see https://nabbla1.livejournal.com/245822.html?ysclid=l86e2zh5w1833261875


class LdlMatrix {
public:
    explicit LdlMatrix(const EquationMatrix &equationMatrix) {
        if (!equationMatrix.GetLeftSide().IsSymmetric()) {
            throw (std::invalid_argument("Matrix should be symmetric in order to proceed LDL factorization"));
        }

        this->_equation = std::make_shared<EquationMatrix>(equationMatrix);

        this->_bottomTriangle = std::make_shared<Matrix>(equationMatrix.GetLeftSide());

        this->_diagonalMatrix = std::make_shared<Matrix>(equationMatrix.GetLeftSide());
        this->_diagonalMatrix->Nullify();

        this->_upperTriangle = std::make_shared<Matrix>(equationMatrix.GetLeftSide());
        this->_upperTriangle->Nullify();

        this->FormMatrices();
    }

    explicit LdlMatrix(const Matrix &matrix) : LdlMatrix(*std::make_unique<EquationMatrix>(matrix)) {
    }

    [[nodiscard]] uint64_t GetRowsNumber() const {
        return this->_equation->GetLeftSide().GetRowsNumber();
    }

    [[nodiscard]] uint64_t GetColumnsNumber() const {
        return this->_equation->GetLeftSide().GetColumnsNumber();
    }

    void FormBottomTriangle() {
        for (uint64_t i = 0; i < this->GetRowsNumber() - 1; i++) {
            for (uint64_t j = i + 1; j < this->GetColumnsNumber(); j++) {
                this->_bottomTriangle->operator[](i)[j] = 0.0;
            }
        }
    }

    [[nodiscard]] double80_t GetAmountOfSomething(const uint64_t &index, const uint64_t &currentRowIndex) {
        double80_t result = 0.0;
        for (uint64_t i = 0; i < currentRowIndex; i++) {
            result += (this->_bottomTriangle->operator[](index)[i]) *
                      (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                      (this->_diagonalMatrix->operator[](i)[i]);
        }

        return result;
    }

    [[nodiscard]] double80_t GetAmountOfSomething1(const uint64_t &currentRowIndex) {
        double80_t result = 0.0;
        for (uint64_t i = 0; i < currentRowIndex; i++) {
            result += (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                      (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                      (this->_diagonalMatrix->operator[](i)[i]);
        }

        return result;
    }

    void CalculateDiagonal(const uint64_t & index) {
            this->_diagonalMatrix->operator[](index)[index] =
                    this->_bottomTriangle->operator[](index)[index] - this->GetAmountOfSomething1(index);

    }

    void CalculateBottomTriangle() {
        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            this->CalculateDiagonal(i);
            this->_bottomTriangle->operator[](i)[i] = 1.0;

            for (uint64_t j = i + 1; j < this->GetRowsNumber(); j++) {
                this->_bottomTriangle->operator[](j)[i] =
                        (this->_bottomTriangle->operator[](j)[i] - this->GetAmountOfSomething(j, i)) /
                        this->_diagonalMatrix->operator[](i)[i];
            }
        }
    }

    void CalculateUpperTriangle() {
        for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
            for (uint64_t j = 0; j < this->GetRowsNumber(); j++) {
                this->_upperTriangle->operator[](i)[j] = this->_bottomTriangle->operator[](j)[i];
            }
        }
    }

    void FormMatrices() {
        this->FormBottomTriangle();
        this->CalculateBottomTriangle();
        this->CalculateUpperTriangle();
    }

    void Print() const {
        this->_bottomTriangle->Print();
        this->_diagonalMatrix->Print();
        this->_upperTriangle->Print();

        (*this->_bottomTriangle * *this->_diagonalMatrix * *this->_upperTriangle).Print();
    }

    void FindSolution() {
        //GaussMatrix ySolution
    }

private:
    std::shared_ptr<Matrix> _bottomTriangle;
    std::shared_ptr<Matrix> _diagonalMatrix;
    std::shared_ptr<Matrix> _upperTriangle;

    std::shared_ptr<EquationMatrix> _equation;
};