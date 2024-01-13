#ifndef FILE_MAT_VEC_DECL_H
#define FILE_MAT_VEC_DECL_H

#include <cmath>

// *Forward declarations* for matrix and vector header files.
// Avoids necessity to mutually include header files leading to recursive file call.
// Classes can be used without details about how they work.

namespace ASC_bla
{
    enum ORDERING { ColMajor, RowMajor };

    template <typename T=double, typename TDIST = std::integral_constant<size_t,1> >
    class VectorView;

    template <typename T=double, ORDERING ORD = ORDERING::RowMajor> // T=double to make Matrix<> work (instead of Matrix<double>)
    class MatrixView;
}

#endif