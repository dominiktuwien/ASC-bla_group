#ifndef FILE_MATRIX_EXPRESSION_H
#define FILE_MATRIX_EXPRESSION_H

#include<iostream>

namespace ASC_bla
{

  template <typename T>
  class MatExpr
  {
  public:
    auto Upcast() const { return static_cast<const T&> (*this); }
    size_t Size() const { return Upcast().Size(); }
    auto operator() (size_t i) const { return Upcast()(i); }
  };
  
 
  template <typename TA, typename TB>
  class SumMatExpr : public MatExpr<SumMatExpr<TA,TB>>
  {
    TA a_;
    TB b_;
  public:
    SumMatExpr (TA a, TB b) : a_(a), b_(b) { }

    auto operator() (size_t i) const { return a_(i)+b_(i); }
    size_t Size() const { return a_.Size(); }      
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

    auto operator() (size_t i) const { return scal_*mat_(i); }
    size_t Size() const { return mat_.Size(); }      
  };
  
  template <typename T>
  auto operator* (double scal, const MatExpr<T> & v)
  {
    return ScaleMatExpr(scal, v.Upcast());
  }

  template <typename T>
  std::ostream & operator<< (std::ostream & ost, const MatExpr<T> & v)
  {
      for (size_t i = 0; i < v.Get_height(); i++){
          for (size_t j = 0; j < v.Get_width(); j++){
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
