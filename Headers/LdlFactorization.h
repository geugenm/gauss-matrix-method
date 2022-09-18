#pragma once

#include "Gauss.h"

/// Theoretical taken from LiveJournal
/// @see https://nabbla1.livejournal.com/245822.html?ysclid=l86e2zh5w1833261875


class LdlMatrix {
public:
    explicit LdlMatrix(const EquationMatrix & matrix) {
        if (!matrix.GetLeftSide().IsSymmetric()) {
            throw (std::invalid_argument("Matrix should be symmetric in order to proceed LDL factorization"));
        }

        this->_equation = std::make_shared<EquationMatrix>(matrix);

        this->_bottomTriangle = std::make_shared<Matrix>(matrix.GetLeftSide());
    }

    explicit LdlMatrix(const Matrix & matrix) : LdlMatrix(*std::make_unique<EquationMatrix>(matrix)) {

    }


private:
    std::shared_ptr<Matrix> _bottomTriangle;

    std::shared_ptr<EquationMatrix> _equation;
};