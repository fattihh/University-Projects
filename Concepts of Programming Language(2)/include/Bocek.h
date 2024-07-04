#ifndef BOCEK_H
#define BOCEK_H

#include "canli.h"
#include <stdio.h>

struct BOCEK {
	Canli super; 
	void (*yoket)(struct BOCEK*);

};

typedef struct BOCEK* Bocek;

Bocek BocekOlustur(int);
void BocekYoket(Bocek);
bool BocekYiyebilirMi(Canli);
char* BocekGorunum();

#endif // BOCEK_H
