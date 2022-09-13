#pragma once

#include "InconsistencyVector.h"


class RelativeError {
public:
    explicit RelativeError(const InconsistencyVector &inconsistencyVector, const Matrix &initialMatrix);

    void PrepareSystem() {
        const uint64_t columnsNumber = this->_initialMatrixEquation->GetColumnsNumber();

        for (uint64_t i = 0; i < columnsNumber; i++) {
            this->_initialMatrixEquation->operator[](i)[columnsNumber - 1] = this->_inconsistencyVector->FindRowSum(i);
        }
    };

    void SolveInconsistentEquation() {
        this->_initialMatrixEquation->SolveSystem();
    }

    [[nodiscard]] double80_t FindMaxFirstRoot() const {
        std::vector<double80_t> firstMaxRoot;

        for (uint64_t i = 0; i < this->_initialMatrixEquation->GetRowsNumber(); i++) {
            firstMaxRoot.push_back(this->_initialMatrixEquation->GetRoot(i));
        }

        const double80_t maxInconsistencyValue = *std::max_element(firstMaxRoot.begin(), firstMaxRoot.end(),
                                                                   [](double80_t a, double80_t b) {
                                                                       return std::fabs(a) < std::fabs(b);
                                                                   });

        return maxInconsistencyValue;
    }

    [[nodiscard]] double80_t FindMaxDifference() const {
        std::vector<double80_t> difference;
        for (uint64_t i = 0; i < this->_initialMatrixEquation->GetRowsNumber(); i++) {
            difference.push_back(this->_initialMatrixEquation->GetRoot(i) - this->_inconsistencyVector->GetRoot(i));
        }

        const double80_t maxInconsistencyValue = *std::max_element(difference.begin(), difference.end(),
                                                                   [](double80_t a, double80_t b) {
                                                                       return std::fabs(a) < std::fabs(b);
                                                                   });

        return maxInconsistencyValue;
    }

    void Print() const {
        std::cout << "\n Relative Error:" << this->FindMaxDifference() / this->FindMaxFirstRoot() << std::endl;
    }

private:
    std::unique_ptr<InconsistencyVector> _inconsistencyVector;

    std::unique_ptr<GaussMatrix> _initialMatrixEquation;
};