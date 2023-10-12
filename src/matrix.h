#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
//#include <expression.h>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };
template <typename T, ORDERING ORD = ORDERING::RowMajor>
    class Matrix {
        ORDERING ORD_ = ORD;
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
        size_t size() const { return n_of_elements_; }        
        T & operator()(size_t row, size_t col) { //indexing startet bei M[0,0]
            if(ORD == ORDERING::RowMajor){ 
                return data_[row*width_+col];
                }
            else{//bedeutet ColMajor
                return data_[col*height_+row];
            }
        }


        const T & operator()(size_t row, size_t col) const {
            if(ORD == ORDERING::RowMajor){ 
                return data_[row*width_+col];
                }
            else{//bedeutet ColMajor
                return data_[col*height_+row];
            }
        }


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
            for(size_t i=1; i<height_+1; i++){
                for(size_t j=1; j<width_+1; j++){
                    data_[(i-1)*width_+(j-1)]=x[(j-1)*width_+(i-1)];
                }
            }


            Matrix<T> X(height_, width_, data_);
            return X;
        }

         Matrix alt_transpose(){
            if(ORD_ == RowMajor) ORD_ = ORDERING::ColMajor;//return *this(bla::ORD::ColMajor)}
            else//ORD == ColMajor
                ORD_ = ORDERING::RowMajor;
                
                return *this;

        }
        
    }
    
    template <typename T, ORDERING ORD>
    std::ostream & operator<< (std::ostream & ost, const Matrix<T,ORD> & v)
    {
        //if (v.Size() > 0)
            //ost << v(1,1);
        for (size_t i = 0; i < v.get_height(); i++){
            for (size_t j = 0; j < v.get_width(); j++){
                if(j==0){
                    ost << v(i,j);
                }
                if(j>0){
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
    
    /*template<typename T>
        Matrix  operator* (const Matrix<T> & a, const Matrix<T> & b)
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
    template<typename T>
        Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b)
        {
            Matrix <T> X(b.get_height(),a.get_width())
        //hier könnte ihr error handling stehen
        //habs gefixt :) -Da
            for(size_t i = 0; i < X.get_Size(); i++)
            {
                typename a_ =         
            }

        }*/



}
#endif