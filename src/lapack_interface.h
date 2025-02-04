#ifndef FILE_LAPACK_INTERFACE_H
#define FILE_LAPACK_INTERFACE_H

#include <iostream>
#include <string>

#include "vector.h"
#include "Matrix-Neu-using_expressions.h"

#include <vector> // for LU decomposition
#include <complex>

typedef int integer;
typedef integer logical;
typedef float real;
typedef double doublereal;
typedef std::complex<float> singlecomplex;
typedef std::complex<double> doublecomplex;

// Windows SDK defines VOID in the file WinNT.h
#ifndef VOID
typedef void VOID;
#endif
typedef int ftnlen;
typedef int L_fp;  // ?


extern "C" {
#include <clapack.h>
}




namespace ASC_bla
{
  
  // BLAS-1 functions:

  /*
    int daxpy_(integer *n, doublereal *da, doublereal *dx, 
    integer *incx, doublereal *dy, integer *incy);
  */
  // y += alpha x
  template <typename SX, typename SY>
  void AddVectorLapack (double alpha, VectorView<double,SX> x, VectorView<double,SY> y)
  {
    integer n = x.Size();
    integer incx = x.Dist();
    integer incy = y.Dist();
    int err = 
      daxpy_ (&n, &alpha, &x(0),  &incx, &y(0), &incy);
    //if (err != 0)
    //  throw std::runtime_error(std::string("daxpy returned errcode "+std::to_string(err)));      
  }
  
  
  // BLAS-2 functions:

  // BLAS-3 functions:
  
  // int dgemm_ (char *transa, char *transb, integer *m, integer * n,
  // integer *k, doublereal *alpha, doublereal *a, integer *lda, 
  // doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, 
  // integer *ldc);

    
  // c = a*b
  template <typename T, typename U, typename V, ORDERING OA, ORDERING OB>
  void MultMatMatLapack (MatrixView<T, OA> a,
                         MatrixView<U, OB> b,
                         MatrixView<V, ColMajor> c)
  {
    char transa_ = (OA == ColMajor) ? 'N' : 'T';
    char transb_ = (OB == ColMajor) ? 'N' : 'T'; 
  
    integer n = c.Get_height();
    integer m = c.Get_width();
    integer k = a.Get_width();
  
    double alpha = 1.0;
    double beta = 0;
    unsigned long a1 = a.Dist();
    integer lda = std::max(a1, 1ul);
    unsigned long b1 = b.Dist();
    integer ldb = std::max(b1, 1ul);
    unsigned long c1 = c.Dist();
    integer ldc = std::max(c1, 1ul);

    //std::cout << transa_ << ";" << transb_ << ";"<< n << ";" << m <<";" <<k << ";" << alpha<< ";" << lda << ";" <<ldb <<";"<< ldc << std::endl;

    int err =
      dgemm_ (&transa_, &transb_, &n, &m, &k, &alpha, 
              a.Data(), &lda, b.Data(), &ldb, &beta, c.Data(), &ldc);

    //if (err != 0)
    //  throw std::runtime_error(std::string("MultMatMat got error "+std::to_string(err)));
  }



  template <typename U, typename V, typename W, ORDERING OA, ORDERING OB>
  void MultMatMatLapack (MatrixView<U, OA> a,
                        MatrixView<V, OB> b,
                        MatrixView<W, RowMajor> c)
  {
    MultMatMatLapack (b.transpose(), a.transpose(), c.transpose());
  }


  

  
  template <ORDERING ORD>
  class LapackLU {
    Matrix <double, ORD> a;
    std::vector<integer> ipiv;
    
  public:
    LapackLU (Matrix<double,ORD> _a)
      : a(std::move(_a)), ipiv(a.Get_height()) {
      integer m = a.Get_height();
      if (m == 0) return;
      integer n = a.Get_width();
      integer lda = a.Dist();
      integer info;
    
      // int dgetrf_(integer *m, integer *n, doublereal *a, 
      //             integer * lda, integer *ipiv, integer *info);

      dgetrf_(&n, &m, &a(0,0), &lda, &ipiv[0], &info);
    }
    
    // b overwritten with A^{-1} b
    void Solve (VectorView<double> b) const {
      char transa =  (ORD == ColMajor) ? 'N' : 'T';
      integer n = a.Get_height();
      integer nrhs = 1;
      integer lda = a.Dist();
      integer ldb = b.Size();
      integer info;

      // int dgetrs_(char *trans, integer *n, integer *nrhs, 
      //             doublereal *a, integer *lda, integer *ipiv,
      //             doublereal *b, integer *ldb, integer *info);

      dgetrs_(&transa, &n, &nrhs, a.Data(), &lda, (integer*)ipiv.data(), b.Data(), &ldb, &info);
    }
  
    Matrix<double,ORD> Inverse() && {
      double hwork;
      integer lwork = -1;
      integer n = a.Get_height();      
      integer lda = a.Dist();
      integer info;

      // int dgetri_(integer *n, doublereal *a, integer *lda, 
      //             integer *ipiv, doublereal *work, integer *lwork, 
      //             integer *info);

      // query work-size
      dgetri_(&n, &a(0,0), &lda, ipiv.data(), &hwork, &lwork, &info);
      lwork = integer(hwork);
      std::vector<double> work(lwork);
      dgetri_(&n, &a(0,0), &lda, ipiv.data(), &work[0], &lwork, &info);
      return std::move(a);      
    }

    Matrix<double,ORD> LFactor() const { // = lower triangular matrix with unit diagonal elements
      integer m = a.Get_height();
      integer n = a.Get_width();
      Matrix<double,ORD> L(m,n);

      for (int i=0; i < m; i++) {
        for (int j=0; j < n; j++) {
          if (i > j) { L(i,j) = a(i,j); }
          else if (i == j) { L(i,j) = 1,0; }
          else { L(i,j) = 0.0; }
        }
      }
      return L;
    }

    Matrix<double,ORD> UFactor() const { // upper triangular matrix -> TODO: wrong U...
      integer m = a.Get_height();
      integer n = a.Get_width();
      Matrix<double,ORD> U(m,n);
      
      for (int i=0; i < m; i++) {
        for (int j=0; j < n; j++) {
          if (i <= j) { U(i,j) = a(i,j); }
          else { U(i,j) = 0.0; }
        }
      }
      return U;
    }

    Matrix<double,ORD> PFactor() const { // Permutation Matrix
      integer m = a.Get_height();
      integer n = a.Get_width();
      Matrix<double,ORD> P(m,n);
      
      for (int i=0; i < m; i++) {
        P(i, ipiv[i]-1) = 1.0; // -1 bc LAPACK (Fortran) indexing starts at 1
      }
      return P;
     }
  };
  

  
}


#endif
