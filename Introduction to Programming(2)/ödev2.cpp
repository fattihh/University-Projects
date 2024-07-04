/****************************************************************************
**					SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				    BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				          PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				ÖDEV NUMARASI…...: 2
**				ÖĞRENCİ ADI...............: Fatih UÇAR
**				ÖĞRENCİ NUMARASI.: G211210038
**				DERS GRUBU…………: 2.Öğretim C grubu
****************************************************************************/


#include <iostream>

#include<iomanip> //setw fonk kullanmak için.

#include<cmath> //Matematik fonk kullanmak için.

using namespace std;

class Karmasik  //Karmasık sayı sınıfı olusturdum.
{
private://Degiskenleri private icine aldım.
    double Gercel;
    double Sanal;

public:
    Karmasik()//Default constructor karmasik sayiyi 0+0i baslatmak icin.
    {
        Gercel = 0, Sanal = 0;
    }

    Karmasik(int gercel, int sanal)// Parametreli baslatmak icin constructor.
    {
        Gercel = gercel;
        Sanal = sanal;
    }

    void set()  //Verileri almak için set fonk.
    {
        cout << "Sayinin gercel kismini giriniz."; cin >> Gercel;
        cout << "Sayinin sanal kismini giriniz."; cin >> Sanal;
    }

    void get()  //Verileri yazdırmak için get fonk.
    {
        cout << "Karmasik sayi " << Gercel << " + " << Sanal << "i " << endl;
    }

    void yazdir()//Karmasık sayıları düzgün yazdırmak icin if else blogu. 
    {
        if (Sanal < 0)
        {
            if (Sanal == -1)
            {
                cout << "Karmasik sayi : " << Gercel << "-i" << endl;
            }
            else
            {
                cout << "Karmasik sayi : " << Gercel << Sanal << "i" << endl;
            }
        }
        else
        {
            if (Sanal == 1)
            {
                cout << "Karmasik sayi : " << Gercel << " + i" << endl;
            }
            else
            {
                cout << "Karmasik sayi : " << Gercel << " + " << Sanal << "i" << endl;
            }
        }
    }


    Karmasik operator+(Karmasik sayi1)// + overloading .
    {
        Karmasik toplam;  //Toplam objesi olusturup 2 objenin gercel ve sanallarını toplam objesine atadım.
        toplam.Gercel = Gercel + sayi1.Gercel;
        toplam.Sanal = Sanal + sayi1.Sanal;
        return toplam;
    }

    Karmasik operator-(Karmasik sayi1)
    {
        Karmasik sonuc; //Sonuc objesi olusturup 2 objenin gercel ve sanallarını sonuc objesine atadım.
        sonuc.Gercel = Gercel - sayi1.Gercel;
        sonuc.Sanal = Sanal - sayi1.Sanal;
        return sonuc;
    }

    Karmasik operator*(Karmasik sayi1)
    {
        Karmasik sonuc;     //Sonuc objesi olusturup 2 objenin gercel ve sanallarını sonuc objesine atadım.
        sonuc.Gercel = Gercel * sayi1.Gercel - Sanal * sayi1.Sanal;
        sonuc.Sanal = Gercel * sayi1.Sanal + Sanal * sayi1.Gercel;
        return sonuc;
    }

    Karmasik operator/(Karmasik sayi1)
    {
        Karmasik eslenik = sayi1;  //esleniğe sayı1 i atadım.
        eslenik.Sanal *= -1;    //esleniği bulmak için sanalı -1 ile çarptım.
        *this *= eslenik;   //esleniği objeye atadım.
        double payda = (sayi1.Gercel * eslenik.Gercel) - (sayi1.Sanal * eslenik.Sanal);
        this->Gercel /= payda;
        this->Sanal /= payda;
        return *this; //objeyi returnledim.
    }
    Karmasik& operator+=(const Karmasik& sayi1)//Karmasık sınıfının adresine gidip üzerine veri ekleme.
    {
        this->Gercel += sayi1.Gercel;
        this->Sanal += sayi1.Sanal;
        return *this;
    }
    Karmasik& operator-=(const Karmasik& sayi1)//Karmasık sınıfının adresine gidip veri cıkartma ekleme.
    {
        this->Gercel -= sayi1.Gercel;
        this->Sanal -= sayi1.Sanal;
        return *this;
    }

    Karmasik& operator*=(const Karmasik& sayi1)//Karmasık sınıfının adresine gidip çarpma.
    {
        Karmasik sonuc;
        sonuc.Gercel = (sayi1.Gercel * this->Gercel) - (sayi1.Sanal * this->Sanal);
        sonuc.Sanal = (sayi1.Sanal * this->Gercel) + (sayi1.Gercel * this->Sanal);
        *this = sonuc;
        return *this;
    }

    Karmasik& operator/=(const Karmasik& sayi1)//Karmasık sınıfının adresine gidip veri cıkartma ekleme.
    {
        Karmasik eslenik = sayi1;
        eslenik.Sanal *= -1;
        *this *= eslenik;
        double payda = (sayi1.Gercel * eslenik.Gercel) - (sayi1.Sanal * eslenik.Sanal);
        this->Gercel /= payda;
        this->Sanal /= payda;
        return *this;
    }

    void toplamaTers(Karmasik* sayi1) //Karmasık sayının adresine gidip toplamaya göre tersini alma.
    {
        sayi1->Gercel = -(sayi1->Gercel);
        sayi1->Sanal = -(sayi1->Sanal);
    }


    void carpmaTers(Karmasik* sayi1)//Karmasık sayının adresine gidip çarpmaya göre tersini alma.
    {
        sayi1->Gercel = 1 / (sayi1->Gercel);
        sayi1->Sanal = 1 / (sayi1->Sanal);
    }


    float ikiNoktAci(int nokta1x, int nokta1y, int nokta2x, int nokta2y)// İki nokta arasındaki açıyı hesaplamak için fonk.
    {
        int yFark = nokta2y - nokta1y; // y noktaları arasındaki fark
        int xFark = nokta2x - nokta1x; // x noktaları arasındaki fark
        float derece = atan2(yFark, xFark) * 180 / 3.141; // dereceye dönüştürme
        return derece;
    }


    void kutupsal(Karmasik* sayi1)
    {
        sayi1->set();

        float uzaklık = sqrt((sayi1->Gercel * sayi1->Gercel) + (sayi1->Sanal * sayi1->Sanal)); //Sanal ve Gercelin karelerinin karekökü.

        cout << "Sayinin kutupsal gösterimi:  " << "(" << uzaklık * (cos(ikiNoktAci(0, 0, sayi1->Gercel, sayi1->Sanal))) << ")";
        cout << "." << "i" << "(" << uzaklık * (sin(ikiNoktAci(0, 0, sayi1->Gercel, sayi1->Sanal))) << ")" << endl;
    }
};


int main()
{
    setlocale(LC_ALL, "Turkish");
    int secenek;
    char cevap = 'e';
    do
    {
        cout << setw(35) << "********** MENU **************" << endl << endl;
        cout << "Hangi islemi yapmak istersiniz ?" << setw(20) << endl << endl;
        cout << setw(20) << "(1)    Karmasik sayilari topla" << setw(20) << endl;
        cout << setw(20) << "(2)    Karmasik sayinin toplamaya gore tersini bul." << setw(20) << endl;
        cout << setw(20) << "(3)    Karmasik sayilari cikar" << setw(20) << endl;
        cout << setw(20) << "(4)    Karmasik sayilari carp" << setw(20) << endl;
        cout << setw(20) << "(5)    Karmasik sayinin carpmaya gore tersini bul." << setw(20) << endl;
        cout << setw(20) << "(6)    Karmasik sayilari bol." << endl;
        cout << setw(20) << "(7)    Karmasik sayiya  bir sayi ekle." << endl;
        cout << setw(20) << "(8)    Karmasik sayidan bir sayi cikar." << endl;
        cout << setw(20) << "(9)    Karmasik sayiyi bir sayi ile carp." << endl;
        cout << setw(20) << "(10)   Karmasik sayiyi bir karmasık sayı  ile bol." << endl;
        cout << setw(20) << "(11)   Karmasik sayiyin bir kutupsal gösterimini bul." << endl;
        cout << "(12)    Cikis" << setw(20) << endl;
        cin >> secenek;
        system("CLS");

        switch (secenek)
        {
        case 1://Karmasık sayı ile  bir karmasık sayıyı toplama.
        {
            Karmasik sayi1, sayi2; //İki tane obje olusturdum.
            sayi1.set();//Objelerin verilerini isteme.
            sayi2.set();
            Karmasik sayi3;
            sayi3 = sayi1 + sayi2;//Objeleri yeni bir objeye aktarma.
            sayi3.yazdir();//Objeyi yazdırma.
            break;
        }

        case 2://Bir karmasık sayının toplamaya göre tersini alma.
        {
            Karmasik sayi1;
            sayi1.set();
            sayi1.toplamaTers(&sayi1);//Adrese gidip sayının toplamaya göre alan fonk.
            sayi1.get();
            break;
        }

        case 3://Karmasık sayı ile  bir karmasık sayıyı cıkartma.
        {
            Karmasik sayi1, sayi2;
            sayi1.set();
            sayi2.set();
            Karmasik sayi3;
            sayi3 = sayi1 - sayi2;
            sayi3.yazdir();
            break;
        }

        case 4://Karmasık sayı ile  bir karmasık sayıyı çarpma.
        {
            Karmasik sayi1, sayi2;
            sayi1.set();
            sayi2.set();
            Karmasik sayi3;
            sayi3 = sayi1 * sayi2;
            sayi3.yazdir();
            break;
        }

        case 5://Karmasık sayının çarpmaya göre tersini alma.
        {
            Karmasik sayi1;
            sayi1.set();
            sayi1.carpmaTers(&sayi1);
            sayi1.get();
            break;
        }

        case 6://Karmasık sayıyı bir karmasık sayıya bölme.
        {
            Karmasik sayi1, sayi2;
            sayi1.set();
            sayi2.set();
            Karmasik sayi3;
            sayi3 = sayi1 / sayi2;
            sayi3.yazdir();
            break;
        }

        case 7://Karmasık sayıya bir karmasık sayı eklemek.
        {
            Karmasik eklenceksayi; //Eklenecek objeyi olusturdum.
            Karmasik sayi1;
            cout << "Ilk sayiyi giriniz:" << endl;
            sayi1.set();
            cout << endl;
            cout << "Eklecenek sayiyi giriniz: " << endl;
            eklenceksayi.set();
            sayi1 += eklenceksayi;
            sayi1.yazdir();
            break;
        }

        case 8://Karmasık sayıdan bir karmasık sayıyı cıkartma.
        {
            Karmasik cıkarılacaksayi;
            Karmasik sayi1;
            cout << "Ilk sayiyi giriniz:" << endl;
            sayi1.set();
            cout << endl;
            cout << "Cıkarılacak sayiyi giriniz: " << endl;
            cıkarılacaksayi.set();
            sayi1 -= cıkarılacaksayi;
            sayi1.yazdir();
            break;

            break;
        }

        case 9://Karmasık sayıyı bir karmasık sayıya çarpma.
        {
            Karmasik carpılacaksayi;//Carpılacak objeyi olusturdum.
            Karmasik sayi1;
            cout << "Ilk sayiyi giriniz:" << endl;
            sayi1.set();
            cout << endl;
            cout << "Carpılacak sayiyi giriniz: " << endl;
            carpılacaksayi.set();
            sayi1 *= carpılacaksayi;
            sayi1.yazdir();
            break;

            break;
        }

        case 10://Karmasık sayıyı bir karmasık sayıya bölme.
        {
            Karmasik boluneceksayi;//Bolunecek objeyi olusturdum.
            Karmasik sayi1;
            cout << "Ilk sayiyi giriniz:" << endl;
            sayi1.set();
            cout << endl;
            cout << "Bolunecek sayiyi giriniz: " << endl;
            boluneceksayi.set();
            sayi1 /= boluneceksayi;
            sayi1.yazdir();
            break;

            break;
        }

        case 11://Kutupsal gösterim.
        {
            Karmasik sayi1;
            sayi1.kutupsal(&sayi1);//Kutupsal koordinatları veren fonk.
            break;
        }

        case 12:
        {
            exit(0);
            break;
        }

        default:
            cout << "Geçersiz bir cevap girdiniz.Tekrar deneyiniz." << endl;
            break;
        }
        cout << "Baska bir islem yapmak ister misiniz ? ";
        cin >> cevap;
        system("CLS");
    } while (cevap == 'e');
}
