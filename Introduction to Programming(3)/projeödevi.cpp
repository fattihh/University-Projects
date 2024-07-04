#include<iostream>

#include<fstream>

#include<string>

#include<iomanip>

#include<algorithm>

#include<Windows.h>

using namespace std;

string strKontrol(string str);

class depourunleri
{
private:
	struct Tarih {
		int gun, ay, yil;
	};
	string urunAdi;
	Tarih uretimTarihi;
	Tarih sonKullanmaTarihi;
	float kaloriGram;
	int stokAdet;
	int fiyat;
	
public:

	void seturun()	//Urun bilgilerini almak icin gerekli method.
	{
		cout << "Urun adini giriniz : ";cin.ignore();getline(cin,urunAdi);
		urunAdi = strKontrol(urunAdi);
		cout << "Urun Uretim tarihini(gun/ay/yil) giriniz : ";cin >> uretimTarihi.gun >> uretimTarihi.ay >> uretimTarihi.yil;
		cout << "Son kullanma tarihini(gun/ay/yil) giriniz : "; cin >> sonKullanmaTarihi.gun >> sonKullanmaTarihi.ay >> sonKullanmaTarihi.yil;
		cout << "Urunun graminin kalorisini giriniz : ";cin >> kaloriGram;
		cout << "Urunden kac adet oldugunu giriniz : ";cin >> stokAdet;
		cout << "Urunun fiyatini giriniz : "; cin >> fiyat;
		cout << "Depodaki sayiyi giriniz : ";cin >> stokAdet;
	}
	void urunleriDosyayaYazdirma()	//Urunleri Dosyaya yazdırmak icin gerekli method.
	{
		fstream myFile;
		myFile.open("Depo.txt", ios::app);
		if (myFile.is_open()) //Dosya acik mi diye kontrol aciksa yazdirir.
		{
			myFile << urunAdi << ",";
			myFile << uretimTarihi.gun << "\\" << uretimTarihi.ay << "\\" << uretimTarihi.yil << ",";
			myFile << sonKullanmaTarihi.gun << "\\" << sonKullanmaTarihi.ay << "\\" << sonKullanmaTarihi.yil << ",";
			myFile << kaloriGram << ",";
			myFile << fiyat ;
			myFile << endl;
			myFile.close();
		}
		else//acik degilse dosya acilamadi yazdirir.
			cout << "Dosya acilamadi";
	}
	void dosyayiyazdir()	//Dosyayı satir satir yazdırmaya yarayan fonk.
	{
		fstream myFile;
		myFile.open("Depo.txt", ios::in);
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line)) //satir satir dosyayi yazdirir.
			{
				cout << line << endl;
			}
			myFile.close();
		}
	}
	void urunSilme()
	{
		string urunadi;//silinecek urunadi.
		string satir;
		ifstream myfile;
		depourunleri urun;
		cout << "Silinecek urunun adini giriniz: ";cin.ignore();getline(cin, urunadi);//silenecek urun adini isteme.
		ofstream depo1;
		depo1.open("depo1.txt");//gecici dosya acma.
		myfile.open("Depo.txt");
		if (!myfile)
		{
			cout << "Dosya bulunamadi." << endl;
			exit(0);
		}
		else
		{
			while (getline(myfile, satir))
			{
				size_t foundindex = satir.find(urunadi);	//urunadini tutan degisken.
				if (foundindex != satir.npos)	//urunadi olan satiri ariyor.
					satir.replace(satir.begin(), satir.end(), "");	//satiri buluyor ve yerine bosluk atıyor.
				if (!satir.empty()) {
					depo1 << satir << endl; //eğer satir bos degilse aynı satiri yazdiriyor.
				}
			}
		}
		depo1.close();
		myfile.close();
		remove("Depo.txt");//Depo.txt silindi.
		rename("depo1.txt", "Depo.txt");//Gecici dosya yeniden isimlendirildi Depo.txt olarak.
	}
	void guncelle()
	{
		string urunadi;
		string satir;
		ifstream myfile;
		depourunleri urun;
		cout << "Guncellenecek urunun adini giriniz: ";cin.ignore();getline(cin, urunadi);//Guncellenecek urun adini istemek.
		cout << "Girmek istediginiz guncel urun adini giriniz : ";getline(cin, urunAdi);
		urunAdi = strKontrol(urunAdi);
		cout << "Urunun uretim tarihini giriniz(gun/ay/yil): ";cin >> uretimTarihi.gun >> uretimTarihi.ay >> uretimTarihi.yil;
		cout << "Urunun son kullanim tarihini giriniz(gun/ay/yil): ";cin >> sonKullanmaTarihi.gun >> sonKullanmaTarihi.ay >> sonKullanmaTarihi.yil;
		cout << "1 graminin kalorisini giriniz: ";cin >> kaloriGram;
		cout << "Depoya eklencek adeti giriniz: ";cin >> stokAdet;
		cout << "Urunun fiyatini giriniz:";cin >> fiyat;
		ofstream depo1;
		depo1.open("depo1.txt");//gecici dosya acma
		myfile.open("Depo.txt");
		if (!myfile)//dosya acik mi kontrol
		{
			cout << "Dosya bulunamadi." << endl;
			exit(0);
		}
		else
		{
			while (getline(myfile, satir))
			{
				size_t foundindex = satir.find(urunadi); //urunadini tutan degisken.
				if (foundindex != satir.npos)  //urunadi olan satiri ariyor.
					satir.replace(satir.begin(), satir.end(), ""); //satiri buluyor ve yerine bosluk atıyor.

				if (!satir.empty())
				{
					depo1 << satir << endl;	//satir bos degilse aynen yazdirir satiri.
				}
				else //eger satir boşsa yukarıda istenen verileri yazar.
				{
					depo1 << urunAdi << "," << uretimTarihi.gun << "/" << uretimTarihi.ay << "/" << uretimTarihi.yil
						<< "," << sonKullanmaTarihi.gun << "/" << sonKullanmaTarihi.ay << "/" << sonKullanmaTarihi.yil << "/"
						<< kaloriGram << "," << stokAdet  << endl;
				}
			}
		}
		depo1.close();
		myfile.close();
		remove("Depo.txt");//Dosyayı silme
		rename("depo1.txt", "Depo.txt");//Gecici dosyayı adlandırma.
	}
	void urunbulma()
	{
		ifstream myfile;
		myfile.open("Depo.txt");
		cout << "Depodaki hangi malzemeyi goruntulemek istersiniz? ";cin.ignore();getline(cin,urunAdi);
		string satir;
		while (getline(myfile, satir))
		{
			size_t foundsatir = satir.find(urunAdi);	//Urun adini tutan degisken
			if (foundsatir != satir.npos)//urunadi boyuta eşitse yazdir.
			{
				cout << satir << endl;
			}
		}
		myfile.close();
	}
	void stokGuncelle(int kullanim)
	{
		ifstream myfile;
		myfile.open("Depo.txt");
		string satir;
		ofstream depo;
		depo.open("Depo1.txt");
		while (getline(myfile, satir))
		{
			size_t foundsatir = satir.find(urunAdi);//urunadini bulma.
			if (foundsatir != satir.npos)
			{
				string kelime = ""; //bos bir string
				int counter = 0;//sayici
				for (int i = 0; i < satir.length(); i++)
				{
					if (satir[i] != ',')
						kelime += satir[i];//eğer virgül değilse bos stringe at.
					else
					{
						if (counter == 4) //eğer sayici 4 ise
						{
							cout << "Depodaki kilo " << kelime << endl;//depodaki kiloyu yazdir
							int kilo = stoi(kelime);//stringi int'e cevirme
							kilo -= kullanim;//kullanilan miktari cikar.
							satir.replace(i - kelime.length(), kelime.length(), to_string(kilo));//replace(başlangıç konumu, silenecek kelimenin uzunlugu, yeni kelime)
						}
						kelime = "";
						counter++;
					}
				}
			}
			depo << satir << endl;
		}
		depo.close();
		myfile.close();
		remove("Depo.txt");//dosyayi silme
		rename("Depo1.txt", "Depo.txt");//dosyayi yeniden adlandırma.
	}
};

class yemekcesit
{
private:
	string yemekAdi;
public:
	void setyemekCesit()//yemek cesidini isteyen fonk.
	{
		cout << "Eklenecek yemek cesidini giriniz: ";cin.ignore();getline(cin, yemekAdi);
	}
	void yemekCesitDosyayaEkleme()
	{
		fstream myFile;
		myFile.open("yemekcesit.txt", ios::app);//ekleme modunda dosyayi acma.
		if (myFile.is_open())
		{
			myFile << yemekAdi ;//yemek adini dosyaya yazdirir.
			myFile << endl;
			myFile.close();
		}
		else
			cout << "Dosya acilamadi";
	}
	void tumYemekKayitGoruntule()
	{
		fstream myFile;
		myFile.open("yemekcesit.txt", ios::in);	//satir satir dosyayı okutma.
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				cout << line << endl;
			}
			myFile.close();
		}
	}
	void yemekCesitSilme()
	{
		string yemekadi;
		string satir;
		ifstream myfile;
		yemekcesit yemek;
		cout << "Silinecek urunun adini giriniz: ";cin.ignore();getline(cin , yemekadi);//silinecek yemek adini istiyoruz.
		ofstream depo1;
		depo1.open("yemekcesit2.txt");//gecici dosyayi acma.
		myfile.open("yemekcesit.txt");
		if (!myfile)
		{
			cout << "Dosya bulunamadi." << endl;
			exit(0);
		}
		else
		{
			while (getline(myfile, satir))
			{
				size_t foundindex = satir.find(yemekadi); //yemek adini iceren satiri bul.
				if (foundindex != satir.npos)
					satir.replace(satir.begin(), satir.end(), "");//yemek adını bulursak boş string at
				if (!satir.empty()) 
				{
					depo1 << satir << endl;//boşsa direk satiri yazdir.
				}
			}
		}
		depo1.close();
		myfile.close();
		remove("yemekcesit.txt");//dosyayi silme
		rename("yemekcesit2.txt", "yemekcesit.txt");//gecici dosyayı yeniden adlandır.
	}
	void yemekGuncelle()//Malzemelerin de güncellenmesi lazım.//buraya bak.
	{
		string yemekadi;
		string satir;
		ifstream myfile;
		yemekcesit yemek;
		cout << "Guncellenecek yemek adini giriniz: ";cin.ignore();getline(cin, yemekadi);//guncellenecek yemekadini isteme
		cout << "Girmek istediginiz yemek adini giriniz : ";getline(cin, yemekAdi);//yeni yemekadini isteme.
		ofstream yemekcesit2;
		yemekcesit2.open("yemekcesit2.txt");
		myfile.open("yemekcesit.txt");
		if (!myfile)
		{
			cout << "Dosya bulunamadi." << endl;
			exit(0);
		}
		else
		{
			while (getline(myfile, satir))
			{
				size_t foundindex = satir.find(yemekadi);//yemekadini bulma.
				if (foundindex != satir.npos)
					satir.replace(satir.begin(), satir.end(), "");//bulursa yerine bos string atma.

				if (!satir.empty())
				{
					yemekcesit2 << satir << endl;//boş değilse direk olan satiri yazdir.
				}
				else
				{
					yemekcesit2 << yemekAdi << endl;//boşsa yemekadini yazdir.

				}
			}
		}
		yemekcesit2.close();
		myfile.close();
		remove("yemekcesit.txt");
		rename("yemekcesit2.txt", "yemekcesit.txt");
	}
	string getYemekAdi()//yemek adini veren get fonk.
	{
		return yemekAdi;
	}
};

class malzemeler
{
private:
	string malzemeAdi;
public:
	int malzemeSayisi;
	void DosyayaMalzemeEkleme()
	{
		fstream myFile;
		myFile.open("malzemeler.txt", ios::app);//ekleme modunda dosyayı açma
		cout << "Yemegin eklencek kac malzemesi var ?";
		cin >> malzemeSayisi;
		yemekcesit yemekadi;
		yemekadi.setyemekCesit();
		myFile << yemekadi.getYemekAdi() << ",";//malzemelerin basina yemek adini yazdirmak icin.
		cout << "Dosyaya eklenecek malzemeleri giriniz." << endl;
		for (int i = 0; i < malzemeSayisi; i++)
		{
			if (myFile.is_open())
			{
				cin >> malzemeAdi;//yeni malzeme adlarini isteme
				myFile <<malzemeAdi;//malzeme adlarını dosyaya yazdırma
				if (i != malzemeSayisi - 1)//satirin sonuna virgül atmaması icin
					myFile << ",";
			}
			else
			{
				cout << "Dosya acilamadi";
			}
		}
		myFile.close();
	}
	void DosyadanMalzemeSilme()
	{
		string yemekAdi;
		string satir;
		ifstream myfile;
		depourunleri urun;
		cout << "Malzemeleri silinecek yemek adini giriniz: ";cin.ignore();getline(cin,yemekAdi);
		ofstream malzemeler1;
		malzemeler1.open("malzemeler1.txt");
		myfile.open("malzemeler.txt");
		if (!myfile)
		{
			cout << "Dosya bulunamadi." << endl;
			exit(0);
		}
		else
		{
			while (getline(myfile, satir))
			{
				size_t foundindex = satir.find(yemekAdi);
				if (foundindex != satir.npos)
					satir.replace(satir.begin(), satir.end(), "");//ismi bulunca yerine bos string atma.
				if (!satir.empty()) 
				{
					malzemeler1 << satir << endl;//isim degilse satiri aynen yazdir.
				}
			}
		}
		malzemeler1.close();
		myfile.close();
		remove("malzemeler.txt");
		rename("malzemeler1.txt", "malzemeler.txt");
	}
	
};

int GenelTutarHesaplama(int malzemeSayisi);
int karHesaplama(int maliyet, int kisiSayisi);

int main()
{
	string cevap;
	cout << "Hangi islemi yapmak istersiniz (depo/yemek/uretim) ? ";
	cin >> cevap;
	do
	{
		transform(cevap.begin(), cevap.end(), cevap.begin(), ::tolower);//Kullancı buyuk harf girse bile kücük harfe cevirir ve do-while döngüsüne sokar.
		if (cevap == "depo")//verilen cevap depo ise girilen kod bloğu
		{
			int depoİslemleriSecenek;
			while (true)
			{
				system("CLS");
				cout << "*************DEPO ISLEMLERI****************" << endl << endl;
				cout << "Yeni bir urun ekle" << setw(20) << "(1)" << endl;
				cout << "Tum kayitlari goruntule" << setw(15) << "(2)" << endl;
				cout << "Istediginiz kayiti goruntuleme" << setw(8) << "(3)" << endl;
				cout << "Urun kayidi silme" << setw(21) << "(4)" << endl;
				cout << "Urun guncelleme/degistirme" << setw(12) << "(5)" << endl;
				cout << "Cikis" << setw(33) << "(6)" << endl;
				cout << "Hangi islemi yapmak istersiniz "; cin >> depoİslemleriSecenek;
				system("CLS");
				switch (depoİslemleriSecenek)
				{
				case 1:
				{
					char ch = 'e';
					do
					{
						depourunleri urun;
						urun.seturun();//urun bilgilerini isteme
						urun.urunleriDosyayaYazdirma();//urunleri dosyaya yazdirma.
						cout << "Baska bir urun eklemek ister misiniz(e/h)?";
						cin >> ch;
						system("cls");
					} while (ch == 'e');
				}
				case 2:
				{
					depourunleri urun;
					urun.dosyayiyazdir();//urunleri tek tek yazdirma.
					system("pause");
					break;
				}
				case 3:
				{
					char ch = 'e';
					do
					{
						depourunleri urun;
						urun.urunbulma();//urun bulma
						cout << "Baska bir urun goruntulemek ister misiniz(e/h)?";
						cin >> ch;
						system("cls");
					} while (ch == 'e');
					break;
				}
				case 4:
				{
					char ch = 'e';
					do
					{
						depourunleri urun;
						urun.urunSilme();//urun silme
						cout << "Baska bir urun silmek ister misiniz(e/h)?";
						cin >> ch;
						system("cls");
					} while (ch == 'e');
					break;
				}
				case 5:
				{

					char ch = 'e';
					do
					{
						depourunleri urun;
						urun.guncelle();//urunleri guncelle.
						cout << "Baska bir urun guncellemek ister misiniz(e/h)?";
						cin >> ch;
						system("cls");
					} while (ch == 'e');
					break;
				}
				case 6:
				{
					exit(0);
				}
				default:
				{
					cout << "Gecersiz bir secenek girdiniz tekrar deneyin." << endl;
					system("pause");
					break;
				}
				}
			}
		}
		if (cevap == "yemek")
		{
			int yemekİslemleriSecenek;
			while (true)
			{
				system("CLS");
				cout << "*************YEMEK ISLEMLERI****************" << endl << endl;
				cout << "Yeni bir yemek cesidi ekle" << setw(20) << "(1)" << endl;
				cout << "Tum yemek kayitlarini goruntule" << setw(15) << "(2)" << endl;
				cout << "Yemek kayidi silme" << setw(28) << "(3)" << endl;
				cout << "Yemek guncelleme/degistirme" << setw(19) << "(4)" << endl;
				cout << "Cikis" << setw(41) << "(5)" << endl;
				cout << "Hangi islemi yapmak istersiniz "; cin >> yemekİslemleriSecenek;
				system("CLS");
				switch (yemekİslemleriSecenek)
				{
				case 1:
				{
					yemekcesit yemek;
					yemek.setyemekCesit();//yemek cesitini isteyen fonk.
					yemek.yemekCesitDosyayaEkleme();//yemek cesidini dosyaya ekleyen fonk.
					malzemeler malzeme;	
					malzeme.DosyayaMalzemeEkleme();//Dosyaya malzeme ekleyen
					break;
				}
				case 2:
				{
					yemekcesit yemek;
					yemek.tumYemekKayitGoruntule();//tum yemek kayitlarini goruntuleme
					system("pause");
					break;
				}
				case 3:
				{
					char ch = 'e';
					do
					{
						yemekcesit yemek;
						yemek.yemekCesitSilme();//yemek cesit silme
						malzemeler malzeme;
						malzeme.DosyadanMalzemeSilme();//malzeme.txt'den malzeme silme.
						break;
						cout << "Baska yemek malzemeleri silmek ister misiniz(e/h)?";
						cin >> ch;
					} while (ch == 'e');
					break;
				}
				case 4:
				{
					char ch = 'e';
					do
					{
						yemekcesit yemek;
						yemek.yemekGuncelle();//yemek guncelleme.
						malzemeler malzeme;
						cout << "Baska bir yemek guncellemek ister misiniz?(e/h)";
						cin >> ch;
					} while (ch == 'e');
					break;
				}
				case 5:
				{
					exit(0);
				}
				default:
				{
					cout << "Gecersiz bir secenek girdiniz tekrar deneyin." << endl;
					system("pause");
					break;
				}

				}
			}
		}
		if (cevap == "uretim")
		{
			string  yemekadi;//yapilacak yemekleri almak icin degisken.
			string yemekAdlari[100];//yapilan yemeklerin tutulduğu liste.
			depourunleri depoMalzemeler;
			int malzemeSayisi;//yemegin kac malzemesi var tutan degisken.
			string cevap;
			int yemekSayisi;//bugun kac cesit yemek yapilacagini tutan degisken.
			int kisiSayisi;//yemekten kac kisilik yapilacak onu tutan degisken.
			string siparisListesi[100];//siparis verilecek urunleri tutan liste.
			string siparis;//ne siparis verilecek tutan degisken.
			int siparisSayisi;//siparis listesi icin kac siparis verilecegini tutan degisken.
			int miktarListesi[100];//siparis verirken siparis verilen urunden ne kadar verilecegini tutan liste.
			int miktar;//siparis verilen urunden ne kadar veriliecegini tutan degisken.
			int secenek;
			int kullanim;//yemek yapimi icin kullanilan üründen ne kadar kullanıldığını tutan degisken.
			int maliyet;//yemegin maliyetini tutmak için degisken.
			string satilanYemekler[50];//satilan yemeklerin listesi.
			int satilanYemekSayisi;//satilan yemek sayisini tutan degisken.
			string satilanYemek;//satilan yemeklerin adi.
			int fiyatListesi[100];//satilan yemeklerin fiyatini tutan liste
			int fiyat;//yemek fiyatını istemek icin degisken.
			while (true)
			{
				system("CLS");
				cout << "*************URETIM ISLEMLERI****************" << endl << endl;
				cout << "Yemek yapmak (1)" << endl;
				cout << "Yemek satisi (2)"  << endl;
				cout << "Gun icinde uretilen yemekleri goruntule(3)" << endl;
				cout << "Hangi islemi yapmak istersiniz?";
				cin >> secenek;
				system("cls");
				switch (secenek)
				{
				case 1:
				{
					yemekcesit yemek;
					yemek.tumYemekKayitGoruntule();//tum yemek kayitlarini goruntuleyen fonk.
					cout << endl;
					cout << "Bugun kac cesit yemek yapilacak";
					cin >> yemekSayisi;
					cout << "Yapilacak yemekleri giriniz." << endl;
					for (int i = 0; i < yemekSayisi; i++)
					{
						cin.ignore();getline(cin, yemekadi);
						yemekadi = strKontrol(yemekadi);
						yemekAdlari[i] = yemekadi;//yemek listesine eleman ekleme.
						cout << endl;
					}
					system("CLS");
					for (int i = 0; i < yemekSayisi; i++)
					{
						cout << yemekAdlari[i] << "'den kac kisilik pisirilecek?";
						cin >> kisiSayisi;//yemekten kac kisilik yapiliyor istedik.
						cout << yemekAdlari[i] << " yapimi icin kac malzeme kullanilacak ? ";
						cin >> malzemeSayisi;//yemegin malzeme sayisini isteme.
						for (int i = 0; i < malzemeSayisi; i++)
						{
							depoMalzemeler.urunbulma();//depodaki urunleri  bulma ve yeterli yetersizligine bakma.
						}
						cout << "Depodaki miktar yeterli mi (evet/hayir)?" << endl;
						cin >> cevap;
						system("CLS");
						if (cevap == "evet")//yeterli ise
						{
							for (int i = 1; i < malzemeSayisi+1; i++)
							{
								depourunleri cekilecekUrunler;
								cout << "Malzemeden ne kadar kullanilacak ? ";
								cin >> kullanim;//malzemeden ne kadar kullanılacagini istedik.
								cekilecekUrunler.urunbulma();//urunleri bulma
								cekilecekUrunler.stokGuncelle(kullanim);//stoktan kullanılan miktari düsme.
								cout << "Stoktan dusuluyor." << endl;
								Sleep(1000);//sistemi uyutma
								system("pause");
								system("cls");
							}
						}
						if (cevap == "hayir")//depodaki miktar yeterli degilse
						{
							cout << "Kac eksik siparis verilecek" << endl;
							cin >> siparisSayisi;//siparis sayisini isteme

							for (int i = 0; i < siparisSayisi; i++)
							{
								cout << "Ne siparis verilecek(isim)" << endl;
								cin >> siparis;//ne siparis verilecegini isteme.
								cout << "Miktari giriniz(kg/paket):" << endl;
								cin >> miktar;//siparis verilmek istenen miktari tutma.
								miktarListesi[i] = miktar;//miktari listeye ekleme
								siparisListesi[i] = siparis;//siparis listesine siparisi ekleme.
							}
							system("CLS");
							cout << "Siparis Listesi" << endl;
							for (int i = 0; i < siparisSayisi; i++)
							{
								cout << siparisListesi[i] << " " << miktarListesi[i] << "(kg/paket)" << endl;//siparis listesini yazdirma.

							}
							system("Pause");
							system("cls");
						}
						maliyet = GenelTutarHesaplama(malzemeSayisi);//yemegin maliyetini hesaplama.
						cout << yemekAdlari[i]<<"'nin kisi basi maliyeti "<<maliyet/kisiSayisi<<" Genel tutar "<<maliyet<<" TL"<<endl;
						karHesaplama(maliyet, kisiSayisi);//yemekten ne kadar edildigini hesaplama.
						system("pause");
						cout<<endl;
						system("CLS");
					}
					break;
				}
				case 2:
				{
					cout << "Kac yemek satisi yapilacak";//kac yemek satisi yapilacagini isteme.
					cin >> satilanYemekSayisi;//satilan yemek sayisini isteme.
					for (int i = 0; i < satilanYemekSayisi; i++)
					{
						cout << "Hangi yemekler satilacak ";
						cin.ignore();getline(cin,satilanYemek);//satilacak yemekleri isteme.
						satilanYemekler[i] = satilanYemek;//satilan yemekleri listeye ekleme.
						cout << "Yemegin fiyatini giriniz:";
						cin >> fiyat;//yemegin fiyatını isteme
						fiyatListesi[i] = fiyat;//yemegin fiyatını listeye ekleme.
					}
						string cevap;
						cout << "Yemek satis raporu cikarilsin mi(evet/hayir) ? ";
						cin >> cevap;
						system("cls");
						while (cevap=="evet")
						{
							cout << "****SATISI YAPILAN YEMEKLER****" << endl;
							for (string ad : satilanYemekler)//satisi yapilan yemekleri yazdirma.
							{
								cout << ad << endl;
							}
							cout << endl;

							int toplam = 0;
							for (int i = 0; i < satilanYemekSayisi; i++)//elde edilen geliri yazdirma.
							{
								toplam += fiyat;
							}
							cout << "Elde edilen gelir " << toplam << endl;
							system("pause");
						}
					break;
				}
				case 3:
				{
					cout << "****GUN ICINDE URETILEN YEMEKLER****" << endl;
					for (string ad : yemekAdlari)//gun icinde uretilen yemekleri yazdirma.
					{
						cout << ad << endl;
					}
					system("pause");
					break;
				}
				default:
				{
						cout << "Gecersiz secenek tekrar deneyin"<<endl;
						system("pause");
					break;
					}

				}
			}
		}
		else//gecersiz cevap girilince devreye giren kod blogu.
		{
			cout << "Gecersiz cevap.Lutfen gecerli bir cevap giriniz.";
			cin >> cevap;
		}
	} while (cevap != "depo" || cevap != "yemek" || cevap == "uretim");
}

string strKontrol(string str)
{
	while (find_if(str.begin(), str.end(), ::isdigit) != str.end() && find_if(str.begin(), str.end(), ::isalpha) != str.end())
	{
		//string basında ve sonuna kadar tarar ve sayi veya ozel karakter var mı kontrol eder.
		cout << "sayi veya ozel karakter iceremez yeniden girin:";
		cin >> str;
	}
	return str;
}

int GenelTutarHesaplama(int malzemeSayisi)
{
	int kullanim;//malzemeden kullanilan miktari tutan degisken.
	int fiyat;//yemegin fiyatini tutan degisken.
	int toplam = 0;//toplam tutarı hesaplama yemegin
	for (int i = 1;i < malzemeSayisi+1;i++)
	{
		cout << i << "." << "malzemeden ne kadar kullanildi ? ";
		cin>>kullanim;//malzemeden ne kadar kullanıldıgını isteme.
		cout << "Malzemenin paketi veya kilogrami kac TL ?";
		cin>>fiyat;//malzemenin fiyatini isteme.
		toplam += kullanim * fiyat;
	}
	return toplam;
}

int karHesaplama(int maliyet,int kisiSayisi)
{
	int fiyat;
	cout << "Yemegi kac TL olarak satilacak ? ";
	cin >> fiyat;//yemegin fiyatini isteme.
	int kar = fiyat - maliyet / kisiSayisi;
	cout << "Yemekten kariniz " << kar<<" TL";
	return kar;
}

