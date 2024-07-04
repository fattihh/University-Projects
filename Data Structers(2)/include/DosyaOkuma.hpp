#ifndef DOSYAOKUMA_HPP
#define DOSYAOKUMA_HPP

#include<iostream>
#include<fstream>
#include<limits.h>
using namespace std;

class DosyaOkuma
{
    ifstream dosya;
    string sayilar;
    int satirSayisi;
public:
    DosyaOkuma();

    string GetSayilar();
    int GetSatirSayisi();
};

#endif