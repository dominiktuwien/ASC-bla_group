#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

enum ORDERING { ColMajor, RowMajor };
template <typename T, ORDERING ORD>
    class Matrix {
        std::Vector(T) data_;
        size_t height_;
        size_t widht_;
        
        
    public:

    Matrix (size_t col_lenght, size_t row_lenght)
        : row_lenght_(row_lenght), col_lenght_(col_lenght), data_(new T);

    Matrix (const Matrix & m)
        : Matrix(m.col_lenght_(),m.row_lenght_())
    {
        *this = m;
    }
    };



#endif