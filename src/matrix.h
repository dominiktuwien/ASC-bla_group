//#ifndef FILE_VECTOR_H
//#define FILE_VECTOR_H

#include <iostream>

enum ORDERING { ColMajor, RowMajor };
template <typename T, ORDERING ORD>
    class Matrix {
        size_t row_lenght_;
        size_t col_lenght_;
        T * data_;

    public:
    
    };