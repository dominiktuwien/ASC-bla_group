#include <iostream>

#include <vector.h>
#include <Matrix-Neu-using_expressions.h>
#include <lapack_interface.h>
#include <chrono>

using namespace ASC_bla;
using namespace std;


int main()
{
/*  Vector<double> x(5);
  Vector<double> y(5);
  double amatrix[6] = {2,2,3,1,4,1};
  double bmatrix[4] = {5,2,7,1};
  Matrix<double,ASC_bla::RowMajor> A(3,2,amatrix);
  Matrix<double> B(2,2,bmatrix);
  Matrix<double,ASC_bla::RowMajor> C(3,2);
  //cout << A << endl;
  //cout << B << endl;
  //unsigned long i = A.Dist();
  //cout << max(i, 1ul) << endl;

  for (int i = 0; i < x.Size(); i++)
    {
      x(i) = i;
      y(i) = 2;
    }

 // cout << "x = " << x << endl;
 // cout << "y = " << y << endl;
  
  //AddVectorLapack (2, x, y);  
  //cout << "y+2*x = " << y << endl;*/



//Matrix Matrix Multiplication

  /*Matrix<double> T1(10,10);
  Matrix<double> T2(10,10);
  Matrix<double> T3(10,10);
  for (int j = 0; j < 10; j++){
    for (int k = 0; k < 10; k++){
      T1(j,k) = 2;
      T2(j,k) = 3;
    }
  }

  //T3 = T1*T2;
  MultMatMatLapack(T1,T2,T3);
  //T3 = T1*T2 | Lapack;
  
  cout << T3 << endl;*/

 /*int n = 10;
 size_t flops = n*n*n;
 size_t runs = size_t (1e9 / flops) + 1;
 auto start = std::chrono::high_resolution_clock::now();
 for (size_t i = 0; i < runs; i++){
  Matrix<double> T1(n,n);
  Matrix<double> T2(n,n);
  Matrix<double> T3(n,n);
  for (int j = 0; j < n; j++){
    for (int k = 0; k < n; k++){
      T1(j,k) = 2;
      T2(j,k) = 3;
    }
  }

  MultMatMatLapack(T1,T2,T3); 
  //T3 = T1*T2; // DON'T USE IF YOU WANT YOUR DEVICE TO FIX
   
   };
 auto end = std::chrono::high_resolution_clock::now();
 double time = std::chrono::duration<double>(end-start).count();
        
 cout << "n = " << n << ", time = " << time << " s, GFlops = " << (flops*runs)/time*1e-9 << endl;*/



//LU-decomposition
  double Mdata[9] = {1,1,0.5,3,1.5,3,0,0,2.5};
  Matrix<double> M(3,3, Mdata);

  // Inverse
    Matrix<double> invM = LapackLU(M).Inverse();
    cout << invM << endl;
    cout << M << endl;

    Matrix<double> invM_mov = LapackLU(std::move(M)).Inverse();
    cout << invM_mov << endl;
    cout << M << endl; // is now empty 

  // Solve (linear system Ax=b);
   /* Matrix<double> A(M);
    double bdata[3] = {1,1,1};
    Vector<double> b(3, bdata);
    cout << b << endl;

    LapackLU(M).Solve(b); // Ax=b -> x=A^{-1}b
    cout << b << endl; // b is now x
    cout << A*b << endl; // A*x = A*(A^{-1}b) = b
    */

   // A = PLU
    /*Matrix<double> A(M);
    Matrix<double> L = LapackLU(A).LFactor();
    Matrix<double> U = LapackLU(A).UFactor();
    Matrix<double> P = LapackLU(A).PFactor();
    cout << A << endl;
    cout << L << endl;
    cout << U << endl;
    cout << P << endl;

    Matrix<double> LU(3,3);
    LU = (L*U);
    Matrix<double> newA(3,3);
    newA = P*LU;
    cout << newA << endl; // should be the same as A ...almost correct :(
      */

  


}

  
