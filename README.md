# Laboratory work №1 "Gauss equation solving"
All tasks are placed on the portal of my university.

Briefly, the task was to solve systems using special methods:
- Gauss with main element selection
- LDLt factorization for symmetric matrices
Also inconsistency and absolute error were calculated here.

# Requirements
- __Cmake__ minimal version required for `Google Test` is currenty __3.24.2__
- __C++20__ version (Only STL)
- __Windows 11__ (uint64_t was used for sizes)


# Compilation
Just use cmake and select CMakeLists.txt in root directory:
```
mkdir GaussBuild
cd GaussBuild
cmake ..
cmake --build
```

## What tools were used
- Clion 2022.2 (Official Pro)
- Valgrind memcheck for debugging
- Perf-linux profiler on Kali WSL

### Sources
[SYM-ILDL: Incomplete LDLT Factorization of Symmetric Indefinite and Skew-Symmetric Matrices](https://arxiv.org/pdf/1505.07589v1.pdf)
