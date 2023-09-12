#pragma once

#include "Matrix.h"

class EquationMatrix {
public:
    // ─── Constructors Section ───────────────────────────────────────────────────────
    explicit EquationMatrix(const Matrix &matrix);

    EquationMatrix(const EquationMatrix &source);

    // ─── Operators ──────────────────────────────────────────────────────────────────
    EquationMatrix &operator=(const EquationMatrix &source);

    // ─── Public Methods ─────────────────────────────────────────────────────────────
    void SumRows(OperableSet sumSet);

    void SubtractRows(OperableSet subtractionSet);

    void MultiplyRow(uint64_t targetRowIndex, double80_t multiplier);

    void SubtractMultipliedRow(OperableSet subtractionSet, double80_t multiplier);

    [[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t &columnIndex) const;

    void SwapRows(const uint64_t &firstRow, const uint64_t &secondRow);

    [[nodiscard]] uint64_t GetRowsNumber() const;

    [[nodiscard]] uint64_t GetColumnsNumber() const;

    [[nodiscard]] Matrix &GetLeftSide() const;

    [[nodiscard]] Matrix &GetRightSide() const;

    void Print() const;

    [[nodiscard]] std::vector<double80_t> const &GetRowByIndex(const uint64_t &rowIndex) const;

    [[nodiscard]] std::vector<double80_t> &GetRowByIndex(const uint64_t &rowIndex);

    [[nodiscard]] bool IsEmpty() const;

    ~EquationMatrix() = default;

private:
    std::shared_ptr<Matrix> _leftSide;

    std::shared_ptr<Matrix> _rightSide;
};