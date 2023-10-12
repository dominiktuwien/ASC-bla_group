#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
#include <expression.h>

namespace ASC_bla
{
enum ORDERING { ColMajor, RowMajor };


template <typename T, typename TDIST = std::integral_constant<size_t,1> >
  class MatrixView : public MatExpr<MatrixView<T,TDIST>>
  {
  protected:
    T * data_;
    size_t height_;
    size_t width_;
    size_t n_of_elements_;
    TDIST dist_;
  public:
    MatrixView (size_t height, size_t width, T * data)
      : data_(data), n_of_elements_(height*width), height_(height), width_(width) { }
    
    MatrixView (size_t height, size_t width, TDIST dist, T * data)
      : data_(data), n_of_elements_(height*width), height_(height), width_(width), dist_(dist) { }
    
    template <typename TB>
    MatrixView & operator= (const MatExpr<TB> & v2)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = v2((i/v2.get_width()),(i%v2.get_width()) );
      return *this;
    }

    MatrixView & operator= (T scal)
    {
      for (size_t i = 0; i < n_of_elements_; i++)
        data_[dist_*i] = scal;
      return *this;
    }

    auto View() const { return MatrixView(height_, width_, n_of_elements_, dist_, data_); }
    size_t Get_width() {return width_}
    size_t Get_height() {return height_}
    size_t Size() const { return n_of_elements_; }
    T & operator()(size_t x, size_t y) { return data_[(x)*width_+y]; }
    const T & operator()(size_t x, size_t y) const { return data_[(x)*width_+y]; }
    
    auto Range(size_t first_x, size_t first_y, size_t next_x, size_t next_y) const {
      return MatrixView((next_x-first_x)*(next_y-first_y), dist_, data_+(first_x)*width_+first_y*dist_);
    }

    auto Slice(size_t first, size_t slice) const {
      return MatrixView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
    }
      
  };


template <typename T> //, ORDERING ORD>
    class Matrix : public MatrixView<T> 
    {
        //ORDERING* order_;
        typedef MatrixView<T> BASE;
        using BASE::n_of_elements_;
        using BASE::data_; 
        
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
        T & operator()(size_t x, size_t y) { return data_[(x)*width_+y]; }
        const T & operator()(size_t x, size_t y) const { return data_[(x)*width_+y]; }


        ~Matrix() {delete [] data_; }


        Matrix & operator=(const Matrix & v2)
        {

            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width()) ,(i%v2.get_width()) );     
            return *this;
        }

        Matrix & operator=(Matrix && v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width())  ,(i%v2.get_width()));     
            return *this;
        }


        Matrix transpose(){
    
            double x[n_of_elements_];
            for(size_t z = 0; z< n_of_elements_;z++){
                x[z] = data_[z];
            }
            for(size_t i=0; i<height_; i++){
                for(size_t j=0; j<width_; j++){
                    data_[(i)*width_+(j)]=x[(j)*width_+(i)];
                }
            }


            Matrix<T> X(height_, width_, data_);
            return X;
        }
        
    };
    
    template <typename T>
    std::ostream & operator<< (std::ostream & ost, const Matrix<T> & v)
    {
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



}
#endif