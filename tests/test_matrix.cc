#include <iostream>
#include <array>

#include <Matrix-Neu-using_expressions.h>
#include <vector.h>

namespace bla = ASC_bla;
int main()
{
// ----- Deactivate comments for testing different parts of bla::Matrix class -----

 //constructor test
    /*bla::Matrix<double>();
    bla::Matrix<double> A(2,2);
    std::cout << "A hat format:"<< A.Get_height() << "X"<< A.Get_width()<< std::endl;
    std::cout <<"A has size: " << A.Size() << std::endl;
    std::cout << "A = " << A << std::endl; */

    /*double test_data[4] = {3.0,5.0,8.0,2.0};
    bla::Matrix<double> B(2,2,test_data); 
    bla::Matrix<double> B1(B); // copy-constructor
    std::cout << B1 << std::endl;
    std::cout << B << std::endl;
    bla::Matrix<double> B2(std::move(B)); // move-constructor
    std::cout << std::endl << B2 << std::endl;
    std::cout << B << std::endl;*/
    
 //transpose test
    /*double test_data_2[9] = {1.0,4.0,2.0,6.0,8.0,3.0,7.0,9.0,0.0};
    bla::Matrix<double, bla::ORDERING::ColMajor> C1(3,3,test_data_2);
    std::cout << C1 << std::endl;
    std::cout << C1.transpose() << std::endl;

    int test_asym[6] = {1,2,3,4,5,6};
    bla::Matrix<int, bla::ORDERING::RowMajor> C2(3,2,test_asym);
    std::cout << C2 << std::endl;
    std::cout << C2.transpose() << std::endl;*/

 //Matrix Expressions
    /*int test_a[6] = {1,2,3,4,5,6};
    int test_b[6] = {6,5,4,3,2,1};
    bla::Matrix<int> D(3,2,test_a);
    bla::Matrix<int> E(3,2,test_b);

    // ScaleMat
    bla::Matrix<int> M_expr(3,2);
    M_expr = 4*D;
    std::cout << M_expr << std::endl;
    // SumMat
    M_expr = D+E;
    std::cout << M_expr << std::endl;
    // DiffMat
    M_expr = D-E;
    std::cout << M_expr << std::endl;
    // MatMatMul
    bla::Matrix<int> E_T(2,3);
    E_T = E.transpose();
    bla::Matrix<int> M_MatMatMul1(2,2);
    bla::Matrix<int> M_MatMatMul2(3,3);
    M_MatMatMul1 = E_T*D;
    M_MatMatMul2 = D*E_T;
    std::cout << M_MatMatMul1 << std::endl;
    std::cout << M_MatMatMul2 << std::endl; */

 //Rows & Columns
    /*int data_f[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    bla::Matrix<int> F(3,5,data_f);

    std::cout << F.Row(0) << std::endl;
    std::cout << F.Row(1) << std::endl;
    std::cout << F.Row(2) << std::endl;
    std::cout << F.Column(0) << std::endl;
    std::cout << F.Column(2) << std::endl;
    std::cout << F.Column(4) << std::endl;
    std::cout << std::endl << F.Rows(1,3) << std::endl;
    std::cout << F.Columns(2,4) << std::endl;*/

 //inverse
    double test_inv[9] = {1.0, 2.0, 3.0, 2.0, 5.0, 8.0, 9.0, 6.0, 4.0};
    bla::Matrix<double, bla::ORDERING::RowMajor> G(3, 3, test_inv);
    std::cout << G << std::endl;
    std::cout << G.inverse() << std::endl;
    




    // gitignore Test


    return 0;
}