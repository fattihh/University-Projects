#include "bitki.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Bitki yapısı için yapıcı fonksiyon
Bitki BitkiOlustur(int deger) {
    Bitki this = (Bitki)malloc(sizeof(struct BITKI));
    if (this == NULL) return NULL;
    this->super = CanliOlustur("Bitki", deger);
    if (this->super == NULL) {
        free(this);
        return NULL;
    }
    this->super->gorunum = &BitkiGorunum;
	this->super->tur_gorunum = "B";
    this->super->yiyebilirMi = &BitkiYiyebilirMi;
    this->yoket = &BitkiYoket;
    return this;
}

void BitkiYoket(Bitki this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}

char* BitkiGorunum(Canli this) {
    return this->tur_gorunum ;
}

// Bitki için yiyebilirMi fonksiyonu
bool BitkiYiyebilirMi(Canli other) {
	// Eğer diğer canlı bir bitki veya pire ise, böcek bu canlıyı yiyebilir.
    if (strcmp(other->tur, "Sinek") == 0 || strcmp(other->tur, "Pire") == 0) {
        return true;
    }
    return false;  // Diğer durumlarda böcek, karşılaştığı canlıyı yiyemez.
}
