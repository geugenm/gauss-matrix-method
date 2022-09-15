cmake_minimum_required(VERSION 3.23)
project(lab_1)

set(CMAKE_CXX_STANDARD 23)

## Task related files
add_executable(lab_1
        main.cpp Headers/Matrix.h Sources/Matrix.cpp Sources/Gauss.cpp Headers/Gauss.h Sources/InconsistencyVector.cpp Headers/InconsistencyVector.h Sources/RelativeError.cpp Headers/RelativeError.h)

add_subdirectory(GoogleUnitTests)