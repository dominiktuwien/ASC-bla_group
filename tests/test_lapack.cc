#include <iostream>

#include <vector.h>
#include <Matrix-Neu-using_expressions.h>
#include <lapack_interface.h>
#include <chrono>

using namespace ASC_bla;
using namespace std;


int main()
{
  Vector<double> x(5);
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
  //cout << "y+2*x = " << y << endl;

  //MultMatMatLapack(A,B,C);
  //C = A*B;
  //cout << "test" << endl;
  //cout << "A*B = " << endl;
  //cout << C << endl;
  Matrix<double> T1(10,10);
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
  cout << T3 << endl;
/*
 int n = 10;
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
  //T3 = T1*T2; 
   
   };
 auto end = std::chrono::high_resolution_clock::now();
 double time = std::chrono::duration<double>(end-start).count();
        
 cout << "n = " << n << ", time = " << time << " s, GFlops = " << (flops*runs)/time*1e-9 << endl;
*/
}

  
