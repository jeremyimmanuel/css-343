#include "poly.h"
using namespace std;

Poly::Poly()
{
    size = 1;
    arr = new int[size] {0};
}

Poly::Poly(int coeff)
{
    size = 1;
    arr = new int[size] {coeff};
}

Poly::Poly(int coeff, int power)
{
    size = power + 1;
    arr = new int[size];
    arr[power] = coeff;
}

Poly::Poly(const Poly& p)
{
    size = p.size;
    arr = new int[size];
    for(int i = 0; i < size; i++)
        arr[i] = p.arr[i];
}

Poly::~Poly()
{
    delete[] arr;
    arr = nullptr;
}

int Poly::getCoeff(int power) const
{
    if(power >= 0 && power < size)
        return arr[power];
    else
        return 0;
}

void Poly::setCoeff(int newCoeff, int power)
{
    //check input
    if(power < 0)
        return;
    if(power < size)
        arr[power] = newCoeff;
    else
    {
        //make new array
        int newSize (power + 1);
        int* newArr = new int[newSize];
        //copy all elements from oldArr to newArr
        for(int i = 0; i < size; i++)
            newArr[i] = this->arr[i];

        newArr[power] = newCoeff;
        
        delete[] arr; //delete oldArr content
        arr = newArr;
        newArr = nullptr;
        
        size = newSize;
    }        
}

Poly Poly::operator+(const Poly& rhs) const
{
    int newSize;
    newSize = size > rhs.size ? size : rhs.size;   
    Poly ans(0, newSize - 1);
    for(int pow = 0; pow < newSize; pow++)
        ans.setCoeff( getCoeff(pow) + rhs.getCoeff(pow), pow);
    return ans;
}

Poly& Poly::operator=(const Poly& rhs)
{
    if(*this == rhs)
        return *this;
    
    size = rhs.size;
    delete[] arr;
    arr =  new int[size];
    for(int i = 0; i < size; i++)
        arr[i] = rhs.arr[i];
    return *this;
}

bool Poly::operator==(const Poly& rhs) const
{
    if(size != rhs.size)
        return false;
    
    for(int i = 0; i < size; i++)
    {
        if(arr[i] != rhs.arr[i])
            return false;
    }
    
    return true;
}
ostream& operator<<(ostream& output, const Poly& p)
{
    string ans = "";
    
    int coeff = 0;
    
    for(int power = 0; power < p.size; power++)
    {
        coeff = p.arr[power];
        string coeff_str = " ";
        if(coeff != 0)
        {
            coeff_str = coeff < 0 ? "-" : "+";
            coeff_str += to_string(coeff);
            ans += coeff_str + "x^" + to_string(power) + " ";
        }
            
    }
    output << ans;

    return output;
}
