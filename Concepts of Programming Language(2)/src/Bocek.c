#include "bocek.h"
#include <stdlib.h>
#include <string.h>

// Bocek yapısı için yapıcı fonksiyon
Bocek BocekOlustur(int deger) {
    Bocek this = (Bocek)malloc(sizeof(struct BOCEK));
    if (this == NULL) return NULL;
    this->super = CanliOlustur("Bocek",deger);
    if (this->super == NULL) {
        free(this);
        return NULL;
    }
    this->super->gorunum = &BocekGorunum;
	this->super->tur_gorunum = "C";
    this->super->yiyebilirMi = &BocekYiyebilirMi;
    this->yoket = &BocekYoket;
    return this;
}

void BocekYoket(Bocek this) {
    if (this == NULL) return;
    this->super->yoket(this->super);
    free(this);
}

char* BocekGorunum(Canli this) {
    return this->tur_gorunum;
}

// Bocek için yiyebilirMi fonksiyonu
bool BocekYiyebilirMi(Canli other) {
    // If the current creature is a bocek, then it cannot eat itself
    if (strcmp(other->tur, "Bocek") == 0 && strcmp(other->tur, "Bocek") == 0) {
        return false;
    }
    // If the other creature is a plant or a pire, then the bocek can eat it
    if (strcmp(other->tur, "Bitki") == 0 || strcmp(other->tur, "Pire") == 0) {
        return true;
    }
    return false;  // In other cases, the bocek cannot eat the other creature
}
