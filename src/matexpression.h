#ifndef FILE_MATRIX_EXPRESSION_H
#define FILE_MATRIX_EXPRESSION_H

#include<iostream>
#include<expression.h>

namespace ASC_bla
{

  template <typename T>
  class MatExpr
  {
  public:
    auto Upcast() const { return static_cast<const T&> (*this); }
    size_t Get_height() const { return Upcast().Get_height();}
    size_t Get_width() const { return Upcast().Get_width();}
    size_t Size() const { return Upcast().Size(); }
    auto operator() (size_t i, size_t j) const { return Upcast()(i,j); }
  };
  
 
  template <typename TA, typename TB>
  class SumMatExpr : public MatExpr<SumMatExpr<TA,TB>>
  {
    TA a_;
    TB b_;
  public:
    SumMatExpr (TA a, TB b) : a_(a), b_(b) { }

    auto operator() (size_t i, size_t j) const { return a_(i,j)+b_(i,j); }
    size_t Size() const { return a_.Size(); }
    size_t Get_height() const {return a_.Get_height();}
    size_t Get_width() const {return a_.Get_width();}        
  };
  
  template <typename TA, typename TB>
  auto operator+ (const MatExpr<TA> & a, const MatExpr<TB> & b)
  {
    return SumMatExpr(a.Upcast(), b.Upcast());
  }



  
  template <typename TSCAL, typename TM>
  class ScaleMatExpr : public MatExpr<ScaleMatExpr<TSCAL,TM>>
  {
    TSCAL scal_;
    TM mat_;
  public:
    ScaleMatExpr (TSCAL scal, TM mat) : scal_(scal), mat_(mat) { }

    auto operator() (size_t i, size_t j) const { return scal_*mat_(i, j); }
    size_t Size() const { return mat_.Size(); }
    size_t Get_height() const {return mat_.Get_height();}
    size_t Get_width() const {return mat_.Get_width();}      
  };
  
  template <typename T>
  auto operator* (double scal, const MatExpr<T> & v)
  {
    return ScaleMatExpr(scal, v.Upcast());
  }

  template<typename TMatA, typename TMatB>
  class MatMatMulExpr : public MatExpr<MatMatMulExpr<TMatA,TMatB>>
  {
    TMatA matA_;
    TMatB matB_;

    public:
      MatMatMulExpr(TMatA matA, TMatB matB) : matA_(matA), matB_(matB) { }

      auto operator() (size_t i, size_t j) {
        double result;
        for(size_t c = 0; c < matA_.Get_width(); c++){
          result += (matA_.Row(i))(c) * (matB_.Column(j))(c);        
          }
        return result;
      }
      size_t Size() const { return matA_.Get_height() * matB_.Get_width(); }
      size_t Get_height() const {return matA_.Get_height();}
      size_t Get_width() const {return matB_.Get_width();}
  };

  template<typename T>
  auto operator* (const MatExpr<T> & left, const MatExpr<T> & right)
  {
    return MatMatMulExpr(left.Upcast(), right.Upcast());
  };

    template<typename TMat, typename TVec>
  class MatMulVecExpr : public VecExpr<MatMulVecExpr<TMat,TVec>>
  {
    TMat mat_;
    TVec vec_;

    public:
      MatMulVecExpr(TMat mat, TVec vec) : mat_(mat), vec_(vec) { }

      auto operator() (size_t i) {
        double result;
        for(size_t c = 0; c < mat_.Get_width(); c++){
          result += (mat_.Row(i))(c) * vec_(c);        
          }
        return result;
      }
      size_t Size() const { return vec_.Size();}
  };

  template<typename T, typename U>
  auto operator* (const MatExpr<T> & left, const VecExpr<U> & right)
  {
    return MatMulVecExpr(left.Upcast(), right.Upcast());
  };

  template <typename T>
  std::ostream & operator<< (std::ostream & ost, const MatExpr<T> & v)
  {
    //std::cout << "test" << std::endl;
    //std::cout << v.Size() << std::endl;
    //std::cout << v(0,0) << std::endl;
    for (size_t i = 0; i < v.Get_height(); i++)
    {
      for (size_t j = 0; j < v.Get_width(); j++)
      {
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
 
}
#endif
