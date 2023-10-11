#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include<vector>
namespace ASC_bla{

enum Ordering{RowMajor, ColMajor};

template<typename T, Ordering>
class Matrix{
    size_t rows_;
    size_t cols_;
    size_t size_;
    vector<vector<T>> entries_;
    


};

}

#endif