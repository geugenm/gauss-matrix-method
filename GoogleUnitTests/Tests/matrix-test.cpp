#include "gtest/gtest.h"
#include "../../Headers/Matrix.h"
#include "../../Headers/Gauss.h"
#include "../../Headers/InconsistencyVector.h"
#include "../../Headers/RelativeError.h"

class MatrixTest : public ::testing::Test {
public:
    MatrixTest() {
        // initialization;
        // can also be done in SetUp()
    }

    void SetUp() {
        // initialization or some code to run before each test
        ASSERT_FALSE(false);
    }

    void TearDown() {
        // code to run after each test;
        // can be used instead of a destructor,
        // but exceptions can be handled in this function only
    }

    ~MatrixTest() {
        //resources cleanup, no exceptions allowed
    }

    // shared user data
};