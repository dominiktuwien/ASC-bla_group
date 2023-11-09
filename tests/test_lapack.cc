#include <iostream>

#include <vector.h>
#include <Matrix-Neu-using_expressions.h>
#include <lapack_interface.h>


using namespace ASC_bla;
using namespace std;


int main()
{
  Vector<double> x(5);
  Vector<double> y(5);

  for (int i = 0; i < x.Size(); i++)
    {
      x(i) = i;
      y(i) = 2;
    }

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
  
  AddVectorLapack (2, x, y);  
  cout << "y+2*x = " << y << endl;
  double data1[9] = {1,2,3,4,5,6,7,8,9};
  Matrix<double, ORDERING::RowMajor> A(3,3,data1);
  Matrix<double, ORDERING::RowMajor> B(3,3, data1);
  Matrix<double, ORDERING::ColMajor> C(3,3);
  cout << C << endl;
  MultMatMatLapack(A,B,C);
  cout << C << endl;


}

  
