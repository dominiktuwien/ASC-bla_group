#ifndef FILE_MATRIX_EXPRESSION_H
#define FILE_MATRIX_EXPRESSION_H

#include <iostream>
#include "expression.h"

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



  template <typename TA, typename TB>
  class DiffMatExpr : public MatExpr<DiffMatExpr<TA,TB>>
  {
    TA a_;
    TB b_;
  public:
    DiffMatExpr (TA a, TB b) : a_(a), b_(b) { }

    auto operator() (size_t i, size_t j) const { return a_(i,j)-b_(i,j); }
    size_t Size() const { return a_.Size(); }
    size_t Get_height() const {return a_.Get_height();}
    size_t Get_width() const {return a_.Get_width();}        
  };
  
  template <typename TA, typename TB>
  auto operator- (const MatExpr<TA> & a, const MatExpr<TB> & b)
  {
    return DiffMatExpr(a.Upcast(), b.Upcast());
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
        double result{0};
        for(size_t c = 0; c < matA_.Get_width(); c++){
          result += (matA_.Row(i))(c) * (matB_.Column(j))(c);        
          }
        return result;
      }
      size_t Size() const { return matA_.Get_height() * matB_.Get_width(); }
      size_t Get_height() const {return matA_.Get_height();}
      size_t Get_width() const {return matB_.Get_width();}
      TMatA Get_matA() const {return matA_;}
      TMatB Get_matB() const {return matB_;}
  };

  template<typename T>
  auto operator* (const MatExpr<T> & left, const MatExpr<T> & right)
  {
    return MatMatMulExpr(left.Upcast(), right.Upcast());
  }


  template<typename TMatA, typename TVecB>
  class MatMulVecExpr : public VecExpr<MatMulVecExpr<TMatA,TVecB>>
  {
    TMatA matA_;
    TVecB vecB_;

    public:
      MatMulVecExpr(TMatA matA, TVecB vecB) : matA_(matA), vecB_(vecB) { }

      auto operator() (size_t i) {
        double result{0};
        for(size_t c = 0; c < vecB_.Size(); c++){
          result += (matA_.Row(i))(c) * (vecB_)(c);        
          }
        return result;
      }
      size_t Size() const { return vecB_.Size(); }
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

  class T_Par {};
  static constexpr T_Par Par;

  template<typename TMatA, typename TMatB>
  class ParMulExpr : public MatExpr<ParMulExpr<TMatA,TMatB>>
  {
    TMatA matA_;
    TMatB matB_;

    public:
      ParMulExpr(TMatA matA, TMatB matB) : matA_(matA), matB_(matB) { }

      size_t Size() const { return matA_.Get_height() * matB_.Get_width(); }
      size_t Get_height() const {return matA_.Get_height();}
      size_t Get_width() const {return matB_.Get_width();}
      TMatA Get_matA() const {return matA_;}
      TMatB Get_matB() const {return matB_;}
  };

  template<typename T = double, typename TMatA,typename TMatB>
  auto operator| (const MatMatMulExpr<TMatA,TMatB> & left, const T_Par & right)
  {
    ParMulExpr<TMatA,TMatB> X(left.Get_matA(),left.Get_matB());
    return X;
  };

    

 
}
#endif
