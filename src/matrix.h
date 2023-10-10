#ifndef FILE_MATRIX_H
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
        size_t widht_;
        size_t n_of_elements_;   //kann man hier nicht direkt height_ * width_ für alle Matrizen machen? -Da
        
    public:

    Matrix()    //Standard-Konstruktor --1x1 Matrix mit Nullelement
        : height_(1), widht_(1), n_of_elements_(1), data_(new T[n_of_elements_]){data_[0] = 0.0; }

    Matrix (size_t height, size_t widht)
        : height_(height), widht_(widht), n_of_elements_(height_*widht_), data_(new T[n_of_elements_]) 
    { for (size_t i = 0; i < n_of_elements_; i++)    //füllt Matrix Element für Element mit 0
        data_[i] = 0.0;
    }

    Matrix (size_t height, size_t widht, const T* imputdata)
        : height_(height), widht_(widht), n_of_elements_(height_*widht_), data_(new T[n_of_elements_]) 
    { for (size_t i = 0; i < n_of_elements_; i++)
        data_[i] = imputdata[i];
    }

    Matrix (const Matrix & m)       //wenn Matrix übergeben, muss nix verändert werden?
        : Matrix(m.col_lenght_(),m.row_lenght_())
    {
        *this = m;
    }

    Matrix (const Matrix && m)
        : height_(0), widht_(0), n_of_elements_(0), data_(nullptr)
    {
        //std::swap(height_, m.height_);
        //std::swap(widht_, m.widht_);
        //std::swap(elements_, m.n_of_elements_);
        //std::swap(data_, m.data_);
    }

    ~Matrix() {delete [] data_; }

    };

}

#endif
