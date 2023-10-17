#include <iostream>
#include <array>

#include <Matrix-Neu-using_expressions.h>

namespace bla = ASC_bla;
int main()
{
    size_t x = 5;
    size_t y = 6;
    bla::Matrix<double>();
    std::cout << "default constructor hat funktioniert" << std::endl;
    bla::Matrix<double> A(2,2);
    std::cout << "größen constructor hat funktioniert" << std::endl;
    std::cout << "A hat format:"<< A.Get_height() << "X"<< A.Get_width()<< std::endl;
    std::cout <<"A has size: " << A.Size() << std::endl;
    std::cout << A << std::endl; 
    double test_data[4] = {3.0,5.0,8.0,2.0};
    bla::Matrix<double> B(2,2,test_data);
    std::cout << "data constructor hat funktioniert" << std::endl;
    bla::Matrix<double> D(B);
    std::cout << "kopier constructor hat funktioniert D:" << std::endl;
    std::cout << D << std::endl;
    std::cout << B << std::endl;
    std::cout << B.transpose() << std::endl;
    double test_data_2[9] = {1.0,4.0,2.0,6.0,8.0,3.0,7.0,9.0,0.0};
    bla::Matrix<double> C(3,3,test_data_2);
    std::cout << C << std::endl;
    std::cout << C.transpose() << std::endl;
    B = D;
    std::cout << B << std::endl;


    return 0;
}