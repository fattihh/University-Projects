#ifndef SayilarListesi_HPP
#define SayilarListesi_HPP

#include "Dugum.hpp"


class SayilarListesi{
	private:
		Dugum* head;
		int size;
		Dugum* enBuyukSayi;
		Dugum* FindPrevByPosition(int);
	public:
		SayilarListesi();
		bool isEmpty() const;
		int Count() const;
		Sayi* first();
		Sayi* last();
		void add(Sayi*);
		void insert(int, Sayi*);
		void remove(Sayi*);
		void removeAt(int);
		bool find(Sayi*) const;
		int indexOf(Sayi*);
		void print();
		void satiryaz(string,string,Dugum*);
		void satiryaz(Dugum*);
		void tekBasamaklariBasaAl();
		void basamaklariTersle();
		void enBuyukSayiyiSil();
		void clear();
		~SayilarListesi();
};
#endif