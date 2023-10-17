#ifndef FILE_MATRIX_H
#define FILE_MATRIX_H

#include <iostream>
//#include <vector.h>
//#include <expression.h>

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

        Matrix (Matrix && m)
            : height_(0), width_(0), n_of_elements_(0), data_(nullptr)
        {
            std::swap(height_, m.height_);
            std::swap(width_, m.width_);
            std::swap(n_of_elements_, m.n_of_elements_);
            std::swap(data_, m.data_);
        }

        size_t get_height() const { return height_;}
        size_t get_width() const { return width_;}
        size_t Size() const { return n_of_elements_; } 
        // 1 based call operators:     
        //T & operator()(size_t x, size_t y) { return data_[(x-1)*width_+y-1]; }
        //const T & operator()(size_t x, size_t y) const { return data_[(x-1)*width_+y-1]; }
        // 0-based call operators:
        T & operator()(size_t x, size_t y) { return data_[x*width_+y]; }
        const T & operator()(size_t x, size_t y) const { return data_[x*width_+y]; }

        ~Matrix() {delete [] data_; }

        // ----- 1-BASED ASSIGNEMENT OPERATORS -----
        // Matrix & operator=(const Matrix & v2)
        // {

        //     for (size_t i = 0; i < n_of_elements_; i++)
        //         data_[i] = v2((i/v2.get_width()) + 1 ,(i%v2.get_width()) +1 );     //fixed !
        //     return *this;
        // }

        // Matrix & operator=(Matrix && v2)
        // {
        //     for (size_t i = 0; i < n_of_elements_; i++)
        //         data_[i] = v2((i/v2.get_width()) + 1 ,(i%v2.get_width()) +1 );     //fixed !
        //     return *this;
        // }

        Matrix & operator=(const Matrix & v2)
        {

            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width()) ,(i%v2.get_width()));     //fixed !
            return *this;
        }

        Matrix & operator=(Matrix && v2)
        {
            for (size_t i = 0; i < n_of_elements_; i++)
                data_[i] = v2((i/v2.get_width()) ,(i%v2.get_width()));     //fixed !
            return *this;
        }

        // ----- 1-BASED TRANSPOSE -----
        // Matrix transpose(){
    
        //     double x[n_of_elements_];
        //     for(size_t z = 0; z< n_of_elements_;z++){
        //         x[z] = data_[z];
        //     }
        //     //data_[1] = x[2];
        //     //data_[2] = x[1];
        //     for(size_t i=1; i<height_+1; i++){
        //         for(size_t j=1; j<width_+1; j++){
        //             data_[(i-1)*width_+(j-1)]=x[(j-1)*width_+(i-1)];
        //         }
        //     }


        //     Matrix<T> X(height_, width_, data_);
        //     return X;
        // }

        Matrix transpose(){
    
            double x[n_of_elements_];
            for(size_t z = 0; z< n_of_elements_;z++){
                x[z] = data_[z];
            }
            //data_[1] = x[2];
            //data_[2] = x[1];
            for(size_t i=0; i<height_; i++){
                for(size_t j=0; j<width_; j++){
                    data_[i*width_+j]=x[j*width_+i];
                }
            }


            Matrix<T> X(height_, width_, data_);
            return X;
        }


        Matrix inverse() const { // works only for 2x2 matrices
            Matrix<T> inv_matrix(2,2);

            if (height_ != 2 || width_ !=2) {
                std::cout << "Oops... Try the Eigen library for inverting matrices with dimensions other than 2x2!" << std::endl;
                return inv_matrix;
            }

            T det = data_[0] * data_[3] - data_[1] * data_[2];
            if (det == 0) {
                std::cout << "Oops... This is a singular matrix, there is no inverse!" << std::endl;
                return inv_matrix;
            }

            inv_matrix(0,0) = data_[3] / det; // TODO: soll auch für ColMajor funktionieren
            inv_matrix(0,1) = (-data_[1] / det);
            inv_matrix(1,0) = (-data_[2]) / det;
            inv_matrix(1,1) = data_[0] / det;
            std::cout << inv_matrix(0,0) << std::endl;
            std::cout << inv_matrix(0,1) << std::endl;
            std::cout << inv_matrix(1,0) << std::endl;
            std::cout << inv_matrix(1,1) << std::endl;

            return inv_matrix;
        }

        
    };
    
    // ----- 1-BASED OSTREAM -----
    // template <typename T>
    // std::ostream & operator<< (std::ostream & ost, const Matrix<T> & v)
    // {
    //     //if (v.Size() > 0)
    //         //ost << v(1,1);
    //     for (size_t i = 1; i < v.get_height()+1; i++){
    //         for (size_t j = 1; j < v.get_width()+1; j++){
    //             if(j==1){
    //                 ost << v(i,j);
    //             }
    //             if(j>1){
    //                 ost << ", " << v(i,j);
    //             }
    //         }
    //         ost << std::endl;
    //         //if(i%(v.get_width-1)==0){
    //             //ost << std::endl;
    //         //}
    //     }
    //     return ost;
    // }    

    template <typename T>
    std::ostream & operator<< (std::ostream & ost, const Matrix<T> & v)
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
    
    template <typename T>
    Matrix<T> operator* (const Matrix<T> & a, const Matrix<T> & b) // matrix multiplication
    {
        Matrix<T> product_m(a.get_height(), b.get_width());

        for (size_t i=0; i < a.get_height(); i++) { // rows of a
            for (size_t j=0; j < b.get_width(); j++) { // cols of b
                T m_entry = 0;
                for (size_t k=0; k < a.get_width(); k++) {
                    m_entry += a(i,k) * b(k,j);
                }
                product_m(i, j) = m_entry;
            }
        }
        return product_m;
    }
    // TODO: ColMajor vs. RowMajor ist hier egal... oder?

    // ----- COMPATIBLE WITH OLD VECTOR CLASS -----
    // template <typename T>
    // Matrix<T> operator* (const Matrix<T> & a, const Vector<T> & v2) // matrix-vector multiplication
    // {
    //     Vector<T> product_v(a.get_height());

    //     for (size_t i=0; i < a.get_height(); i++) { // rows of a
    //         T v_entry = 0;
    //         for (size_t j=0; j < a.get_width; j++) { // cols of a (= length of vector)
    //             v_entry += a(i, j) * v2(j);
    //         }
    //         product_v(i) = v_entry;
    //     }
    //     return product_v;
    // }

}
#endif