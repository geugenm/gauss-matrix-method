#include "gtest/gtest.h"
#include "../../Headers/LdlFactorization.h"

TEST(MatrixTestLdl, test1) {
    Matrix initialMatrix(15, 15);
    initialMatrix.RandomSymmetricInit(-100.0, 100.0);

    Matrix equationPart(initialMatrix.GetRowsNumber(), 1);
    equationPart.RandomInit(-100.0, 100.0);

    initialMatrix.Append(equationPart);

    EquationMatrix equationMatrix(initialMatrix);

    GaussMatrix solvedGaussMatrix(equationMatrix);

    InconsistencyVector inconsistencyVector(solvedGaussMatrix, initialMatrix);

    const bool isAdequateInconsistency = inconsistencyVector.GetMaxAbsoluteInconsistency() <= 1e-10;
    ASSERT_TRUE(isAdequateInconsistency);

    RelativeError relativeError(inconsistencyVector, initialMatrix);

    if (equationMatrix.GetLeftSide().IsSymmetric()) {
        LdlMatrix ldlMatrix(initialMatrix);
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}