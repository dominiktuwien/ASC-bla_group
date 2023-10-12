cmake_minimum_required(VERSION 3.20)
project(ASC_bla)

set (CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable (test_matrix tests/test_matrix.cc)
target_sources (test_matrix PUBLIC src/Matrix-Neu-Expression.h src/expression.h)

add_executable (test_matrix tests/test_matrix.cc)
target_sources (test_matrix PUBLIC src/matrix.h src/expression.h)




