#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <expression.h>

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
            : height_(height), width_(width), n_of_elements_(height*width), data_(new T[height*width]) 
        { for (size_t i = 0; i < n_of_elements_; i++)
            data_[i] = imputdata[i];
        }

        Matrix (const Matrix & m)       //wenn Matrix übergeben, muss nix verändert werden?
            : Matrix(m.get_height(),m.get_width())
        {
            *this = m;
        }

        Matrix (const Matrix && m)
            : height_(0), width_(0), n_of_elements_(0), data_(nullptr)
        {
            //std::swap(height_, m.height_);
            //std::swap(widht_, m.widht_);
            //std::swap(n_of_elements_, m.n_of_elements_);
            //std::swap(data_, m.data_);
        }
        size_t get_height() const { return height_;}
        size_t get_width() const { return width_;}
        size_t Size() const { return n_of_elements_; }        
        T & operator()(size_t x, size_t y) { return data_[(x-1)*width_+y-1]; }
        const T & operator()(size_t x, size_t y) const { return data_[(x-1)*width_+y-1]; }


        ~Matrix() {delete [] data_; }


        Matrix & operator=(const Matrix & v2)
        {

            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width()) + 1 ,(i%v2.get_width()) +1 );     //fixed !
            return *this;
        }

        Matrix & operator=(Matrix && v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width()) + 1 ,(i%v2.get_width()) +1 );     //fixed !
            return *this;
        }


        Matrix transpose(){
    
            double x[n_of_elements_];
            for(size_t z = 0; z< n_of_elements_;z++){
                x[z] = data_[z];
            }
            //data_[1] = x[2];
            //data_[2] = x[1];
            for(size_t i=0; i<height_; i++){
                for(size_t j=0; j<width_; j++){
                    //std::cout << "Data (" << i*width_+j << ") = " << "x (" << j*height_+i << ")" << std::endl; 
                    data_[j*height_+i]=x[i*width_+j];
                }
            }
            //for(size_t i=0;i<n_of_elements_;i++){
                //std::cout << data_[i] << std::endl;
            //}

            Matrix<T> X(width_, height_, data_);
            return X;
        }
        
    };
    
    template <typename T>
    std::ostream & operator<< (std::ostream & ost, const Matrix<T> & v)
    {
        //if (v.Size() > 0)
            //ost << v(1,1);
        for (size_t i = 1; i < v.get_height()+1; i++){
            for (size_t j = 1; j < v.get_width()+1; j++){
                if(j==1){
                    ost << v(i,j);
                }
                if(j>1){
                    ost << ", " << v(i,j);
                }
            }
            ost << std::endl;
            //if(i%(v.get_width-1)==0){
                //ost << std::endl;
            //}
        }
        return ost;
    }    
    
    template<typename T>
        Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b)
        {
        //hier könnte ihr error handling stehen
        //habs gefixt :) -Da
            for(size_t i = 0; i < a.get_height(); i++)
            {
                for(size_t j = 0; j < b.Size(); j+= b.get_width)
                {

                }
            }

        }
    /*template<typename T>
        Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b)
        {
            Matrix <T> X(b.get_height(),a.get_width())
        //hier könnte ihr error handling stehen
        //habs gefixt :) -Da
            for(size_t i = 0; i < X.get_Size(); i++)
            {
                //typename a_ =         
            }

        }
*/


}
#endif