#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include"TextOku.hpp"
#include"SayilarListesi.hpp"

class Program
{ 
public:
    SayilarListesi* sayilarListesi;
    Program();
    void SayilarListesiOlustur();
    void programiBaslat();
    
};

#endif