/** 
* @file SayilarListesi.cpp
* @description SayilarListesi sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 17-24.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include"SayilarListesi.hpp"

Dugum* SayilarListesi::FindPrevByPosition(int position){
	if(position < 0 || position > size) throw "Index out of range";
	int index=1;
	
	for(Dugum* itr=head;itr!=NULL;itr=itr->next,index++){
		if(position == index) return itr;
	}
	return NULL;
}	
SayilarListesi::SayilarListesi()
{
	head = NULL;	
	size=0;
}
bool SayilarListesi::isEmpty() const
{
	return head == NULL;
}
int SayilarListesi::Count() const
{
	return size;
}
Sayi* SayilarListesi::first(){
	if(isEmpty()) throw "Empty list";
	return head->item;
}
Sayi* SayilarListesi::last(){
	if(isEmpty()) throw "Empty list";
	return FindPrevByPosition(size)->item;
}
void SayilarListesi::add(Sayi* item){
	insert(size,item);
}
void SayilarListesi::insert(int index,Sayi* item){
	if(index == 0) head = new Dugum(item, head);
	else{
		Dugum* prev = FindPrevByPosition(index);
		prev->next = new Dugum(item,prev->next);
	}						
	size++;
}
void SayilarListesi::remove(Sayi* item){
	int position = indexOf(item);
	removeAt(position);			
}
void SayilarListesi::removeAt(int index){
	if(size == 0) throw "Empty list";
	Dugum* del;
	if(index == 0){
		del = head;
		head = head->next;
	}
	else{
		Dugum* prev = FindPrevByPosition(index);
		del = prev->next;
		prev->next = prev->next->next;
	}
	delete del;
	size--;
}
bool SayilarListesi::find(Sayi* item) const{
	for(Dugum* itr=head;itr!=NULL;itr=itr->next){
		if(itr->item == item) return true;
	}
	return false;
}
int SayilarListesi::indexOf(Sayi* item){
	int index=0;
	for(Dugum* itr=head;itr!=NULL;itr=itr->next,index++){
		if(itr->item == item) return index;
	}
	throw "Index out of range";
}

void SayilarListesi::print()
{
	if (head == NULL) cout << "SayilarListesi::Empty list";
	else
	{
		for (Dugum* itr = head; itr != NULL; itr = itr->next) 
		{	
			string kare = "#########";
			string yildiz = "*****";
			satiryaz(kare, yildiz, itr);
			satiryaz(itr);
			satiryaz("---------", yildiz, itr);
			string sayiDegeri = itr->item->sayidegeri();
			satiryaz(sayiDegeri, "basamak",itr);
			satiryaz(kare, yildiz, itr);
			cout << endl;
		}
	}
}

void SayilarListesi::satiryaz(string x, string y, Dugum* itr)
{
	cout << "#" << setw(9) << right << x << "#";
	itr->item->satiryaz(y);
	cout << endl;
}

void SayilarListesi::satiryaz(Dugum* itr)
{
	cout << "#" << setw(9) << right << &itr->item << "#";
	itr->item->satiryaz();
	cout << endl;
}

void SayilarListesi::tekBasamaklariBasaAl()
{
	for (Dugum* itr = head; itr != NULL; itr = itr->next) 
	{
		itr->item->tekBasamaklariBasaAl();
	}	
}

void SayilarListesi::basamaklariTersle()
{
	for (Dugum* itr = head; itr != NULL; itr = itr->next) 
	{
		itr->item->basamaklariTersle();
	}	
}

void SayilarListesi::enBuyukSayiyiSil()
{
	int max = -1;
	for (Dugum* itr = head; itr != NULL; itr = itr->next) 
	{
		string strSayiDegeri = itr->item->sayidegeri();
		int intSayiDegeri = stoi(strSayiDegeri);
		if(intSayiDegeri > max)
		{
			max = intSayiDegeri;
			enBuyukSayi = itr;
		}
	}
	remove(enBuyukSayi->item);
}

void SayilarListesi::clear(){
	while(!isEmpty())
		removeAt(0);			
}


SayilarListesi::~SayilarListesi()
{
	clear();
}
