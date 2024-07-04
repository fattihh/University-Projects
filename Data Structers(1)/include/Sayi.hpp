#ifndef Sayi_HPP
#define Sayi_HPP

#include "Basamak.hpp"
#include <sstream>
#include <iomanip>

class Sayi {
private:
	Basamak* head;

	int size;

	Basamak* FindPrevByPosition(int);

public:
	Sayi() ;

	bool isEmpty() const ;

	int Count() const ;

	const int& first() ;

	const int& last() ;

	void add(const int&) ;

	void insert(int, const int&) ;

	void remove(const int&) ;

	void removeAt(int) ;

	bool find(const int&) const ;

	int indexOf(const int&) ;

	void print();

	void satiryaz(string);

	void satiryaz();

	string sayidegeri();

	void tekBasamaklariBasaAl();

	void basamaklariTersle();

	void clear() ;

	~Sayi() ;
};
#endif