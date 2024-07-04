#include "canli.h"
#include <stdlib.h>
#include <string.h>
#include<stdio.h>

Canli CanliOlustur(char* tur, int deger) {
    Canli this = (Canli)malloc(sizeof(struct CANLI));
    if (this == NULL) return NULL;
    this->tur = strdup(tur);
    this->deger = deger;
    this->yoket = CanliYoket;
	this->setGorunum=&setGorunum;
    return this;
}

void CanliYoket(Canli this) {
    if (this == NULL) return;
    free(this->tur);
    free(this);
}

char* setGorunum(Canli this)
{
    this->tur_gorunum = "X" ;
}



