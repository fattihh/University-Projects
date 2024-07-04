#ifndef HABITAT_H
#define HABITAT_H
#include "canli.h"
#include "bitki.h"
#include "bocek.h"
#include "pire.h"
#include "sinek.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 

struct HABITAT{
    int HabitatSatirSayisi;
	int HabitatSutunSayisi;
	Canli** hayvanlar;
	int* sutunSayilari; 
	void (*makeHabitat)(const char*,struct HABITAT*);
	void (*HabitatYokEt)(struct HABITAT*);
	void (*habitatYazdir)(struct HABITAT*);
	void (*simulasyon)(struct HABITAT*);

};
typedef struct HABITAT* Habitat;

Habitat HabitatOlustur();

void HabitatYokEt(Habitat);

void makeHabitat();

void simulasyon(Habitat);
void habitatYazdir(Habitat);
#endif