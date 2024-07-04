#include "habitat.h"
#include <ctype.h>

Habitat HabitatOlustur()
{
	Habitat this;
	this = (Habitat)malloc(sizeof(struct HABITAT));
	this->makeHabitat=&makeHabitat;
	this->HabitatYokEt=&HabitatYokEt;
	this->habitatYazdir=&habitatYazdir;
	this->simulasyon=&simulasyon;
	return this;
}


void habitatYazdir(Habitat habitat) {
    for (int i = 0; i < habitat->HabitatSatirSayisi; i++) {
        for (int j = 0; j < habitat->sutunSayilari[i]; j++) {
            Canli canli = habitat->hayvanlar[i][j];
            if (canli != NULL) {
                char* gorunum = canli->gorunum(canli);
                printf("%s ",gorunum);
                free(gorunum);  // strdup ile oluşturulan string serbest bırakılmalı
            } else {
                printf("Gecersiz Canli", i + 1, j + 1);
            }
        }
        printf("\n"); // Her satır sonunda bir yeni satır karakteri ekleyin
    }
}


void makeHabitat(const char* fileName, Habitat habitat) {
    FILE* dosya = fopen(fileName, "r");
    if (!dosya) {
        perror("Dosya açılamadı");
        exit(EXIT_FAILURE);
    }

    char *satir = NULL;
    size_t len = 0;
    ssize_t read;
    int satirSayisi = 0, maxSutunSayisi = 0;
    int* sutunSayilari = NULL;
    int* yeniSutunSayilari;

    while ((read = getline(&satir, &len, dosya)) != -1) {
        int sutunSayisi = 0;
        char *baslangic = satir;
        char *token;

        // Boş satırları ve sadece boşluk içeren satırları atlayın
        if (strlen(satir) == 0 || strspn(satir, " \t\r\n") == strlen(satir)) {
            continue;
        }

        while ((token = strtok(baslangic, " \t\n")) != NULL) {
            sutunSayisi++;
            baslangic = NULL;  // strtok için NULL ayarı yapılmalı
        }

        if (sutunSayisi > 0) {
            yeniSutunSayilari = realloc(sutunSayilari, (satirSayisi + 1) * sizeof(int));
            if (!yeniSutunSayilari) {
                perror("Bellek yeniden ayrılamadı");
                free(sutunSayilari);
                fclose(dosya);
                free(satir);
                exit(EXIT_FAILURE);
            }
            sutunSayilari = yeniSutunSayilari;
            sutunSayilari[satirSayisi] = sutunSayisi;
            satirSayisi++;
            if (sutunSayisi > maxSutunSayisi) {
                maxSutunSayisi = sutunSayisi;
            }
        }
    }

    habitat->HabitatSatirSayisi = satirSayisi;
    habitat->HabitatSutunSayisi = maxSutunSayisi;
    habitat->hayvanlar = (Canli**)malloc(satirSayisi * sizeof(Canli*));
    if (!habitat->hayvanlar) {
        perror("Bellek ayrılamadı");
        free(sutunSayilari);
        fclose(dosya);
        exit(EXIT_FAILURE);
    }
    habitat->sutunSayilari = sutunSayilari;
    for (int i = 0; i < satirSayisi; i++) {
        habitat->hayvanlar[i] = (Canli*)calloc(sutunSayilari[i], sizeof(Canli));
        if (!habitat->hayvanlar[i]) {
            perror("Bellek ayrılamadı");
            for (int j = 0; j < i; j++) {
                free(habitat->hayvanlar[j]);
            }
            free(habitat->hayvanlar);
            free(sutunSayilari);
            fclose(dosya);
            exit(EXIT_FAILURE);
        }
    }

    // Dosyayı baştan okuyup nesneleri oluşturma
    rewind(dosya);
    satir = NULL; // getline otomatik olarak bellek ayırır
    int satirIndex = 0;
    while ((read = getline(&satir, &len, dosya)) != -1) {
        if (strlen(satir) == 0 || strspn(satir, " \t\r\n") == strlen(satir)) {
            continue;
        }
        char *baslangic = satir;
        char *token;
        int sutunIndex = 0;

        while ((token = strtok(baslangic, " \t\n")) != NULL) {
            int sayi = atoi(token);
            if (sayi >= 1 && sayi <= 9) {
                habitat->hayvanlar[satirIndex][sutunIndex] = BitkiOlustur(sayi)->super;
            } else if (sayi >= 10 && sayi <= 20) {
                habitat->hayvanlar[satirIndex][sutunIndex] = BocekOlustur(sayi)->super;
            } else if (sayi >= 21 && sayi <= 50) {
                habitat->hayvanlar[satirIndex][sutunIndex] = SinekOlustur(sayi)->super->super;
            } else if (sayi >= 51 && sayi <= 99) {
                habitat->hayvanlar[satirIndex][sutunIndex] = PireOlustur(sayi)->super->super;
            } else {
                habitat->hayvanlar[satirIndex][sutunIndex] = NULL;
            }
            sutunIndex++;
            baslangic = NULL;  // strtok için NULL ayarı yapılmalı
        }
        satirIndex++;
    }

    fclose(dosya);
    free(satir);
}


void simulasyon (Habitat habitat){
    int x=0, y=0;
    int control=0;
    int lastCreatureX = -1;
    int lastCreatureY = -1;
    char* lastCreatureType = NULL;

    printf("Press any key to start the simulation...");
    _getch(); // The program will wait for a key press here
    system("cls"); // Clear the console

    for (int i = 0; i < habitat->HabitatSatirSayisi; i++) {
        for (int j = 0; j < habitat->sutunSayilari[i]; j++) { // Use the correct column count for each row
	
            if (habitat->hayvanlar[i][j]->tur_gorunum == "X" || habitat->hayvanlar[i][j]->tur_gorunum == "\0") {
                continue; // Skip empty places
            }

            if (i==0 && j==0){
                j=1;
            }

            if (habitat->hayvanlar[x][y]->gorunum(habitat->hayvanlar[x][y]) == habitat->hayvanlar[i][j]->gorunum(habitat->hayvanlar[i][j]) && habitat->hayvanlar[x][y]->gorunum(habitat->hayvanlar[x][y])!="X" && habitat->hayvanlar[i][j]->gorunum(habitat->hayvanlar[i][j]) != "X")
            {
                if (habitat->hayvanlar[x][y]->deger==habitat->hayvanlar[i][j]->deger){
                    control=1;
                    habitat->hayvanlar[i][j]->tur_gorunum= "X";
                }
                else if (habitat->hayvanlar[x][y]->deger < habitat->hayvanlar[i][j]->deger){
                    control=1;                 
                    habitat->hayvanlar[x][y]->tur_gorunum= "X";
                    x=i;
                    y=j;
                }
                else
                {
                    control=1;
                    habitat->hayvanlar[i][j]->tur_gorunum = "X";
                }
            }
            else
            {
                char* ilk_kontrol = habitat->hayvanlar[x][y]->gorunum(habitat->hayvanlar[x][y]);
                switch (*ilk_kontrol)
                {
                    case 'B':
                        control=BitkiYiyebilirMi(habitat->hayvanlar[i][j]);
                        if(control){
                            habitat->hayvanlar[i][j]->tur_gorunum = "X";
                        }
                        else{
                            habitat->hayvanlar[x][y]->tur_gorunum = "X";
                             x=i;
                             y=j;
                        }
                        break;
                    case 'C':
                        control=BocekYiyebilirMi(habitat->hayvanlar[i][j]);
                        if(control){
                            habitat->hayvanlar[i][j]->tur_gorunum ="X";
                        }
                        else{
                            habitat->hayvanlar[x][y]->tur_gorunum ="X";
                             x=i;
                             y=j;
                        }
                        break;
                    case 'S':
                        control=SinekYiyebilirMi(habitat->hayvanlar[i][j]);
                        if(control){
                            habitat->hayvanlar[i][j]->tur_gorunum = "X";
                        }
                        else{
                            habitat->hayvanlar[x][y]->tur_gorunum ="X";
                             x=i;
                             y=j;
                        }
                        break;
                    case 'P':
                        control=PireYiyebilirMi(habitat->hayvanlar[i][j]);
                        if(control){
                            habitat->hayvanlar[i][j]->tur_gorunum ="X";
                        }
                        else{
                            habitat->hayvanlar[x][y]->tur_gorunum ="X";
                             x=i;
                             y=j;
                        }
                        break;
                }
				//DİREKT SONUCU GÖRMEK İSTİYORSANIZ BLOĞU SİLİN
				//BLOK BAŞLANGIC
				habitatYazdir(habitat);
                system("cls"); // Clear the console after each eating operation
				//BLOK BİTİS
            }

            if (habitat->hayvanlar[i][j]->tur_gorunum != "X" && habitat->hayvanlar[i][j]->tur_gorunum != "\0") {
                lastCreatureX = i;
                lastCreatureY = j;
                lastCreatureType = habitat->hayvanlar[i][j]->tur;
            }
        }

        printf("\n");
    }

    habitatYazdir(habitat); // Print the habitat only once at the end of the simulation

    // Check if there is only one non-"X" creature left
    int creatureCount = 0;
    for (int i = 0; i < habitat->HabitatSatirSayisi; i++) {
        for (int j = 0; j < habitat->sutunSayilari[i]; j++) { // Use the correct column count for each row
            if (habitat->hayvanlar[i][j]->tur_gorunum != "X" && habitat->hayvanlar[i][j]->tur_gorunum != "\0") {
                creatureCount++;
            }
        }
    }

    for (int i = 0; i < habitat->HabitatSatirSayisi; i++) {
        for (int j = 0; j < habitat->sutunSayilari[i]; j++) { // Use the correct column count for each row
            if (habitat->hayvanlar[i][j] != NULL) {
                habitat->hayvanlar[i][j]->yoket(habitat->hayvanlar[i][j]);
            }
        }
        free(habitat->hayvanlar[i]);
    }
    free(habitat->hayvanlar);
    free(habitat->sutunSayilari);

    if (creatureCount == 1) {
        printf("Last creature is at (%d, %d)\n", lastCreatureX, lastCreatureY);
        printf("Winner is: %s\n", lastCreatureType);
    } else {
        printf("Press any key to continue...");
        _getch(); // The program will wait for a key press here
        system("cls"); // Clear the console
    }
}


void HabitatYokEt(Habitat this) {
    if(this==NULL) return;

    for (int i = 0; i < this->HabitatSatirSayisi; i++) {
        for (int j = 0; j < this->sutunSayilari[i]; j++) {
            if (this->hayvanlar[i][j] != NULL) {
                this->hayvanlar[i][j]->yoket(this->hayvanlar[i][j]);
            }
        }
        free(this->hayvanlar[i]);
    }
    free(this->hayvanlar);
    free(this->sutunSayilari);
    free(this);
}






