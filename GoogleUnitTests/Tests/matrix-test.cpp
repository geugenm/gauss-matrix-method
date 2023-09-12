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

int main(int argc, char ** argv, char ** env) {
    std::cout << "Running main() from " << __FILE__ << std::endl;

    std::cout << "Arguments: " << argc - 1 << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << " " << argv[i];
    }
    std::cout << std::endl;

    std::cout << "Environment: " << env << std::endl;

    ::testing::InitGoogleTest();

    std::cout << "Test result: " << testing::UnitTest::GetInstance()->Run() << std::endl;

    std::cin.get();

    return RUN_ALL_TESTS();
}