#include "pire.h"
#include <stdlib.h>
#include <string.h>

// Pire yapısı için yapıcı fonksiyon
Pire PireOlustur(int deger) {
    Pire this = (Pire)malloc(sizeof(struct PIRE));
    if (this == NULL) return NULL;
    this->super = BocekOlustur(deger);
    if (this->super == NULL) {
        free(this);
        return NULL;
    }
    this->super->super->gorunum = &PireGorunum;
    this->super->super->yiyebilirMi = &PireYiyebilirMi;
	this->super->super->tur = strdup("Pire");
	this->super->super->tur_gorunum = "P";
    this->yoket = &PireYoket;
    return this;
}

void PireYoket(Pire this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}

char* PireGorunum(Canli this) {
    return 	this->tur_gorunum ;
}

bool PireYiyebilirMi(Canli other) {
    return false;  // Pireler hiçbir şey yiyemez.
}


