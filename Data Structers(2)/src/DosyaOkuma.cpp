/**
* @file DosyaOkuma.cpp
* @description Text'den verilerin okunmasý
* @course Veri Yapilari Grup 2A
* @assignment 2.Ödev
* @date 16.12.2023
* @author Fatih Uçar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include"DosyaOkuma.hpp"

DosyaOkuma::DosyaOkuma()
{
    satirSayisi = 0;

    dosya.open("Veri.txt");
    string sLine;
    sayilar = "";
    while (!dosya.eof())
    {
        getline(dosya, sLine);
        if (sLine != "") { satirSayisi++; }
        sayilar += sLine.data();
        sayilar += "*";
    }

    dosya.close();
}

string DosyaOkuma::GetSayilar()
{
    return this->sayilar;
}

int DosyaOkuma::GetSatirSayisi()
{
    return this->satirSayisi;
}