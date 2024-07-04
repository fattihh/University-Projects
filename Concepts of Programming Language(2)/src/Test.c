#include "bitki.h"
#include "bocek.h"
#include "pire.h"
#include "sinek.h"
#include "habitat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
	
// EĞER DİREKT SONUCU GÖRMEK İSTİYORSANIZ HABİTAT.C -> SİMULASYON FONK() -> SATIR 233,234 SİLİNMELİ VEYA YORUMA ALINMALI.
Habitat habitat = HabitatOlustur();
makeHabitat("veri.txt", habitat);
habitatYazdir(habitat);
habitat->simulasyon(habitat);

return 0;
}
