#include <iostream>

#include <vector.h>
#include <lapack_interface.h>


using namespace ASC_bla;
using namespace std;


int main()
{
  Vector<double> x(5);
  Vector<double> y(5);
  double amatrix[4] = {2,1,1,1};
  double bmatrix[4] = {1,1,1,1};
  Matrix<double,ASC_bla::RowMajor> A(2,2,amatrix);
  Matrix<double> B(2,2,bmatrix);
  Matrix<double,ASC_bla::RowMajor> C(2,2);
  cout << A << endl;
  cout << B << endl;
  //unsigned long i = A.Dist();
  //cout << max(i, 1ul) << endl;

  for (int i = 0; i < x.Size(); i++)
    {
      x(i) = i;
      y(i) = 2;
    }

 // cout << "x = " << x << endl;
 // cout << "y = " << y << endl;
  
  AddVectorLapack (2, x, y);  
  cout << "y+2*x = " << y << endl;

  MultMatMatLapack(A,B,C);
  //cout << "test" << endl;
  cout << "A*B = " << endl;
  cout << C << endl;
}

  
