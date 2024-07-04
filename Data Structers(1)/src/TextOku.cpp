/** 
* @file TextOku.cpp
* @description TextOku sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 15-16.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/


#include"TextOku.hpp"

TextOku::TextOku(string dosyaAdi)
{
    this->dosyaAdi = dosyaAdi;
    dosya.open(dosyaAdi);
    string sLine;
    sayilar = "";
    while (!dosya.eof())
    {
        getline(dosya, sLine);
        sayilar += " ";         
        sayilar += sLine.data();
    }
    SayiSayisi = SayiSayisiBul();

    dosya.close();
}

int TextOku::SayiSayisiBul()
{
    int SayiSayisi = 1;
    for(int i = 0; i < sayilar.length(); i++)
    {
        if(sayilar[i] == ' ')
        {
            SayiSayisi++;
        }
    }
    return SayiSayisi;
}

string TextOku::GetSayilar()
{
    return this->sayilar;
}