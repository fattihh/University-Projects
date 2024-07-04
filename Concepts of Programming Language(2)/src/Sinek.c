#include "sinek.h"
#include <stdlib.h>
#include <string.h>

// Sinek yapısı için yapıcı fonksiyon
Sinek SinekOlustur(int deger) {
    Sinek this = (Sinek)malloc(sizeof(struct SINEK));
    if (this == NULL) return NULL;
    this->super = BocekOlustur(deger);
    if (this->super == NULL) {
        free(this);
        return NULL;
    }
    this->super->super->gorunum = &SinekGorunum;
    this->super->super->yiyebilirMi = &SinekYiyebilirMi;
	this->super->super->tur = strdup("Sinek");
	this->super->super->tur_gorunum = "S";
    this->yoket = &SinekYoket;
    return this;
}

void SinekYoket(Sinek this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}

char* SinekGorunum(Canli this) {
    return this->tur_gorunum;
}

// Sinek için yiyebilirMi fonksiyonu
bool SinekYiyebilirMi(Canli other) {
    // Eğer diğer canlı bir bitki veya pire ise, böcek bu canlıyı yiyebilir.
    if (strcmp(other->tur, "Pire") == 0 || strcmp(other->tur, "Bocek") == 0) {
        return true;
    }
    return false;  // Diğer durumlarda böcek, karşılaştığı canlıyı yiyemez.
}



