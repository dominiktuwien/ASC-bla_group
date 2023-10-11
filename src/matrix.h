#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };
template <typename T> //, ORDERING ORD>
    class Matrix {
        //ORDERING* order_;
        T * data_;
        size_t height_;
        size_t width_;
        size_t n_of_elements_;   //kann man hier nicht direkt height_ * width_ für alle Matrizen machen? -Da
        
        public:

        Matrix()    //Standard-Konstruktor --1x1 Matrix mit Nullelement
            : height_(1), width_(1), n_of_elements_(1), data_(new T[1]){data_[0] = 0.0; }

        Matrix (size_t height, size_t width)
            : height_(height), width_(width), n_of_elements_(height*width), data_(new T[height*width]) 
        { for (size_t i = 0; i < n_of_elements_; i++)    //füllt Matrix Element für Element mit 0
            data_[i] = 0.0;
        }

        Matrix (size_t height, size_t width, const T* imputdata)
            : height_(height), width_(width), n_of_elements_(height_*width_), data_(new T[n_of_elements_]) 
        { for (size_t i = 0; i < n_of_elements_; i++)
            data_[i] = imputdata[i];
        }

        Matrix (const Matrix & m)       //wenn Matrix übergeben, muss nix verändert werden?
            : Matrix(m.col_lenght_(),m.row_lenght_())
        {
            *this = m;
        }

        Matrix (const Matrix && m)
            : height_(0), width_(0), n_of_elements_(0), data_(nullptr)
        {
            //std::swap(height_, m.height_);
            //std::swap(widht_, m.widht_);
            //std::swap(elements_, m.n_of_elements_);
            //std::swap(data_, m.data_);
        }
        size_t get_height() const { return height_;}
        size_t get_width() const { return width_;}
        size_t Size() const { return n_of_elements_; }        
        T & operator()(size_t x, size_t y) { return data_[(x-1)*width_+y-1]; }
        const T & operator()(size_t x, size_t y) const { return data_[(x-1)*width_+y-1]; }


    Matrix transpose()

        ~Matrix() {delete [] data_; }


        Matrix & operator=(const Matrix & v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2(i);
            return *this;
        }

        Matrix & operator=(Matrix && v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2(i);
            return *this;
        }

        
    };
    
    template<typename T>
    Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b)
    {
        //hier könnte ihr error handling stehen
        for(size_t i = 0; i < a.get_height(); i++)
            for(size_t j = 0; j < b.Size(); j+= b.get_width)

    }

}

#endif
