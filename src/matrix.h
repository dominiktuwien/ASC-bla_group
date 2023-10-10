#ifndef FILE_MATRIX_H //to avoid double declaration if "matrix" is opened from multiple files
#define FILE_MATRIX_H

#include <iostream>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };
template <typename T, ORDERING ORD>
    class Matrix {
        //ORD* order_;
        T* data_;
        size_t height_;
        size_t width_;
        size_t elements_;
        
    public:

    Matrix()
        : height_(1), width_(1), elements_(1), data_(new T[elements_]){data_[0] = 0.0; }

    Matrix (size_t height, size_t width)
        : height_(height), width_(width), elements_(height_*width_), data_(new T[elements_]) 
    { for (size_t i = 0; i < elements_; i++)
        data_[i] = 0.0;
    }

    Matrix (size_t height, size_t width, const T* inputdata)
        : height_(height), width_(width), elements_(height_*width_), data_(new T[elements_]) 
    { for (size_t i = 0; i < elements_; i++)
        data_[i] = inputdata[i];
    }

    Matrix (const Matrix & m)
        : Matrix(m.col_lenght_(),m.row_lenght_())
    {
        *this = m;
    }

    Matrix (const Matrix && m)
        : height_(0), width_(0), elements_(0), data_(nullptr)
    {
        //std::swap(height_, m.height_);
        //std::swap(widht_, m.widht_);
        //std::swap(elements_, m.elements_);
        //std::swap(data_, m.data_);
    }

    ~Matrix() {delete [] data_; }

    };

}

#endif