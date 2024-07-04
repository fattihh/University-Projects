#ifndef BITKI_H
#define BITKI_H

#include "canli.h"

struct BITKI {
    Canli super;  // Base Canli yapısını içerir
    void (*yoket)(struct BITKI*);
};

typedef struct BITKI* Bitki;

Bitki BitkiOlustur(int);  
void BitkiYoket(Bitki); 
bool BitkiYiyebilirMi(Canli);
char* BitkiGorunum();
#endif 
