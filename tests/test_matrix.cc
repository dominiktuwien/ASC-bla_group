#include <iostream>
#include <array>

#include <Matrix-Neu-using_expressions.h>
#include <vector.h>

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
    std::cout << B << std::endl;

    int test_asym[6] = {1,2,3,4,5,6};
    bla::Matrix<int, bla::ORDERING::ColMajor> J(3,2,test_asym);
    int a;
    a = J(0,1);
    std::cout << J << std::endl;
    std::cout << J.transpose() << std::endl;
    std::cout << a << std::endl;
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
    std::cout << M.Column(1) << std::endl;*/
    //std::cout << U << std::endl;
    //U = 2*K;
    //std::cout << U << std::endl;
    
    //Matrix Multiplication tests
    int testmul1[4] = {2,1,1,1};
    int testmul2[4] = {2,2,3,1};
    int testmul3[2] = {3,1};

    bla::Matrix<int> A(2,2,testmul1);
    bla::Matrix<int> B(2,2,testmul2);
    bla::Vector<int> C(2,testmul3);
    //std::cout << C << std::endl;
    //std::cout << 3*C << std::endl;
    //std::cout << "" << std::endl;
    //std::cout << "testing" << std::endl;
    //std::cout << (B*A) << std::endl;
    //std::cout << B*C << std::endl;
    //std::cout << "test" << std::endl;

    //alt transpose test
    /*int test_a[6] = {1,2,3,4,5,6};
    bla::Matrix<int, bla::ORDERING::ColMajor> J(2,3,test_a);
    std::cout << J << std::endl;
    std::cout << J.transpose() << std::endl;*/

    //Columns !!Mehrzahl, test
    int test_cols[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    bla::Matrix<int,bla::ORDERING::ColMajor> N(3,5,test_cols);
    std::cout << N << std::endl;
    std::cout << N.Rows(1,3) << std::endl;

    //inverse test
    /*
    double test_inv[9] = {1.0, 2.0, 3.0, 2.0, 5.0, 8.0, 9.0, 6.0, 4.0};
    bla::Matrix<double, bla::ORDERING::RowMajor> I(3, 3, test_inv);
    std::cout << I << std::endl;
    std::cout << I.inverse() << std::endl;
    */




    // gitignore Test


    return 0;
}