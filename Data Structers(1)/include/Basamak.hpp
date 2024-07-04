#ifndef Basamak_hpp
#define Basamak_hpp
#include <iostream>

using namespace std;

class Basamak
{
    public:
        int item;
        Basamak* next;
        Basamak(const int&, Basamak* next);
};


#endif