#pragma once

#include "RelativeError.h"

/// Theoretical taken from LiveJournal
/// @see https://nabbla1.livejournal.com/245822.html?ysclid=l86e2zh5w1833261875
/// Also there is an additional theoretical source
/// @see https://arxiv.org/pdf/1505.07589v1.pdf


class LdlMatrix {
public:
    // ─── Constructors Section ───────────────────────────────────────────────────────
    explicit LdlMatrix(const EquationMatrix &equationMatrix);

    explicit LdlMatrix(const Matrix &matrix);

    // ─── Public Methods ─────────────────────────────────────────────────────────────
    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    [[nodiscard]] GaussMatrix GetSolution() const;

    [[nodiscard]] Matrix GetLdltMatrix() const;

    void Print() const;

    ~LdlMatrix() = default;

private:
    void FormBottomTriangle();

    [[nodiscard]] double80_t GetBottomRowSum(const uint64_t &index, const uint64_t &currentRowIndex);

    [[nodiscard]] double80_t GetDiagonalRowSum(const uint64_t &currentRowIndex);

    [[nodiscard]] GaussMatrix GetSolvedBottomEquation() const;

    [[nodiscard]] GaussMatrix GetSolvedDiagonalEquation(const GaussMatrix & solvedBottomEquation) const;

    [[nodiscard]] GaussMatrix GetSolvedUpperEquation(const GaussMatrix & solvedDiagonalEquation) const;

    void CalculateDiagonal(const uint64_t & index);

    void CalculateBottomTriangle();

    void CalculateUpperTriangle();

    void FormMatrices();

private:
    std::shared_ptr<Matrix> _bottomTriangle;
    std::shared_ptr<Matrix> _diagonalMatrix;
    std::shared_ptr<Matrix> _upperTriangle;

    std::shared_ptr<EquationMatrix> _equation;
};