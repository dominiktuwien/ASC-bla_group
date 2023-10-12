#include <iostream>
#include <array>

#include <matrix.h>

namespace bla = ASC_bla;
int main()
{
    size_t x = 5;
    std::cout << x << std::endl;
    size_t y = 6;
    bla::Matrix<double>();
    std::cout << "default constructor hat funktioniert" << std::endl;
    bla::Matrix<double> A(2,2);
    std::cout << "größen constructor hat funktioniert" << std::endl;
    std::cout << A.get_height() << "  "<< A.get_widht()<< std::endl;
    double test_data[4] = {3.0,5.0,8.0,2.0};
    bla::Matrix<double> B(2,2,test_data);
    std::cout << "data constructor hat funktioniert" << std::endl;
    std::cout << "auf matrixelemente zugreifen: "<< std::endl;
    std::cout << B(1,1) << "  " << B(1,2) << std::endl;
    std::cout << B(2,1) << "  " << B(2,2) << std::endl;
    bla::Matrix<double> C(B);
    std::cout << "kopier constructor hat funktioniert" << std::endl;
    std::cout << C(1,1) << "  " << C(1,2) << std::endl;
    std::cout << C(2,1) << "  " << C(2,2) << std::endl;
}
