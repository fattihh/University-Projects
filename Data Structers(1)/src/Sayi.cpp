/** 
* @file Sayi.cpp
* @description Sayi sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 17-24.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include "Sayi.hpp"
#include <iomanip>

Basamak* Sayi::FindPrevByPosition(int position) {
		if (position < 0 || position > size) throw "Index out of range";
		int index = 1;

		for (Basamak* itr = head; itr != NULL; itr = itr->next, index++) {
			if (position == index) return itr;
		}
		return NULL;
	}

Sayi::Sayi() {
		head = NULL;
		size = 0;
	}

bool Sayi::isEmpty() const {
		return head == NULL;
	}

int Sayi::Count() const {
		return size;
	}

const int& Sayi:: first() {
		if (isEmpty()) throw "Empty list";
		return head->item;
	}

const int& Sayi::last()  {
		if (isEmpty()) throw "Empty list";
		return FindPrevByPosition(size)->item;
	}

void Sayi::add(const int& item) {
		insert(size, item);
	}

void Sayi::insert(int index, const int& item) {
		if (index == 0) head = new Basamak(item, head);
		else {
			Basamak* prev = FindPrevByPosition(index);
			prev->next = new Basamak(item, prev->next);
		}
		size++;
	}

void Sayi::remove(const int& item) {
		int position = indexOf(item);
		removeAt(position);
	}

void Sayi::removeAt(int index) {
		if (size == 0) throw "Empty list";
		Basamak* del;
		if (index == 0) {
			del = head;
			head = head->next;
		}
		else {
			Basamak* prev = FindPrevByPosition(index);
			del = prev->next;
			prev->next = prev->next->next;
		}
		delete del;
		size--;
	}

bool Sayi::find(const int& item) const {
		for (Basamak* itr = head; itr != NULL; itr = itr->next) {
			if (itr->item == item) return true;
		}
		return false;
	}

int Sayi::indexOf(const int& item) {
		int index = 0;
		for (Basamak* itr = head; itr != NULL; itr = itr->next, index++) {
			if (itr->item == item) return index;
		}
		throw "Index out of range";
	}

void Sayi::print()
{
	if (head == NULL) cout << "SayilarListesi::Empty list";
	else
	{
		for (Basamak* itr = head; itr != NULL; itr = itr->next) 
		{
			cout <<itr->item;
			cout<<endl;
		}
	}
}

void Sayi::satiryaz(string y)
{
	for (Basamak* itr = head; itr != NULL; itr = itr->next)
	{
		if(y == "basamak")
			cout << " *" << setw(5) << right << itr->item<< "*";
		else
			cout << " *" << setw(5) << right << y << "*";
	}
}

void Sayi::satiryaz()
{
	for (Basamak* itr = head; itr != NULL; itr = itr->next)
	{
		stringstream ss;
		ss << &itr->item;
		string adres = ss.str();
		adres = adres.substr(adres.length() - 3);
		cout << " *" << setw(5) << right << adres << "*";
	}
}

string Sayi::sayidegeri()
{
	string sayiDegeri = "";
	for (Basamak* itr = head; itr != NULL; itr = itr->next)
	{
		sayiDegeri += itr->item + '0';
	}
	return sayiDegeri;
}

void Sayi::tekBasamaklariBasaAl()
{
	if(this->Count() == 1) return;
	bool x = false;
	Basamak* itr = head;
	if(itr->item % 2 == 0 && itr->next->item % 2)
	{
		Basamak* temp = itr->next;
		itr->next = temp->next;
		temp->next = itr;
		head = temp;
	}
	for (Basamak* itr = head; size > 2 && itr->next->next != NULL; itr = itr->next)
	{
		if(x)
		{
			x = false;
			itr = head;
			if(itr->item % 2 == 0 && itr->next->item % 2)
			{
				Basamak* temp = itr->next;
				itr->next = temp->next;
				temp->next = itr;
				head = temp;
			}
		}
		if(itr->next->item % 2 == 0 && itr->next->next->item % 2)
		{
			Basamak* temp = itr->next;
			itr->next = temp->next;
			temp->next = itr->next->next;
			itr->next->next = temp;
			x = true;
			itr = head;
		}
	}
}

void Sayi::basamaklariTersle()
{
	if(this->Count() == 1) return;
	Basamak* itr = head;
	Basamak* tail = NULL;
	while(itr->next->next != NULL) itr = itr->next;
	Basamak* temp = itr->next;
	itr->next = temp->next;
	temp->next = head;
	if(tail == NULL) { head = temp; tail = head;}
	for(int i = 0; i < size - 1; i++)
	{
		Basamak* itr = head;
		while(itr->next->next != NULL) itr = itr->next;
		Basamak* temp = itr->next;
		itr->next = temp->next;
		temp->next = tail->next;
		tail->next = temp;
		tail = temp;
	}
}

void Sayi::clear() {
		while (!isEmpty())
			removeAt(0);
	}
Sayi::~Sayi() {
		clear();
	}

