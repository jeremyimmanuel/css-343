#ifndef _POLY_H_
#define _POLY_H_

#include <iostream>
#include <string>

using namespace std;

class Poly
{
    friend ostream& operator<<(ostream& output, const Poly& p);
    //friend istream& operator>>(ostream& input, Poly& p);
    
    public:
        Poly();
        Poly(int coeff);
        Poly(int coeff, int power);
        Poly(const Poly &p);
        ~Poly();

        int getCoeff(int power) const;
        void setCoeff(int newCoeff, int power);

        Poly operator+(const Poly& rhs) const;

        Poly& operator=(const Poly& rhs);

        bool operator==(const Poly& rhs) const;
        
    private:
        int* arr;
        int size;
};

#endif