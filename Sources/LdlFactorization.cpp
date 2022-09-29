//
// Created by gleba on 9/17/2022.
//

#include "../Headers/LdlFactorization.h"

/**
 * A constructor for the LdlMatrix class.
 *
 * @param equationMatrix The equation matrix that we want to factorize.
 */
LdlMatrix::LdlMatrix(const EquationMatrix &equationMatrix) {
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

LdlMatrix::LdlMatrix(const Matrix &matrix) : LdlMatrix(*std::make_unique<EquationMatrix>(matrix)) {
}

uint64_t LdlMatrix::GetRowsNumber() const {
    return this->_equation->GetLeftSide().GetRowsNumber();
}

uint64_t LdlMatrix::GetColumnsNumber() const {
    return this->_equation->GetLeftSide().GetColumnsNumber();
}

Matrix LdlMatrix::GetLdltMatrix() const {
    return *this->_bottomTriangle * *this->_diagonalMatrix * *this->_upperTriangle;
}

void LdlMatrix::Print() const {
    GaussMatrix result = this->GetSolution();

    std::cout << std::fixed;
    std::cout.precision(2);
    result.Print();

    InconsistencyVector inconsistencyVector(result, *this->_equation);
    inconsistencyVector.Print();

    RelativeError relativeError(inconsistencyVector, *this->_equation);
    relativeError.Print();
}

void LdlMatrix::FormBottomTriangle() {
    for (uint64_t i = 0; i < this->GetRowsNumber() - 1; i++) {
        for (uint64_t j = i + 1; j < this->GetColumnsNumber(); j++) {
            this->_bottomTriangle->operator[](i)[j] = 0.0;
        }
    }
}

double80_t LdlMatrix::GetBottomRowSum(const uint64_t &index, const uint64_t &currentRowIndex) {
    double80_t result = 0.0;
    for (uint64_t i = 0; i < currentRowIndex; i++) {
        result += (this->_bottomTriangle->operator[](index)[i]) *
                  (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                  (this->_diagonalMatrix->operator[](i)[i]);
    }

    return result;
}

double80_t LdlMatrix::GetDiagonalRowSum(const uint64_t &currentRowIndex) {
    double80_t result = 0.0;
    for (uint64_t i = 0; i < currentRowIndex; i++) {
        result += (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                  (this->_bottomTriangle->operator[](currentRowIndex)[i]) *
                  (this->_diagonalMatrix->operator[](i)[i]);
    }

    return result;
}

void LdlMatrix::CalculateDiagonal(const uint64_t &index) {
    this->_diagonalMatrix->operator[](index)[index] =
            this->_bottomTriangle->operator[](index)[index] - this->GetDiagonalRowSum(index);

}

void LdlMatrix::CalculateBottomTriangle() {
    for (uint64_t i = 0; i < this->GetRowsNumber(); i++) {
        this->CalculateDiagonal(i);
        this->_bottomTriangle->operator[](i)[i] = 1.0;

        for (uint64_t j = i + 1; j < this->GetRowsNumber(); j++) {
            this->_bottomTriangle->operator[](j)[i] =
                    (this->_bottomTriangle->operator[](j)[i] - this->GetBottomRowSum(j, i)) /
                    this->_diagonalMatrix->operator[](i)[i];
        }
    }
}

void LdlMatrix::CalculateUpperTriangle() {
    this->_upperTriangle = std::make_shared<Matrix>(this->_bottomTriangle->GetTransposed());
}

void LdlMatrix::FormMatrices() {
    this->FormBottomTriangle();
    this->CalculateBottomTriangle();
    this->CalculateUpperTriangle();
}

GaussMatrix LdlMatrix::GetSolvedBottomEquation() const {
    Matrix equation = *this->_bottomTriangle;
    equation.Append(this->_equation->GetRightSide());

    return GaussMatrix(equation);
}

GaussMatrix LdlMatrix::GetSolvedDiagonalEquation(const GaussMatrix &solvedBottomEquation) const {
    Matrix diagonalMatrixEquation = *this->_diagonalMatrix;
    diagonalMatrixEquation.Append(solvedBottomEquation.GetRootsMatrix());

    return GaussMatrix(diagonalMatrixEquation);
}

GaussMatrix LdlMatrix::GetSolvedUpperEquation(const GaussMatrix &solvedDiagonalEquation) const {
    Matrix upperTriangleMatrixEquation = *this->_upperTriangle;
    upperTriangleMatrixEquation.Append(solvedDiagonalEquation.GetRootsMatrix());

    return GaussMatrix(upperTriangleMatrixEquation);
}

GaussMatrix LdlMatrix::GetSolution() const {
    GaussMatrix bottomEquation = this->GetSolvedBottomEquation();
    GaussMatrix diagonalEquation = this->GetSolvedDiagonalEquation(bottomEquation);
    GaussMatrix upperEquation = this->GetSolvedUpperEquation(diagonalEquation);

    return upperEquation;
}