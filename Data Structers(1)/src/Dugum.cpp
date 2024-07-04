/** 
* @file Dugum.cpp
* @description Dugum Dugum sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 14.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include "Dugum.hpp"

Dugum:: Dugum(Sayi* item = NULL, Dugum* next = NULL)
{
    this->item = item;
    this->next = next;
}