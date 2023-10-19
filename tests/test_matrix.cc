#include <iostream>
#include <array>

#include <Matrix-Neu-using_expressions.h>

namespace bla = ASC_bla;
int main()
{
    /*size_t x = 5;
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
    std::cout << B << std::endl;*/

    int test_asym[6] = {1,2,3,4,5,6};
    bla::Matrix<int> J(3,2,test_asym);
    int a;
    a = J(0,0);
    //std::cout << J << std::endl;
    //std::cout << J.transpose() << std::endl;
    //std::cout << a << std::endl;
    int test_a[6] = {1,2,3,4,5,6};
    int test_b[6] = {6,5,4,3,2,1};
    bla::Matrix<int> K(3,2,test_a);
    bla::Matrix<int> M(3,2,test_b);
    std::cout << K << std::endl;
    std::cout << "type of (2*K) is  " << typeid(2*K).name() << std::endl;
    std::cout << (4*K) << std::endl;
    std::cout << "type of (M+K) is  " << typeid(M+K).name() << std::endl;
    std::cout << (M+K) << std::endl;
    std::cout << M.Row(0) << std::endl;
    std::cout << M.Row(1) << std::endl;
    std::cout << M.Row(2) << std::endl;
    std::cout << M << std::endl;
    std::cout << M.Column(0) << std::endl;
    std::cout << M.Column(1) << std::endl;
    //std::cout << U << std::endl;
    //U = 2*K;
    //std::cout << U << std::endl;
    
   
    

    // This is a test :)


    return 0;
}