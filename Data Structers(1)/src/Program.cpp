/** 
* @file Program.cpp
* @description Program sınıfının kaynak kodları 
* @course Veri yapilari 2A grubu
* @assignment 1.odev
* @date 17-24.11.2023
* @author Fatih Ucar fatih.ucar1@ogr.sakarya.edu.tr
*/

#include "Program.hpp"
#include <cstdlib>


Program::Program()
{
    sayilarListesi = new SayilarListesi();
    SayilarListesiOlustur();
}

void Program::SayilarListesiOlustur()
{
    TextOku* textoku = new TextOku("Sayilar.txt");
    string sayilar = textoku->GetSayilar();

    Sayi* sayi = new Sayi();
    for(int i = 0; i < sayilar.length(); i++)
    {
        if(sayilar[i] == ' ')
        {
            if(sayi->Count() > 0) sayilarListesi->add(sayi);
            else delete sayi;
            sayi = new Sayi();
        }
        else
        {
            int basamak = sayilar[i] - '0';
            sayi->add(basamak);
        }
    }
        if(sayi->Count() > 0) sayilarListesi->add(sayi);
        else delete sayi;
        delete textoku;
}


void Program::programiBaslat()
{
        
    int secim=0;
    do{
        sayilarListesi->print();
        cout<<"[1]\tTek basamaklari basa al"<<endl;
        cout<<"[2]\tBasamaklari tersle"<<endl;
        cout<<"[3]\tEn buyuk cikar"<<endl;
        cout<<"[4]\tCikis"<<endl;
        cout<<"Secim:";
        cin>>secim;
        switch(secim){
            case 1:
                sayilarListesi->tekBasamaklariBasaAl();
                break;
            case 2:
                sayilarListesi->basamaklariTersle();
                break;
            case 3:
                sayilarListesi->enBuyukSayiyiSil();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout<<endl<<"Yanlis Secim!!"<<endl;
                cin.ignore();
                cin.get();
                break;
            }
        }while(secim != 4);
}