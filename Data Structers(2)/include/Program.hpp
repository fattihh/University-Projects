#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include"AVL.hpp"
#include"DosyaOkuma.hpp"
#include<Windows.h>
#include<unistd.h>
class Program
{
	int AvlSayisi;
	AVL** agaclar;
	DosyaOkuma* dosyaOku;
	Stack** yaprakStackleri;
	int silinenElemanSayisi;
	void AvlAgaclariniOlustur();
	Stack* kucukElemanStackGetir();
	Stack* buyukElemanStackGetir();
	void AsciiDegerleriniEkranaYazdir();
public:
	void ProgramiBaslat();
	~Program();
};

#endif