#ifndef TEXTOKU_HPP
#define TEXTOKU_HPP

#include<iostream>
#include<fstream>
using namespace std;

class TextOku
{
    ifstream dosya;
    string dosyaAdi;
    string sayilar;
    int SayiSayisi;
public:
    int SayiSayisiBul();
    TextOku(string);
    string GetSayilar();
};

#endif