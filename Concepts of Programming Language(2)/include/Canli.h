#ifndef CANLI_H
#define CANLI_H

#include <stdbool.h>

struct CANLI {
    char* tur;
	int deger;
	char* tur_gorunum;
    bool (*yiyebilirMi)();
    char* (*gorunum)();
    void (*yoket)(struct CANLI*);
	char* (*setGorunum)(struct CANLI*);

};
typedef struct CANLI* Canli;
Canli CanliOlustur(char*,int);
char* setGorunum(Canli);
void CanliYoket(Canli);

#endif 
