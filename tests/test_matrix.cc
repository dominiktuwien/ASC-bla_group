#include <iostream>

#include <matrix.h>

namespace bla = ASC_bla;
int main()
{
    size_t x = 5;
    size_t y = 6;
    bla::Matrix<double>();
    //std::cout << "default constructor hat funktioniert" << std::endl;
    bla::Matrix<double> A(2,2);
    //std::cout << "größen constructor hat funktioniert" << std::endl;
    std::cout << A.get_height() << "  "<< A.get_width()<< std::endl;
    std::cout <<"A has size: " << A.Size() << std::endl; 
    double test_data[4] = {3.0,5.0,8.0,2.0};
    bla::Matrix<double> B(2,2,test_data);
    //std::cout << "data constructor hat funktioniert" << std::endl;
    std::cout << "B(1,2) = " << B(1,2) << std::endl;
    std::cout << "B(2,1) = " << B(2,1) << std::endl;
    std::cout << B << std::endl;
    std::cout << B.transpose() << std::endl;
    double test_data_2[9] = {1.0,4.0,2.0,6.0,8.0,3.0,7.0,9.0,0.0};
    bla::Matrix<double> C(3,3,test_data_2);
    std::cout << C << std::endl;
    std::cout << C.transpose() << std::endl;


return 0;
}
