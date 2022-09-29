project(Google_tests)
cmake_minimum_required(VERSION 3.24.2)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run Tests/matrix-test.cpp ../../Headers/Matrix.h ../../Sources/Matrix.cpp ../../Sources/Gauss.cpp ../../Headers/Gauss.h ../../Sources/EquationMatrix.cpp ../../Headers/EquationMatrix.h
        ../../Sources/InconsistencyVector.cpp ../../Headers/InconsistencyVector.h ../../Sources/RelativeError.cpp ../../Headers/RelativeError.h ../../Sources/LdlFactorization.cpp ../../Headers/LdlFactorization.h)

target_link_libraries(Google_Tests_run gtest gtest_main)