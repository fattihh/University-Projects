/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI…...:  1 
**				ÖĞRENCİ ADI...............: Fatih Uçar
**				ÖĞRENCİ NUMARASI.: G211210038
**				DERS GRUBU…………: 2.ÖĞRETİM C GRUBU
****************************************************************************/


#include <iostream>
#include<time.h>
#include<clocale>
#include<iomanip>
#include<cmath>
#include<string.h>
using namespace std;

struct ogrenci
{
    string adi;
    string soyadi;
    int okul_numara;
    int quiz1;
    int quiz2;
    int odev1;
    int odev2;
    int proje;
    int vize;
    int final;
    float basariNotu;
    struct Tarih
{
    int gün, ay, yıl;
};
    Tarih gün, ay, yıl;
};
ogrenci sinif_listesi[100];
int not_kontrol(int Not); 
float basari_notu_hesaplama(ogrenci ogr);
void isim_kontrol(ogrenci& ogr);
string harfNotuHesapla(float Not);
void sinif_listesi_yazdirma(ogrenci* sinif_listesi);
void en_buyuk_notu_hesaplama(ogrenci* sinif_listesi);
void en_dusuk_notu_hesaplama(ogrenci* sinif_listesi);
void sinif_ortalama_hesaplama(ogrenci* sinif_listesi);
void standart_sapma_hesaplama(ogrenci* sinif_listesi);
void basari_notu_aralik(ogrenci* sinif_listesi);
void basari_notu_deger_altı(ogrenci* sinif_listesi);
void basari_notu_deger_üstü(ogrenci* sinif_listesi);
void soyisim_kontrol(ogrenci& ogr);
const int size_sinif_listesi = sizeof(sinif_listesi) / sizeof(ogrenci);  //Sınıf listesinin eleman sayısnı veren degisken.

int main()
{
    setlocale(LC_ALL, "Turkish");
    srand(time(NULL));

    string isimler[30] = { "Fatih","Ahmet","Veli","Yusuf","Cem","Levent","Beyza","Berkant","Yasin",
    "Deniz","Suleyman","Dilan","Sunay","Ezgi","Furkan","Tufan","İbrahim","Cihat","Yusuf","Hamza","Dilara",
    "Emrecan","Oguz","Esra","Aybars","Zafer","Tugba","Semih","Enver","Berke" };

    string soy_isimler[30] = { "Ucar","unal","Yilmaz","Sonmez","Keles","Aslan","Karaca","Kala","Memis","Yazar",
    "Som","Kutbay","Bakirci","Turkmen","Bahar","Yurur","Gor","Bedir","Sonmez","ozturk","celebi","cicek","Akman",
    "urek","Al","Derya","sen","senturk","Soylu","Yilmaz" };
    
    string cevap;
    cout << "Öğrenciler random mu belirlensin manuel olarak mi girmek istersiniz ?(random/manuel)" << endl;
    cout << setw(5); cin >> cevap;
    system("CLS");


    if (cevap == "random")
    {
        int index_sinif_listesi = 0;        
        for (int i = 0; i < 10; i++)    // Listenin ilk 10 elemanini random olarak isim ,soy isim ve not donduren for dongusu.
        {          
            sinif_listesi[index_sinif_listesi].adi = isimler[rand() % 30];  //İsimler listesinden random index secmek için.
            sinif_listesi[index_sinif_listesi].soyadi = soy_isimler[rand() % 30]; //Soyisimler listesinden random index secmek icin.
            sinif_listesi[index_sinif_listesi].okul_numara = rand() % 100;
            sinif_listesi[index_sinif_listesi].gün.gün = rand() % 31;   //Random tarih günü atama.
            sinif_listesi[index_sinif_listesi].ay.ay = rand() % 13;     //Random ay atama
            sinif_listesi[index_sinif_listesi].yıl.yıl = 1990+rand() % 11;  //Random Dogum yılı atama.
            sinif_listesi[i].quiz1 = (rand() % 40) + 1; //1-41 random sayi dondurmek icin.
            sinif_listesi[i].quiz2 = (rand() % 40) + 1;
            sinif_listesi[i].odev1 = (rand() % 40) + 1;
            sinif_listesi[i].odev2 = (rand() % 40) + 1;
            sinif_listesi[i].proje = (rand() % 40) + 1;
            sinif_listesi[i].vize = (rand() % 40) + 1;
            sinif_listesi[i].final = (rand() % 40) + 1;

            cout << setw(8) << sinif_listesi[index_sinif_listesi].adi << setw(5) << "  ";
            cout << sinif_listesi[index_sinif_listesi].soyadi<<endl<<endl;
            cout << setw(20) <<"Okul numarası:  " << sinif_listesi[index_sinif_listesi].okul_numara << endl<<endl;
            cout << setw(20) << "Doğum tarihi :  " << sinif_listesi[index_sinif_listesi].gün.gün<<"."<<sinif_listesi[index_sinif_listesi].ay.ay<<"."<<sinif_listesi[index_sinif_listesi].yıl.yıl << endl << endl;
            cout << setw(20) << "Birinci quiz: " << sinif_listesi[i].quiz1 << setw(10) << endl;
            cout << setw(20) << "İkinci quiz: " << sinif_listesi[i].quiz2 << setw(10) << endl;
            cout << setw(20) << "Birinci  odev: " << sinif_listesi[i].odev1 << setw(10) << endl;
            cout << setw(20) << "İkinci  odev: " << sinif_listesi[i].odev2 << setw(10) << endl;
            cout << setw(20) << " Proje : " << sinif_listesi[i].proje << setw(10) << endl;
            cout << setw(20) << " Vize : " << sinif_listesi[i].vize << setw(10) << endl;
            cout << setw(20) << " Final : " << sinif_listesi[i].final << setw(10) << endl;
            sinif_listesi[i].basariNotu = basari_notu_hesaplama(sinif_listesi[i]); //Basari notlarını tutan degisken.
            cout << "Basari puani "<<basari_notu_hesaplama(sinif_listesi[i]);
            cout << endl;
            cout << "Harf notu : " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i]));
            cout << endl << endl;

            cout << endl << endl;
            index_sinif_listesi += 1;
        }

        int basla1 = 40;    //random sayilari 40-70 arasi yapmak icin .
        for (int i = 10; i < 60; i++)    // Listenin ilk 10-60 elemanini random olarak isim ,soy isim ve not donduren for dongusu.
        {           
            sinif_listesi[index_sinif_listesi].adi = isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].soyadi = soy_isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].okul_numara = rand() % 100;
            sinif_listesi[index_sinif_listesi].gün.gün = rand() % 31;   //Random tarih günü atama.
            sinif_listesi[index_sinif_listesi].ay.ay = rand() % 13;     //Random ay atama
            sinif_listesi[index_sinif_listesi].yıl.yıl = 1990 + rand() % 11;  //Random Dogum yılı atama.
            sinif_listesi[i].quiz1 = basla1 + (rand() % 30);    //40-70 arasi not dondurur.
            sinif_listesi[i].quiz2 = basla1 + (rand() % 30);
            sinif_listesi[i].odev1 = basla1 + (rand() % 30);
            sinif_listesi[i].odev2 = basla1 + (rand() % 30);
            sinif_listesi[i].proje = basla1 + (rand() % 30);
            sinif_listesi[i].vize = basla1 + (rand() % 30);
            sinif_listesi[i].final = basla1 + (rand() % 30);

            cout << setw(8) << sinif_listesi[index_sinif_listesi].adi << setw(5) << "  ";
            cout << sinif_listesi[index_sinif_listesi].soyadi << endl <<endl;
            cout << setw(20) << "Okul numarası:  " << sinif_listesi[index_sinif_listesi].okul_numara << endl << endl;
            cout << setw(20) << "Doğum tarihi :  " << sinif_listesi[index_sinif_listesi].gün.gün << "." << sinif_listesi[index_sinif_listesi].ay.ay << "." << sinif_listesi[index_sinif_listesi].yıl.yıl << endl << endl;
            cout << setw(20) << "Birinci quiz: " << sinif_listesi[i].quiz1 << setw(10) << endl;
            cout << setw(20) << "İkinci quiz: " << sinif_listesi[i].quiz2 << setw(10) << endl;
            cout << setw(20) << "Birinci  odev: " << sinif_listesi[i].odev1 << setw(10) << endl;
            cout << setw(20) << "İkinci  odev: " << sinif_listesi[i].odev2 << setw(10) << endl;
            cout << setw(20) << " Proje : " << sinif_listesi[i].proje << setw(10) << endl;
            cout << setw(20) << " Vize : " << sinif_listesi[i].vize << setw(10) << endl;
            cout << setw(20) << " Final : " << sinif_listesi[i].final << setw(10) << endl;
            sinif_listesi[i].basariNotu = basari_notu_hesaplama(sinif_listesi[i]); //Basari notlarını tutan degisken.
            cout << "Basari puani " << basari_notu_hesaplama(sinif_listesi[i]);          
            cout << endl;
            cout << "Harf notu :  " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i]));
            cout << endl << endl;
            
            index_sinif_listesi += 1;
            
        }

        int basla2 = 70;    //random sayilari 40-70 arasi yapmak icin .
        for (int i = 60; i < 75; i++)    // Listenin ilk 60-75 elemanini random olarak isim ,soy isim ve not donduren for dongusu.
        {           
            sinif_listesi[index_sinif_listesi].adi = isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].soyadi = soy_isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].okul_numara = rand() % 100;
            sinif_listesi[index_sinif_listesi].gün.gün = rand() % 31;   //Random tarih günü atama.
            sinif_listesi[index_sinif_listesi].ay.ay = rand() % 13;     //Random ay atama
            sinif_listesi[index_sinif_listesi].yıl.yıl = 1990 + rand() % 11;  //Random Dogum yılı atama.
            sinif_listesi[i].quiz1 = basla2 + (rand() % 10); //sayıları 70-80 arası yapmak için.
            sinif_listesi[i].quiz2 = basla2 + (rand() % 10);
            sinif_listesi[i].odev1 = basla2 + (rand() % 10);
            sinif_listesi[i].odev2 = basla2 + (rand() % 10);
            sinif_listesi[i].proje = basla2 + (rand() % 10);
            sinif_listesi[i].vize = basla2 + (rand() % 10);
            sinif_listesi[i].final = basla2 + (rand() % 10);

            cout << setw(8) << sinif_listesi[index_sinif_listesi].adi << setw(5) << "  ";
            cout << sinif_listesi[index_sinif_listesi].soyadi << endl << endl;
            cout << setw(20) << "Okul numarası:  " << sinif_listesi[index_sinif_listesi].okul_numara << endl << endl;
            cout << setw(20) << "Doğum tarihi :  " << sinif_listesi[index_sinif_listesi].gün.gün << "." << sinif_listesi[index_sinif_listesi].ay.ay << "." << sinif_listesi[index_sinif_listesi].yıl.yıl << endl << endl;
            cout << setw(20) << "Birinici quiz: " << sinif_listesi[i].quiz1 << setw(10) << endl;
            cout << setw(20) << "İkinci quiz: " << sinif_listesi[i].quiz2 << setw(10) << endl;
            cout << setw(20) << "Birinci  odev: " << sinif_listesi[i].odev1 << setw(10) << endl;
            cout << setw(20) << "İkinci  odev: " << sinif_listesi[i].odev2 << setw(10) << endl;
            cout << setw(20) << " Proje : " << sinif_listesi[i].proje << setw(10) << endl;
            cout << setw(20) << " Vize : " << sinif_listesi[i].vize << setw(10) << endl;
            cout << setw(20) << " Final : " << sinif_listesi[i].final << setw(10) << endl;
            sinif_listesi[i].basariNotu = basari_notu_hesaplama(sinif_listesi[i]); //Basari notlarını tutan degisken.
            cout << "Basari puani " << basari_notu_hesaplama(sinif_listesi[i]);
            cout << endl;
            cout << "Harf notu : " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i]));
            cout << endl << endl;            
            index_sinif_listesi += 1;
           
        }

        int basla3 = 80;    //random sayilari 80-100 arasi yapmak icin .
        for (int i = 75; i < 100; i++)    // Listenin ilk 75-100 elemanini random olarak isim ,soy isim ve not donduren for dongusu.
        {            
            sinif_listesi[index_sinif_listesi].adi = isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].soyadi = soy_isimler[rand() % 30];
            sinif_listesi[index_sinif_listesi].okul_numara = rand() % 100;
            sinif_listesi[index_sinif_listesi].gün.gün = rand() % 31;   //Random tarih günü atama.
            sinif_listesi[index_sinif_listesi].ay.ay = rand() % 13;     //Random ay atama
            sinif_listesi[index_sinif_listesi].yıl.yıl = 1990 + rand() % 11;  //Random Dogum yılı atama.
            sinif_listesi[i].quiz1 = basla3 + (rand() % 20);    //Sayıları 80-100 arası yapmak için.
            sinif_listesi[i].quiz2 = basla3 + (rand() % 20);
            sinif_listesi[i].odev1 = basla3 + (rand() % 20);
            sinif_listesi[i].odev2 = basla3 + (rand() % 20);
            sinif_listesi[i].proje = basla3 + (rand() % 20);
            sinif_listesi[i].vize = basla3 + (rand() % 20);
            sinif_listesi[i].final = basla3 + (rand() % 20);

            cout << setw(8) << sinif_listesi[index_sinif_listesi].adi << setw(5) << "  ";
            cout << sinif_listesi[index_sinif_listesi].soyadi << endl << endl;
            cout << setw(20) << "Okul numarası:  " << sinif_listesi[index_sinif_listesi].okul_numara << endl << endl;
            cout << setw(20) << "Doğum tarihi :  " << sinif_listesi[index_sinif_listesi].gün.gün << "." << sinif_listesi[index_sinif_listesi].ay.ay << "." << sinif_listesi[index_sinif_listesi].yıl.yıl << endl << endl;
            cout << setw(20) << "Birinici quiz: " << sinif_listesi[i].quiz1 << setw(10) << endl;
            cout << setw(20) << "İkinci quiz: " << sinif_listesi[i].quiz2 << setw(10) << endl;
            cout << setw(20) << "Birinci  odev: " << sinif_listesi[i].quiz2 << setw(10) << endl;
            cout << setw(20) << "İkinci  odev: " << sinif_listesi[i].odev2 << setw(10) << endl;
            cout << setw(20) << " Proje : " << sinif_listesi[i].proje << setw(10) << endl;
            cout << setw(20) << " Vize : " << sinif_listesi[i].vize << setw(10) << endl;
            cout << setw(20) << " Final : " << sinif_listesi[i].final << setw(10) << endl;
            sinif_listesi[i].basariNotu = basari_notu_hesaplama(sinif_listesi[i]); //Basari notlarını tutan degisken.
            cout << "Basari puani " << basari_notu_hesaplama(sinif_listesi[i]);
            cout << endl;
            cout << "Harf notu : " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i]));
            cout << endl << endl;
            index_sinif_listesi += 1;
        }
        
    }

    else if (cevap == "manuel")
    {
        int index_sinif_listesi = 0;   // manuel olarak yazdigimiz her ogrencinin indexini tutan degisken.
        int cevap;  //secenekler icin sorulan cevap degiskeni.
        for (int i = 0; i < 20; i++)     // manuel olarak yazdigimiz her ogrencinin indexini tutan for dongusu.
        {
            cout << "Öğrencinin ismini giriniz : ";
            cin >> sinif_listesi[i].adi;
            isim_kontrol(sinif_listesi[i]);
            cout << "Öğrencinin soyismini giriniz : ";
            cin >> sinif_listesi[i].soyadi;
            soyisim_kontrol(sinif_listesi[i]);
            cout << "Birinci quizin notunu giriniz : ";
            cin >> sinif_listesi[i].quiz1;
            sinif_listesi[i].quiz1 = not_kontrol(sinif_listesi[i].quiz1);
            cout << "İkinici quizin notunu giriniz : ";
            cin >> sinif_listesi[i].quiz2;
            sinif_listesi[i].quiz2 = not_kontrol(sinif_listesi[i].quiz2);
            cout << "Birinci odevin notunu giriniz : ";
            cin >> sinif_listesi[i].odev1;
            sinif_listesi[i].odev1 = not_kontrol(sinif_listesi[i].odev1);
            cout << "İkinci odevin notunu giriniz : ";
            cin >> sinif_listesi[i].odev2;
            sinif_listesi[i].odev2 = not_kontrol(sinif_listesi[i].odev2);
            cout << "Proje notunu giriniz : ";
            cin >> sinif_listesi[i].proje;
            sinif_listesi[i].proje = not_kontrol(sinif_listesi[i].proje);
            cout << "Vize notunu giriniz :";
            cin >> sinif_listesi[i].vize;
            sinif_listesi[i].vize = not_kontrol(sinif_listesi[i].vize);
            cout << "Final notunu giriniz : ";
            cin >> sinif_listesi[i].final;
            sinif_listesi[i].final = not_kontrol(sinif_listesi[i].final);

            sinif_listesi[i].basariNotu=basari_notu_hesaplama(sinif_listesi[i]); //Basarı notlarını tutan degisken.
            system("CLS");
            sinif_listesi[index_sinif_listesi] = sinif_listesi[i];
            system("CLS");
            index_sinif_listesi += 1;
        }

        cout << "Asagidaki seceneklerden hangisi yapmak istersiniz ? " << endl;
        cout << "Sinif listesi yazdirma.(1)" << endl;
        cout << "Sinifin en yuksek notunu yazdirma.(2)" << endl;
        cout << "Sinifin en dusuk notunu yazdirma.(3)" << endl;
        cout << "Sinifin ortalamasini hesaplama.(4)" << endl;
        cout << "Sinifin standart sapmasini hesaplama(5)" << endl;
        cout << "Basari notu 90-70 arasi olanlari yazdir(6)." << endl;
        cout << "Basari notu 70'ten kucuk olanlari yazdir(7)." << endl;
        cout << "Basari notu 80'den buyuk olanlari yazdir.(8)" << endl;

        cin >> cevap;
        system("CLS");
        switch (cevap)      //Seceneklere gore fonksiyon donduren switch case yapisi.
        {
        case 1:
            sinif_listesi_yazdirma(sinif_listesi);
            break;
        case 2:
            en_buyuk_notu_hesaplama(sinif_listesi);
            break;
        case 3:
            en_dusuk_notu_hesaplama(sinif_listesi);
            break;
        case 4:
            sinif_ortalama_hesaplama(sinif_listesi);
            break;
        case 5:
            standart_sapma_hesaplama(sinif_listesi);
            break;
        case 6:
            basari_notu_aralik(sinif_listesi);
            break;
        case 7:
            basari_notu_deger_altı(sinif_listesi);
            break;
        case 8:
            basari_notu_deger_üstü(sinif_listesi);
            break;
        default:
            cout << "Lutfen 1 ve 8 arasinda bir sayi giriniz.";
            cin >> cevap;
            break;
        }

    }
    else   //random ve manuel secenekleri disinda bir cevap girilirse verilen cevap.        
    {
        cout << "Lutfen gecerli bir cevap giriniz.";
    }
}

float basari_notu_hesaplama(ogrenci ogr)
{
    float basari_notu = 0;  //yil sonu basari notunu tutan degisken.
    float yil_ici = (ogr.quiz1 * (7 / float(100))) + (ogr.quiz2 * (7 / float(100))) + (ogr.odev1 * (1 / float(10))) +
        (ogr.odev2 * (1 / float(10))) + (ogr.proje * (16 / float(100))) + (ogr.vize * (1 / float(2)));//yil ici notu hesaplayan denklem
    return basari_notu += (yil_ici * (55 / float(100))) + (ogr.final * (45 / float(100))); //fonkisyonun dondurdugu deger.

}
int not_kontrol(int Not)
{
    while (Not < 0 || Not > 100)//notların 0 ve 100 arasinda degilse tekrar not donduren dongu.
    {
        cout << "Gecersiz not araligi tekrar deneyin.";                       
        cin >> Not;
    }
    return Not;
}
string harfNotuHesapla(float Not)
{
    if (Not >= 90) return " Harf notunuz AA.";      //Harf notlarini belirli bir aralikta donduren fonksiyon.
    else if (Not >= 80) return " Harf notununz BA.";
    else if (Not >= 70) return " Harf notununz BB.";
    else if (Not >= 60) return " Harf notununz CB.";
    else if (Not >= 55) return " Harf notununz CC.";
    else if (Not >= 45) return " Harf notununz DC.";
    else if (Not >= 40) return " Harf notununz DD.";
    else return "Kaldininz.";           
}
void sinif_listesi_yazdirma(ogrenci* sinif_listesi)
{
    string cevap;
    for (int i = 0; i < 20; i++)   // ogrenci bilgilerini yazdıran for dongusu.
    {
        cout << setw(10) << sinif_listesi[i].adi << "\t";
        cout << setw(10) << sinif_listesi[i].soyadi << endl << endl;
        cout << setw(10) << "Birinci quiz: " << sinif_listesi[i].quiz1 << setw(10) << endl;
        cout << setw(10) << "İkinci quiz: " << sinif_listesi[i].quiz2 << setw(10) << endl;
        cout << setw(10) << "Birinci  odev: " << sinif_listesi[i].odev1 << setw(10) << endl;
        cout << setw(10) << "İkinci  odev: " << sinif_listesi[i].odev2 << setw(10) << endl;
        cout << setw(10) << " Proje : " << sinif_listesi[i].proje << setw(10) << endl;
        cout << setw(10) << " Vize : " << sinif_listesi[i].vize << setw(10) << endl;
        cout << setw(10) << " Final : " << sinif_listesi[i].final << setw(10) << endl;
        cout << "Basari notunuz : " << basari_notu_hesaplama(sinif_listesi[i]); cout << endl;
        cout << "Harf notu " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i])) << endl << endl;
    }
    system("pause");
    system("CLS");

    cout << "Baska bir liste daha yazmak ister misiniz?(evet/hayir) ";
    cin >> cevap;
    if (cevap == "evet")        //cevaba gore tekrar bilgi isteyen kosul.
    {
        for (int i = 20; i < 40; i++)   // ogrenci bilgilerini isteyen for dongusu.
        {
            cout << "ogrencinin ismini giriniz : ";
            cin >> sinif_listesi[i].adi;
            isim_kontrol(sinif_listesi[i]);
            cout << "ogrencinin Soyismini giriniz : ";
            cin >> sinif_listesi[i].soyadi;
            soyisim_kontrol(sinif_listesi[i]);
            cout << "Birinci quizin notunu giriniz : ";
            cin >> sinif_listesi[i].quiz1;
            sinif_listesi[i].quiz1=not_kontrol(sinif_listesi[i].quiz1);
            cout << "İkinici quizin notunu giriniz : ";
            cin >> sinif_listesi[i].quiz2;
            sinif_listesi[i].quiz2 = not_kontrol(sinif_listesi[i].quiz2);
            cout << "Birinci odevin notunu giriniz : ";
            cin >> sinif_listesi[i].odev1;
            sinif_listesi[i].odev1 = not_kontrol(sinif_listesi[i].odev1);
            cout << "İkinci odevin notunu giriniz : ";
            cin >> sinif_listesi[i].odev2;
            sinif_listesi[i].odev2 = not_kontrol(sinif_listesi[i].odev2);
            cout << "Proje notunu giriniz : ";
            cin >> sinif_listesi[i].proje;
            sinif_listesi[i].proje = not_kontrol(sinif_listesi[i].proje);
            cout << "Vize notunu giriniz :";
            cin >> sinif_listesi[i].vize;
            sinif_listesi[i].vize = not_kontrol(sinif_listesi[i].vize);
            cout << "Final notunu giriniz : ";
            cin >> sinif_listesi[i].final;
            sinif_listesi[i].final = not_kontrol(sinif_listesi[i].final);
            system("CLS");
        }
        for (int i = 20; i < 40; i++) //Diger listenin yazilmasini saglayan for dongusu.
        {
            cout << sinif_listesi[i].adi << "   ";
            cout << sinif_listesi[i].soyadi << endl<<endl;
            cout << setw(20) << "Birinci quiz " << sinif_listesi[i].quiz1 << setw(8) << endl;
            cout << setw(20) << "İkinci quiz " << sinif_listesi[i].quiz2 << setw(8) << endl;
            cout << setw(20) << "Birinici odev " << sinif_listesi[i].odev1 << setw(8) << endl;
            cout << setw(20) << "İkinci odev " << sinif_listesi[i].odev2 << setw(8) << endl;
            cout << setw(20) << "Proje " << sinif_listesi[i].proje << setw(8) << endl;
            cout << setw(20) << "Vize " << sinif_listesi[i].vize << setw(8) << endl;
            cout << setw(20) << "Final " << sinif_listesi[i].final << setw(8) << endl;
            cout << "Basari puani " << basari_notu_hesaplama(sinif_listesi[i]) << endl;
            cout << "Harf notu " << harfNotuHesapla(basari_notu_hesaplama(sinif_listesi[i])) << endl << endl;
            cout << endl;
        }
    }

}
void en_buyuk_notu_hesaplama(ogrenci* sinif_listesi)
{
    int en_buyuk_not = 0;   //En buyuk not degerini tutan degisken.
    for (int i = 0; i < 20; i++)     //Tum sinifi gezmesi icin gerekli dongu.
    {
        en_buyuk_not = sinif_listesi[i].quiz1;
        if (sinif_listesi[i].quiz2 > sinif_listesi[i].quiz1)  //Kosullar.
        {
            en_buyuk_not = sinif_listesi[i].quiz2;  //Eger quiz2 quiz1 den buyukse tekrar atama yapar.
        }
        if (sinif_listesi[i].odev1 > sinif_listesi[i].quiz2)
        {
            en_buyuk_not = sinif_listesi[i].odev1;
        }
        if (sinif_listesi[i].odev2 > sinif_listesi[i].odev1)
        {
            en_buyuk_not = sinif_listesi[i].odev2;
        }
        if (sinif_listesi[i].proje > sinif_listesi[i].odev2)
        {
            en_buyuk_not = sinif_listesi[i].proje;
        }
        if (sinif_listesi[i].vize > sinif_listesi[i].proje)
        {
            en_buyuk_not = sinif_listesi[i].vize;
        }
        if (sinif_listesi[i].final > sinif_listesi[i].vize)
        {
            en_buyuk_not = sinif_listesi[i].final;
        }
    }
    cout << "Sinifin en yuksek notu : " << en_buyuk_not;
}
void en_dusuk_notu_hesaplama(ogrenci* sinif_listesi)
{
    int en_dusuk_not = 100; //En dusuk not degerini tutan degisken.
    for (int i = 0; i < 20; i++)     //Tum sinifi gezmesi icin gerekli dongu
    {
        en_dusuk_not = sinif_listesi[i].quiz1;
        if (sinif_listesi[i].quiz2 < sinif_listesi[i].quiz1)
        {
            en_dusuk_not = sinif_listesi[i].quiz2;   //Eger quiz2 quiz1 den kucukse gerekli atamayi yapan kosul.
        }
        if (sinif_listesi[i].odev1 < sinif_listesi[i].quiz2)
        {
            en_dusuk_not = sinif_listesi[i].odev1;
        }
        if (sinif_listesi[i].odev2 < sinif_listesi[i].odev1)
        {
            en_dusuk_not = sinif_listesi[i].odev2;
        }
        if (sinif_listesi[i].proje < sinif_listesi[i].odev2)
        {
            en_dusuk_not = sinif_listesi[i].proje;
        }
        if (sinif_listesi[i].vize < sinif_listesi[i].proje)
        {
            en_dusuk_not = sinif_listesi[i].vize;
        }
        if (sinif_listesi[i].final < sinif_listesi[i].vize)
        {
            en_dusuk_not = sinif_listesi[i].final;
        }
    }
    cout << "Sinifin en dusuk notu: " << en_dusuk_not;

}
void sinif_ortalama_hesaplama(ogrenci* sinif_listesi)
{
    float ortalama_toplam = 0;  //sinifin ortalamasini tutan degisken.
    for (int i = 0; i < 20; i++) //Tum sinifin notlarini donduren for dongusu.
    {
        float ortalama = (sinif_listesi[i].quiz1) + (sinif_listesi[i].quiz2) + (sinif_listesi[i].odev1) + (sinif_listesi[i].odev2) +
            (sinif_listesi[i].proje) + (sinif_listesi[i].vize) + (sinif_listesi[i].final);
        ortalama_toplam += ortalama;
    }
    cout << "Sinifin ortalamasi " << ortalama_toplam / (7 * 20); //Ortalamanin kisi sayisina bolumu.

}
void standart_sapma_hesaplama(ogrenci* sinif_listesi) {
    float toplam = 0.0;
    float aritmetik_ortalama;
    float sinifin_standart_sapmasi = 0.0;

    for (int i = 0; i < 20; ++i)     //Sinifin notlarini donduren dongu.
    {
        toplam += (sinif_listesi[i].quiz1) + (sinif_listesi[i].quiz2) + (sinif_listesi[i].odev1) + (sinif_listesi[i].odev2) +
            (sinif_listesi[i].proje) + (sinif_listesi[i].vize) + (sinif_listesi[i].final);
    }

    aritmetik_ortalama = toplam / (7 * 20);  //Aritmetik ortalamayi veren degisken.

    float sinif_varyansi = 0;
    for (int i = 0; i < 20; i++) //sinif varyansini tutan dongu.
    {
        sinif_varyansi += pow(sinif_listesi[i].quiz1 - aritmetik_ortalama, 2) + pow(sinif_listesi[i].quiz2 - aritmetik_ortalama, 2) +
            pow(sinif_listesi[i].odev1 - aritmetik_ortalama, 2) + pow(sinif_listesi[i].odev2 - aritmetik_ortalama, 2) +
            pow(sinif_listesi[i].proje - aritmetik_ortalama, 2) + pow(sinif_listesi[i].vize - aritmetik_ortalama, 2) +
            pow(sinif_listesi[i].vize - aritmetik_ortalama, 2) + pow(sinif_listesi[i].final - aritmetik_ortalama, 2);

    }

    float karekok = sinif_varyansi / (7 * 20) - 1;   //Sinif varyansinin karekokunu almak icin 
    sinifin_standart_sapmasi = sqrt(karekok);
    cout << "Sinifin standart sapmasi " << sinifin_standart_sapmasi;

}
void basari_notu_aralik(ogrenci* sinif_listesi)
{
    for (int i = 0; i < 20; i++) //Öğrencilerin notunda gezinmek için gerekli for döngüsü.
    {
        if (sinif_listesi[i].basariNotu >= 70 && sinif_listesi[i].basariNotu <= 90)
            cout << sinif_listesi[i].adi <<" " << sinif_listesi[i].soyadi << " isimli ögrencinin basarı notu 90-70 arasıdır." << endl;
    }
}
void isim_kontrol(ogrenci& ogr) {
    for (int i = 0; i < ogr.adi.length(); i++) //İsimde gezinmemizi sağlayan for döngüsü.
    {
        if (ogr.adi[i] - '0' >= 0 && ogr.adi[i] - '0' < 10 ) //İsimde sayı olup olmadığını kontrol eden for döngüsü.
        {
            cout << "Geçersiz isim.İsim sayı içeremez."<<endl;
            cin >> ogr.adi;
            i = -1;
        }
    }
}
void basari_notu_deger_altı(ogrenci* sinif_listesi)
{
    for (int i = 0; i < 20; i++)     //Basari notlarında gezinmemizi sağlayan for döngüsü.
    {
        if (sinif_listesi[i].basariNotu <= 70 )
            cout << sinif_listesi[i].adi << " " << sinif_listesi[i].soyadi << " isimli ögrencinin basarı notu 70'in altındadır." << endl;
    }
}
void basari_notu_deger_üstü(ogrenci* sinif_listesi)
{
    for (int i = 0; i < 20; i++)     //Basari notlarında gezinmemizi sağlayan for döngüsü.
    {
        if (sinif_listesi[i].basariNotu >= 80)
            cout << sinif_listesi[i].adi << " " << sinif_listesi[i].soyadi << " isimli ögrencinin basarı notu 80'in üstündedir." << endl;
    }
}
void soyisim_kontrol(ogrenci& ogr)
{
    for (int i = 0; i < ogr.soyadi.length(); i++)//Soyisimde gezinmemizi sağlayan for döngüsü.
    {

        if (ogr.soyadi[i] - '0' >= 0 && ogr.soyadi[i] - '0' < 10)   //Soyisimde sayı olup olmadığını kontrol eden döngü.
        {
            cout << "Geçersiz soyisim.Soyisim sayı içeremez." << endl;
            cin >> ogr.soyadi;
            i = -1;
        }

    }
}