#ifndef SINEK_H
#define SINEK_H

#include "bocek.h"

// Sinek yapısı, Bocek'den türemiştir
struct SINEK {
    Bocek super; // Base Bocek yapısını içerir
	void (*yoket)(struct SINEK*);
	
};

typedef struct SINEK* Sinek;

// Sinek için yapıcı ve yıkıcı fonksiyon prototipleri
Sinek SinekOlustur(int);
void SinekYoket(Sinek);
// Sinek için özel fonksiyonlar
bool SinekYiyebilirMi(Canli);
char* SinekGorunum();

#endif // SINEK_H
