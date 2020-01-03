cmake_minimum_required(VERSION 3.14)
project(PrimeFiniteField)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=corei7 -fopenmp")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable(PrimeFiniteField main.cpp include/FFp.h tests/FFprimeTest.cpp)
target_link_libraries (PrimeFiniteField Eigen3::Eigen)