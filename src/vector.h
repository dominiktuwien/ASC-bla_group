#ifndef FILE_VECTOR_H
#define FILE_VECTOR_H

#include <iostream>
#include <cmath>

#include "mat_vec_decl.h"
#include "expression.h"



namespace ASC_bla
{

  // Vec class for use in mass_spring
  template <int SIZE, typename T=double>
  class Vec : public VecExpr<Vec<SIZE, T>>
  {
    T data[SIZE];

    public:
    Vec() { ; }

    Vec(T val) 
    {
      for (size_t i = 0; i < SIZE; i++) {
        data[i] = val;
      }
    }

    Vec(std::initializer_list<T> values) 
    {
      for (size_t i = 0; i < values.size(); i++) {
        data[i] = values.begin()[i];
      }
    }

    template<typename TB>
    Vec(const VecExpr<TB> &v2)
    {
      for (size_t i=0; i < SIZE; i++)
        data[i] = v2(i);
    }

    T & operator()(size_t i) { return data[i]; }
    const T & operator()(size_t i) const { return data[i]; }

    size_t Size() const { return SIZE; }

    
    
  };


 
  template <typename T, typename TDIST>
  class VectorView : public VecExpr<VectorView<T,TDIST>>
  {
  protected:
    T * data_;
    size_t size_;
    TDIST dist_;
  public:
    VectorView (size_t size, T * data)
      : data_(data), size_(size) { }
    
    VectorView (size_t size, TDIST dist, T * data)
      : data_(data), size_(size), dist_(dist) { }

    VectorView (size_t size)
      : size_(size), data_(new T[size]) {}

    //VectorView(size_t size)
    //    :   size_(size) {}
    


    VectorView & operator= (const VectorView & v2) // for ODE
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] = v2(i);
      return *this;
    }
    
    template <typename TB>
    VectorView & operator= (const VecExpr<TB> & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] = v2(i);
      return *this;
    }

    VectorView & operator= (T scal)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] = scal;
      return *this;
    }

    
    template <typename TB>
    VectorView & operator+= (const VecExpr<TB> & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] += v2(i);
      return *this;
    }

    VectorView & operator*= (double scal)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] *= scal;
      return *this;
    }

    template <typename TB>
    VectorView & operator-= (const VecExpr<TB> & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] -= v2(i);
      return *this;
    }

    VectorView & operator/= (double scal)
    {
      for (size_t i = 0; i < size_; i++)
        data_[dist_*i] /= scal;
      return *this;
    }

    
    auto View() const { return VectorView(size_, dist_, data_); }
    size_t Size() const { return size_; }
    auto Dist() const { return dist_; }    
    auto Data() const {return data_;} // necessary for Lapack
    T & operator()(size_t i) { return data_[dist_*i]; }
    const T & operator()(size_t i) const { return data_[dist_*i]; }
    
    auto Range(size_t first, size_t next) const {
      return VectorView(next-first, dist_, data_+first*dist_);
    }

    auto Slice(size_t first, size_t slice) const {
      return VectorView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
    }

    // for Mass_Spring:
    auto AsMatrix(size_t height, size_t width) const
    {
      return MatrixView<T, ORDERING::RowMajor>(height, width, data_); 
    }

      
  };

  
  
  

  
  template <typename T=double>
  class Vector : public VectorView<T>
  {
    typedef VectorView<T> BASE;
    using BASE::size_;
    using BASE::data_;
  public:
    //Vector (double size) 
    //  : VectorView<T> (size, new T[size]) { ; }

    Vector (size_t size) 
    : VectorView<T> (size) { ; } 

    Vector (size_t size, T* data)
      : VectorView<T> (size, data) { ; }

    Vector (const Vector & v)
      : Vector(v.Size())
    {
      *this = v;
    }

    Vector (Vector && v)
      : VectorView<T> (0, nullptr)
    {
      std::swap(size_, v.size_);
      std::swap(data_, v.data_);
    }

    template <typename TB>
    Vector (const VecExpr<TB> & v)
      : Vector(v.Size())
    {
      *this = v;
    }

    Vector (std::initializer_list<T> list)
    : Vector<T> (list.size(), new T[list.size()])
    {
    size_t cnt = 0;
    for (auto val : list)
    (*this)(cnt++) = val;
    }
    
    
    ~Vector () { delete [] data_; }

    using BASE::operator=;
    Vector & operator=(const Vector & v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[i] = v2(i);
      return *this;
    }

    Vector & operator= (Vector && v2)
    {
      for (size_t i = 0; i < size_; i++)
        data_[i] = v2(i);
      return *this;
    }
    
    
  };

  template <typename T>
  auto L2Norm(const VecExpr<T> & v)
  {
    double temp = 0.0; //ACHTUNG HIER SOLLTE TEMPLATE TYPE VERWENDET WERDEN
    for(int i = 0; i < v.Size(); i++)
      {
        temp += v(i)*v(i);
      }
    temp = std::sqrt(temp);
    return temp;  
  }


  template <typename ...Args>
  std::ostream & operator<< (std::ostream & ost, const VectorView<Args...> & v)
  {
    if (v.Size() > 0)
      ost << v(0);
    for (size_t i = 1; i < v.Size(); i++)
      ost << ", " << v(i);
    //std::cout << "test" << std::endl;
    return ost;
  }
  
}

#endif