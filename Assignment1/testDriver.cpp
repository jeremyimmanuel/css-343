#include "poly.h"

int main()
{
    Poly A;
    Poly B(5,6);
    B.setCoeff(4, 2);
    B.setCoeff(2, 3);
    //A = B;
    cout << B << endl;
    B.setCoeff(3, 8);
    //A = B;

    cout << B << endl;
    //cout << A << endl;
    
    return 0;
}