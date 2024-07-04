/** 
* @file Basamak.cpp
* @description Basamak Dugum sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 14.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/


#include "Basamak.hpp"

Basamak::Basamak(const int& item=0 , Basamak* next = NULL)
{
    this->item=item;
    this->next=next;
}