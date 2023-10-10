#include <iostream>

#include <matrix.h>

namespace bla = ASC_bla;
int main()
{
    size_t x = 5;
    size_t y = 6;
    bla::Matrix<double,bla::ColMajor>();

    bla::Matrix<double,bla::ColMajor> A(x,x),B(x,y);

return 0;
}
