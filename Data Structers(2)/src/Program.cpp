/**
* @file Program.cpp
* @description Main iþlevlerinin yapýlmasý
* @course Veri Yapilari Grup 2A
* @assignment 2.Ödev
* @date 16-23.12.2023
* @author Fatih Uçar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include "Program.hpp"

void Program::ProgramiBaslat()
{
	this->silinenElemanSayisi = 0;
	this->dosyaOku = new DosyaOkuma();
	this->AvlSayisi = dosyaOku->GetSatirSayisi();
	this->agaclar = new AVL * [AvlSayisi];
	AvlAgaclariniOlustur();
	AsciiDegerleriniEkranaYazdir();

	this->yaprakStackleri = new Stack * [AvlSayisi];
	bool buyukSil = false;
	while (silinenElemanSayisi != (AvlSayisi - 1))
	{
		while (true)
		{
			Stack* stack;
			if (buyukSil)
				stack = buyukElemanStackGetir();
			else
				stack = kucukElemanStackGetir();

			stack->pop();

			if (stack->isEmpty())
			{
				for (int i = 0; i < AvlSayisi; i++)
				{
					if (agaclar[i] != NULL)
					{
						if (agaclar[i]->getPostorderYaprak() == stack)
						{
							delete agaclar[i];
							agaclar[i] = NULL;
							silinenElemanSayisi++;
						}
						else
						{
							agaclar[i]->stackleriOlustur();
						}
					}
				}
				buyukSil = false;
				break;
			}

			buyukSil = !buyukSil;
		}

		AsciiDegerleriniEkranaYazdir();
	}
}

Stack* Program::kucukElemanStackGetir()
{
	int kucuk = INT_MAX;
	Stack* silinecekStack;
	for (int i = 0; i < AvlSayisi; i++)
	{
		if (agaclar[i] != NULL)
		{
			Stack* stack = agaclar[i]->getPostorderYaprak();
			if (stack->top() < kucuk)
			{
				kucuk = stack->top();
				silinecekStack = stack;
			}
		}
	}
	return silinecekStack;
}

Stack* Program::buyukElemanStackGetir()
{
	int buyuk = -1;
	Stack* silinecekStack;
	for (int i = 0; i < AvlSayisi; i++)
	{
		if (agaclar[i] != NULL)
		{
			Stack* stack = agaclar[i]->getPostorderYaprak();
			if (stack->top() > buyuk)
			{
				buyuk = stack->top();
				silinecekStack = stack;
			}
		}
	}
	return silinecekStack;
}

void Program::AvlAgaclariniOlustur()
{
	string sayilar = dosyaOku->GetSayilar();

	string strSayi = "";
	int avlSayac = 0;
	agaclar[avlSayac] = new AVL();

	int sayilarSize = sayilar.length();
	for (int i = 0; i < sayilarSize; i++)
	{
		if (sayilar[i] == ' ')
		{
			if (strSayi.length() != 0)
			{
				int sayi = stoi(strSayi);
				agaclar[avlSayac]->Add(sayi);
				strSayi = "";
			}
		}
		else if (sayilar[i] == '*')
		{
			if (strSayi.length() != 0)
			{
				int sayi = stoi(strSayi);
				agaclar[avlSayac]->Add(sayi);
				strSayi = "";
			}
			agaclar[++avlSayac] = new AVL();
		}
		else
		{
			strSayi += sayilar[i];
		}
	}
}

void Program::AsciiDegerleriniEkranaYazdir()
{
	system("cls");
	for (int i = 0; i < AvlSayisi; i++)
	{
		if (agaclar[i] != NULL)
		{
			char ascii = agaclar[i]->getascii();
			if (silinenElemanSayisi == (AvlSayisi - 1))
			{
				cout << "===================================" << endl;
				cout << "|                                 |" << endl;
				cout << "|                                 |" << endl;
				cout << "|    Son Karakter: " << ascii << "              | " << endl;
				cout << "|    AVL No      : " << i+1 << "            |" << endl;
				cout << "|                                 |" << endl;
				cout << "|                                 |" << endl;
				cout << "===================================" << endl;
			}
			else
				cout << ascii;
		}
	}
}

Program::~Program()
{
	delete dosyaOku;
	for (int i = 0; i < AvlSayisi; i++) { delete agaclar[i]; }
	delete[] agaclar;
}