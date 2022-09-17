#pragma once

#include "Matrix.h"

class EquationMatrix {
public:
    explicit EquationMatrix(const Matrix &equationMatrix);

    EquationMatrix(const EquationMatrix &source);

    EquationMatrix &operator=(const EquationMatrix &source);

    void SumRows(const OperableSet &sumSet);

    void SubtractRows(const OperableSet &subtractionSet);

    void MultiplyRow(const uint64_t &targetRowIndex, const double80_t &multiplier);

    void SubtractMultipliedRow(const OperableSet &subtractionSet, const double80_t &multiplier);

    [[nodiscard]] uint64_t GetMaxColumnElementIndex(const uint64_t &columnIndex, const uint64_t &fromRow) const;

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
    std::unique_ptr<Matrix> _leftSide;

    std::unique_ptr<Matrix> _rightSide;
};