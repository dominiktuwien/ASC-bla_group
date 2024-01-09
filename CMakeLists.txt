cmake_minimum_required(VERSION 3.20)
project(ASC_bla)

set (CMAKE_CXX_STANDARD 17)

include_directories(src)

find_package(Python 3.8 COMPONENTS Interpreter Development REQUIRED)

execute_process(
  COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PYBIND11_DIR)
list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_DIR}")
find_package(pybind11 CONFIG REQUIRED)


add_executable (test_vector tests/test_vector.cc)
target_sources (test_vector PUBLIC src/vector.h src/expression.h)

#if(WIN32)
#   file (DOWNLOAD https://sourceforge.net/projects/openblas/files/v0.3.24/OpenBLAS-0.3.24-x64.zip/download "${CMAKE_BINARY_DIR}/openblas.zip" EXPECTED_MD5 fc08fe8c0dc7364da115d0e09b5a134f)
#   file (ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/openblas.zip DESTINATION ${CMAKE_BINARY_DIR}/openblas)
#   set(BLA_STATIC ON)
#   set(BLAS_LIBRARIES ${CMAKE_BINARY_DIR}/openblas/lib/libopenblas.a CACHE PATH "BLAS" FORCE)
#   set(LAPACK_LIBRARIES ${CMAKE_BINARY_DIR}/openblas/lib/libopenblas.a CACHE PATH "LAPACK" FORCE)
#endif()

#add_executable (linkertest tests/testlink.cc src/taskmanager.cc src/timer.cc)
#target_sources (linkertest PUBLIC src/Matrix-Neu-using_expressions.h ASC-HPC_physics_group/src/taskmanager.h)

add_executable (test_matrix tests/test_matrix.cc src/taskmanager.cc src/timer.cc)
target_sources (test_matrix PUBLIC src/Matrix-Neu-using_expressions.h src/matexpression.h)


#find_package(LAPACK REQUIRED)
#add_executable (test_lapack tests/test_lapack.cc)
#target_link_libraries (test_lapack PUBLIC ${LAPACK_LIBRARIES})


#pybind11_add_module(bla src/bind_bla.cpp)

#install (TARGETS bla DESTINATION ASCsoft)
#install (FILES src/vector.h DESTINATION ASCsoft/include)


