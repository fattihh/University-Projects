#ifndef PIRE_H
#define PIRE_H

#include "bocek.h"


struct PIRE {
    Bocek super; 
	void (*yoket)(struct PIRE*);

};

typedef struct PIRE* Pire;


Pire PireOlustur(int);
void PireYoket(Pire);
bool PireYiyebilirMi(Canli);
char* PireGorunum();

#endif // PIRE_H
