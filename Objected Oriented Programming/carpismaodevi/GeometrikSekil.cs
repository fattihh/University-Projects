using carpismaodevi;
using Microsoft.VisualBasic.Devices;
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace carpismaodevi
{

    public class Nokta : Sekil
    {
        public double x { get; set; }
        public double y { get; set; }

        public int yaricap { get; set; }

        public Nokta()
        {
            Random random = new Random();
            this.x = random.Next(100);
            this.y = random.Next(100);
        }

        public override void Cizdir(Graphics g)
        {

            g.FillEllipse(Brushes.Red, (float)x, (float)y, 5, 5);

        }
        public override bool Carpisma(Sekil digerSekil)
        {
            if (digerSekil is Cember digerCember)
            {
                // İki cember arasındaki merkezler arası mesafeyi hesaplayan formül
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerCember.x_Koordinat + digerCember.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerCember.y_Koordinat + digerCember.yaricap / 2), 2));

                // Merkezler arası mesafenin, iki cemberin yarıçaplarının toplamının yarısına eşit veya daha küçük olup olmadığını kontrol eden ifade
                return merkezlerArasiMesafe <= (this.yaricap + digerCember.yaricap) / 2;
            }

            else if (digerSekil is Küre digerKüre)
            {
                // Cember ve Küre arasındaki merkezler arası mesafeyi hesaplayan formül
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerKüre.x_Koordinat + digerKüre.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerKüre.y_Koordinat + digerKüre.yaricap / 2), 2));
                // Merkezler arası mesafenin, Cemberin ve Kürenin yarıçaplarının toplamının yarısına eşit veya daha küçük olup olmadığını kontrol eden ifade
                return merkezlerArasiMesafe <= (this.yaricap + digerKüre.yaricap) / 2;

            }

            else if (digerSekil is Nokta nokta)
            {

                // İlk olarak, noktanın x koordinatının dairenin x koordinatından çıkarılmasıyla x mesafesi hesaplanıyor.
                double distanceX = nokta.x_Koordinat - x_Koordinat;

                // Ardından, noktanın y koordinatının dairenin y koordinatından çıkarılmasıyla y mesafesi hesaplanıyor.
                double distanceY = nokta.y_Koordinat - y_Koordinat;

                // X mesafesi ve y mesafesi kullanılarak iki nokta arasındaki uzaklık karesi hesaplanıyor.
                // İki mesafenin karesi alınarak toplanıyor.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, dairenin yarıçapının karesine eşit veya daha küçükse,
                // nokta dairenin içinde veya çevresinde yer alıyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (yaricap * yaricap);

            }

            else if (digerSekil is Kare digerKare)
            {
                // İki karenin merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKare.x_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // İki karenin merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKare.y_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // Hem x ekseni hem de y ekseni boyunca çarpışma kontrolü yapılır.
                // Eğer her iki eksende de çarpışma varsa, kareler birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;

            }

            else if (digerSekil is Küp digerKüp)
            {
                // Bir kare ve Küpün merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKüp.x_Koordinat - digerKüp.x_Koordinat / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // Bir kare ve Kürenin  merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKüp.y_Koordinat - digerKüp.kenar / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // Hem x ekseni hem de y ekseni boyunca çarpışma kontrolü yapılır.
                // Eğer her iki eksende de çarpışma varsa, kare ve küp birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

            else if (digerSekil is Yüzey digerYüzey)
            {
                // Çemberin merkez noktasının yüzeyin sınırları içerisinde olup olmadığını kontrol et
                double closestX = Math.Max(digerYüzey.x_Koordinat, Math.Min(digerYüzey.x_Koordinat, digerYüzey.x_Koordinat + digerYüzey.Genislik));
                double closestY = Math.Max(digerYüzey.y_Koordinat, Math.Min(digerYüzey.y_Koordinat, digerYüzey.y_Koordinat + digerYüzey.Yukseklik));

                double distanceX = x_Koordinat - closestX;
                double distanceY = y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (yaricap * yaricap);

            }

            else if (digerSekil is Dikdortgen digerDikdortgen)
            {
                // Diğer dikdörtgenin minimum ve maksimum x koordinatları
                double dikdortgenMinX = digerDikdortgen.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgen.x_Koordinat + digerDikdortgen.kenar;

                // Diğer dikdörtgenin minimum ve maksimum y koordinatları
                double dikdortgenMinY = digerDikdortgen.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgen.y_Koordinat + digerDikdortgen.genislik;

                // Bu dairenin en yakın noktasının x koordinatı, bu dairenin x koordinatının diğer dikdörtgenin x koordinat aralığına kısıtlanmış hali olur.
                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));

                // Bu dairenin en yakın noktasının y koordinatı, bu dairenin y koordinatının diğer dikdörtgenin y koordinat aralığına kısıtlanmış hali olur.
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                // Bu dairenin en yakın noktası ile dairenin merkezi arasındaki x mesafesi
                double distanceX = this.x_Koordinat - closestX;

                // Bu dairenin en yakın noktası ile dairenin merkezi arasındaki y mesafesi
                double distanceY = this.y_Koordinat - closestY;

                // İki mesafenin karesi alınarak toplanır ve böylece uzaklık karesi elde edilir.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, dairenin yarıçapının karesine eşit veya daha küçükse,
                // daire dikdörtgenin içinde veya çevresinde yer alıyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (this.yaricap * this.yaricap);

            }

            else if (digerSekil is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Diğer prizmanın minimum ve maksimum x koordinatları
                double dikdortgenMinX = digerDikdortgenPrizma.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.kenar;
                // Diğer prizmanın minimum ve maksimum x koordinatları
                double dikdortgenMinY = digerDikdortgenPrizma.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.kenar;

                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                double distanceX = this.x_Koordinat - closestX;
                double distanceY = this.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (this.yaricap * this.yaricap);
            }

            return false;
        }


    }

    public abstract class Sekil
    {
        public int x_Koordinat { get; set; }
        public int y_Koordinat { get; set; }
        public abstract void Cizdir(Graphics g);//Cizdirme metodu
        public abstract bool Carpisma(Sekil other);//Carpisma metodu
    }

    class Cember : Sekil 
    {
        public int yaricap;
        public Cember()
        {
            Random r = new Random();
            x_Koordinat = r.Next(200);
            y_Koordinat = r.Next(200);
            yaricap = 100;

        }
        public Cember(string x)
        {
        }
        public override void Cizdir(Graphics g)
        {
            g.DrawEllipse(Pens.Red, x_Koordinat, y_Koordinat, yaricap, yaricap);

        }
        public override bool Carpisma(Sekil digerSekil)
        {
            if (digerSekil is Cember digerCember)
            {
                // İki cember arasındaki merkezler arası mesafeyi hesaplayan formül
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerCember.x_Koordinat + digerCember.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerCember.y_Koordinat + digerCember.yaricap / 2), 2));

                // Merkezler arası mesafenin, iki cemberin yarıçaplarının toplamının yarısına eşit veya daha küçük olup olmadığını kontrol eden ifade
                return merkezlerArasiMesafe <= (this.yaricap + digerCember.yaricap) / 2;
            }

            else if (digerSekil is Küre digerKüre)
            {
                // Cember ve Küre arasındaki merkezler arası mesafeyi hesaplayan formül
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerKüre.x_Koordinat + digerKüre.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerKüre.y_Koordinat + digerKüre.yaricap / 2), 2));
                // Merkezler arası mesafenin, Cemberin ve Kürenin yarıçaplarının toplamının yarısına eşit veya daha küçük olup olmadığını kontrol eden ifade
                return merkezlerArasiMesafe <= (this.yaricap + digerKüre.yaricap) / 2;

            }

            else if (digerSekil is Nokta nokta)
            {
                               
                // İlk olarak, noktanın x koordinatının dairenin x koordinatından çıkarılmasıyla x mesafesi hesaplanıyor.
                double distanceX = nokta.x_Koordinat - x_Koordinat;

                // Ardından, noktanın y koordinatının dairenin y koordinatından çıkarılmasıyla y mesafesi hesaplanıyor.
                double distanceY = nokta.y_Koordinat - y_Koordinat;

                // X mesafesi ve y mesafesi kullanılarak iki nokta arasındaki uzaklık karesi hesaplanıyor.
                // İki mesafenin karesi alınarak toplanıyor.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, dairenin yarıçapının karesine eşit veya daha küçükse,
                // nokta dairenin içinde veya çevresinde yer alıyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (yaricap * yaricap);

            }

            else if (digerSekil is Kare digerKare)
            {
                // İki karenin merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKare.x_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // İki karenin merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKare.y_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // Hem x ekseni hem de y ekseni boyunca çarpışma kontrolü yapılır.
                // Eğer her iki eksende de çarpışma varsa, kareler birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;

            }

            else if (digerSekil is Küp digerKüp)
            {
                // Bir kare ve Küpün merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKüp.x_Koordinat - digerKüp.x_Koordinat / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // Bir kare ve Kürenin  merkez noktaları arasındaki uzaklık, yarıçaplarının yarısıyla kenar uzunluklarının yarısı toplanarak hesaplanır.
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKüp.y_Koordinat - digerKüp.kenar / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // Hem x ekseni hem de y ekseni boyunca çarpışma kontrolü yapılır.
                // Eğer her iki eksende de çarpışma varsa, kare ve küp birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

            else if (digerSekil is Yüzey digerYüzey) 
            {
                // Çemberin merkez noktasının yüzeyin sınırları içerisinde olup olmadığını kontrol et
                double closestX = Math.Max(digerYüzey.x_Koordinat, Math.Min(digerYüzey.x_Koordinat, digerYüzey.x_Koordinat + digerYüzey.Genislik));
                double closestY = Math.Max(digerYüzey.y_Koordinat, Math.Min(digerYüzey.y_Koordinat, digerYüzey.y_Koordinat + digerYüzey.Yukseklik));

                double distanceX = x_Koordinat - closestX;
                double distanceY = y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (yaricap * yaricap);

            }
            
            else if (digerSekil is Dikdortgen digerDikdortgen)
            {
                // Diğer dikdörtgenin minimum ve maksimum x koordinatları
                double dikdortgenMinX = digerDikdortgen.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgen.x_Koordinat + digerDikdortgen.kenar;

                // Diğer dikdörtgenin minimum ve maksimum y koordinatları
                double dikdortgenMinY = digerDikdortgen.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgen.y_Koordinat + digerDikdortgen.genislik;

                // Bu dairenin en yakın noktasının x koordinatı, bu dairenin x koordinatının diğer dikdörtgenin x koordinat aralığına kısıtlanmış hali olur.
                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));

                // Bu dairenin en yakın noktasının y koordinatı, bu dairenin y koordinatının diğer dikdörtgenin y koordinat aralığına kısıtlanmış hali olur.
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                // Bu dairenin en yakın noktası ile dairenin merkezi arasındaki x mesafesi
                double distanceX = this.x_Koordinat - closestX;

                // Bu dairenin en yakın noktası ile dairenin merkezi arasındaki y mesafesi
                double distanceY = this.y_Koordinat - closestY;

                // İki mesafenin karesi alınarak toplanır ve böylece uzaklık karesi elde edilir.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, dairenin yarıçapının karesine eşit veya daha küçükse,
                // daire dikdörtgenin içinde veya çevresinde yer alıyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (this.yaricap * this.yaricap);

            }

            else if (digerSekil is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Diğer prizmanın minimum ve maksimum x koordinatları
                double dikdortgenMinX = digerDikdortgenPrizma.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.kenar;
                // Diğer prizmanın minimum ve maksimum x koordinatları
                double dikdortgenMinY = digerDikdortgenPrizma.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.kenar;

                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                double distanceX = this.x_Koordinat - closestX;
                double distanceY = this.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (this.yaricap * this.yaricap);
            }

            return false;
        }
    }

    class Kare : Sekil 
    {
        public int kenar { get; set; }
        public override void Cizdir(Graphics g)
        {
            Random rnd = new Random();

            kenar = rnd.Next(20, 200);
            x_Koordinat = rnd.Next(0, kenar);
            y_Koordinat = rnd.Next(0, kenar);

            Point[] points = new Point[4];
            points[0] = new Point(x_Koordinat, y_Koordinat);
            points[1] = new Point(x_Koordinat + kenar, y_Koordinat);
            points[2] = new Point(x_Koordinat + kenar, y_Koordinat + kenar);
            points[3] = new Point(x_Koordinat, y_Koordinat + kenar);

            g.DrawPolygon(Pens.Red, points);
        }

        public override bool Carpisma(Sekil other)
        {
            if (other is Cember digerCember)
            {
                // Diğer dikdörtgenin minimum ve maksimum x koordinatları
                double dikdortgenMinX = x_Koordinat;
                double dikdortgenMaxX = x_Koordinat + kenar;

                // Diğer dikdörtgenin minimum ve maksimum y koordinatları
                double dikdortgenMinY = y_Koordinat;
                double dikdortgenMaxY = y_Koordinat + kenar;

                // Bu çemberin en yakın noktasının x koordinatı, çemberin x koordinatının diğer çemberin x koordinat aralığına kısıtlanmış hali olur.
                double closestX = Math.Max(digerCember.x_Koordinat, Math.Min(x_Koordinat, digerCember.x_Koordinat + digerCember.yaricap));

                // Bu çemberin en yakın noktasının y koordinatı, çemberin y koordinatının diğer çemberin y koordinat aralığına kısıtlanmış hali olur.
                double closestY = Math.Max(digerCember.y_Koordinat, Math.Min(y_Koordinat, digerCember.y_Koordinat + digerCember.yaricap));

                // Bu çemberin en yakın noktası ile çemberin merkezi arasındaki x mesafesi
                double distanceX = x_Koordinat - closestX;

                // Bu çemberin en yakın noktası ile çemberin merkezi arasındaki y mesafesi
                double distanceY = y_Koordinat - closestY;

                // İki mesafenin karesi alınarak toplanır ve böylece uzaklık karesi elde edilir.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, diğer çemberin yarıçapının karesine eşit veya daha küçükse,
                // çemberler birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (digerCember.yaricap * digerCember.yaricap);
            }

            else if (other is Küre digerKüre)
            {
                // Diğer dikdörtgenin minimum ve maksimum x koordinatları
                double dikdortgenMinX = x_Koordinat;
                double dikdortgenMaxX = x_Koordinat + kenar;

                // Diğer dikdörtgenin minimum ve maksimum y koordinatları
                double dikdortgenMinY = y_Koordinat;
                double dikdortgenMaxY = y_Koordinat + kenar;

                // Bu kürenin en yakın noktasının x koordinatı, kürenin x koordinatının diğer kürenin x koordinat aralığına kısıtlanmış hali olur.
                double closestX = Math.Max(digerKüre.x_Koordinat, Math.Min(x_Koordinat, digerKüre.x_Koordinat + digerKüre.yaricap));

                // Bu kürenin en yakın noktasının y koordinatı, kürenin y koordinatının diğer kürenin y koordinat aralığına kısıtlanmış hali olur.
                double closestY = Math.Max(digerKüre.y_Koordinat, Math.Min(y_Koordinat, digerKüre.y_Koordinat + digerKüre.yaricap));

                // Bu kürenin en yakın noktası ile kürenin merkezi arasındaki x mesafesi
                double distanceX = x_Koordinat - closestX;

                // Bu kürenin en yakın noktası ile kürenin merkezi arasındaki y mesafesi
                double distanceY = y_Koordinat - closestY;

                // İki mesafenin karesi alınarak toplanır ve böylece uzaklık karesi elde edilir.
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Eğer bu uzaklık karesi, diğer kürenin yarıçapının karesine eşit veya daha küçükse,
                // küreler birbirine temas ediyor demektir.
                // Bu durumda true değeri döndürülür, aksi takdirde false değeri döndürülür.
                return distanceSquared <= (digerKüre.yaricap * digerKüre.yaricap);

            }

            else if (other is Kare digerKare)
            {
                // X ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = x_Koordinat + kenar >= digerKare.x_Koordinat && digerKare.x_Koordinat + digerKare.kenar >= x_Koordinat;

                // Y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = y_Koordinat + kenar >= digerKare.y_Koordinat && digerKare.y_Koordinat + digerKare.kenar >= y_Koordinat;

                // Hem X ekseninde hem de Y ekseninde çarpışma durumu kontrol edilir.
                // Eğer her iki eksen üzerinde de çarpışma mevcutsa, true değeri döndürülür.
                // Aksi takdirde, false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;

            }

            else if (other is Küp digerKüp)
            {
                // X ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = x_Koordinat + kenar >= digerKüp.x_Koordinat && digerKüp.x_Koordinat + digerKüp.kenar >= x_Koordinat;

                // Y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = y_Koordinat + kenar >= digerKüp.y_Koordinat && digerKüp.y_Koordinat + digerKüp.kenar >= y_Koordinat;

                // Hem X ekseninde hem de Y ekseninde çarpışma durumu kontrol edilir.
                // Eğer her iki eksen üzerinde de çarpışma mevcutsa, true değeri döndürülür.
                // Aksi takdirde, false değeri döndürülür.
                return xEksenindeCarpisma && yEksenindeCarpisma;

            }

            else if (other is Dikdortgen digerDikdortgen)
            {
                // Kare ve dikdörtgen çarpışma denetimi

                bool xEksenindeCarpisma = x_Koordinat + kenar >= digerDikdortgen.x_Koordinat && digerDikdortgen.x_Koordinat + digerDikdortgen.genislik >= x_Koordinat;
                bool yEksenindeCarpisma = y_Koordinat + kenar >= digerDikdortgen.y_Koordinat && digerDikdortgen.y_Koordinat + digerDikdortgen.en >= y_Koordinat;

                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

            else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Kare ve dikdörtgenprizma çarpışma denetimi

                bool xEksenindeCarpisma = x_Koordinat + kenar >= digerDikdortgenPrizma.x_Koordinat && digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.genislik >= x_Koordinat;
                bool yEksenindeCarpisma = y_Koordinat + kenar >= digerDikdortgenPrizma.y_Koordinat && digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.en >= y_Koordinat;

                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

            if (other is Nokta digerNokta)
            {
                // Çember ile çarpışma kontrolü
                double dikdortgenMinX = x_Koordinat;
                double dikdortgenMaxX = x_Koordinat + kenar;
                double dikdortgenMinY = y_Koordinat;
                double dikdortgenMaxY = y_Koordinat + kenar;

                double closestX = Math.Max(digerNokta.x_Koordinat, Math.Min(x_Koordinat, digerNokta.x_Koordinat + digerNokta.yaricap));
                double closestY = Math.Max(digerNokta.y_Koordinat, Math.Min(y_Koordinat, digerNokta.y_Koordinat + digerNokta.yaricap));

                double distanceX = x_Koordinat - closestX;
                double distanceY = y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (digerNokta.yaricap * digerNokta.yaricap);
            }

            else if (other is Yüzey yuzey)
            {
                // Kare ve yüzeyin çarpışma kontrolü yapılır

                // Kare'nin x ve y koordinatlarından kareX2 ve kareY2 değerleri hesaplanır.
                int kareX2 = x_Koordinat + kenar;
                int kareY2 = y_Koordinat + kenar;

                // Kare'nin yüzey ile çarpışma durumu kontrol edilir.
                // Eğer karenin sağ kenarı yüzeyin sol kenarından küçükse,
                // karenin sol kenarı yüzeyin sağ kenarından büyükse,
                // karenin alt kenarı yüzeyin üst kenarından küçükse veya
                // karenin üst kenarı yüzeyin alt kenarından büyükse, çarpışma yoktur.
                // Bu durumlar sağlanmıyorsa, kare ve yüzey çarpışmış demektir.
                // Dolayısıyla, çarpışma durumu terslenir (!) ve sonuç döndürülür.
                return !(kareX2 < yuzey.x_Koordinat || x_Koordinat > yuzey.x_Koordinat + yuzey.Genislik ||
                         kareY2 < yuzey.y_Koordinat || y_Koordinat > yuzey.y_Koordinat + yuzey.Yukseklik);

            }


            return false;

        }
    }

    class Yüzey : Sekil
    {
        public int Genislik { get; set; }
        public int Yukseklik { get; set; }

        public int kenar { get; set; }


        public Yüzey() 
        {
            Random random = new Random();
            Genislik = random.Next(100);
            Yukseklik = random.Next(100);
            x_Koordinat = random.Next(200);
            y_Koordinat = random.Next(200);
        }
        public Yüzey(int xKoordinat, int yKoordinat, int genislik, int yukseklik)
        {
            x_Koordinat = xKoordinat;
            y_Koordinat = yKoordinat;
            Genislik = genislik;
            Yukseklik = yukseklik;
        }
        public override void Cizdir(Graphics g)
        {
            g.DrawRectangle(Pens.Blue, x_Koordinat, y_Koordinat, Genislik, Yukseklik);
        }

        public override bool Carpisma(Sekil other)
        {
            if (other is Cember digerCember)
            {
                // Yüzey ve çemberin çarpışma kontrolünü yap
                double closestX = Math.Max(x_Koordinat, Math.Min(digerCember.x_Koordinat, x_Koordinat + Genislik));
                double closestY = Math.Max(y_Koordinat, Math.Min(digerCember.y_Koordinat, y_Koordinat + Yukseklik));

                double distanceX = digerCember.x_Koordinat - closestX;
                double distanceY = digerCember.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (digerCember.yaricap * digerCember.yaricap);
            }
            else if (other is Küre digerKüre)
            {
                // Yüzey ve çemberin çarpışma kontrolünü yap
                double closestX = Math.Max(x_Koordinat, Math.Min(digerKüre.x_Koordinat, x_Koordinat + Genislik));
                double closestY = Math.Max(y_Koordinat, Math.Min(digerKüre.y_Koordinat, y_Koordinat + Yukseklik));

                double distanceX = digerKüre.x_Koordinat - closestX;
                double distanceY = digerKüre.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                return distanceSquared <= (digerKüre.yaricap * digerKüre.yaricap);
            }
            else if (other is Dikdortgen digerDikdortgen)
            {
                // Kare ve dikdörtgen çarpışma denetimi

                // Kare sınırlarını belirle
                double kareMinX = x_Koordinat;
                double kareMaxX = x_Koordinat + kenar;
                double kareMinY = y_Koordinat;
                double kareMaxY = y_Koordinat + kenar;

                // Dikdörtgen sınırlarını belirle
                double dikdortgenMinX = digerDikdortgen.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgen.x_Koordinat + digerDikdortgen.genislik;
                double dikdortgenMinY = digerDikdortgen.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgen.y_Koordinat + digerDikdortgen.en;

                // Çarpışma durumunu kontrol et ve sonucu döndür
                return !(kareMaxX < dikdortgenMinX || kareMinX > dikdortgenMaxX || kareMaxY < dikdortgenMinY || kareMinY > dikdortgenMaxY);
            }
            else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Kare ve dikdörtgen çarpışma denetimi

                // Kare sınırlarını belirle
                double kareMinX = x_Koordinat;
                double kareMaxX = x_Koordinat + kenar;
                double kareMinY = y_Koordinat;
                double kareMaxY = y_Koordinat + kenar;

                // Dikdörtgen sınırlarını belirle
                double dikdortgenMinX = digerDikdortgenPrizma.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.genislik;
                double dikdortgenMinY = digerDikdortgenPrizma.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.en;

                // Çarpışma durumunu kontrol et ve sonucu döndür
                return !(kareMaxX < dikdortgenMinX || kareMinX > dikdortgenMaxX || kareMaxY < dikdortgenMinY || kareMinY > dikdortgenMaxY);
            }
            else if (other is Yüzey digerYuzey)
            {
                // İki yüzey arasında çarpışma kontrolü
                bool xEksenindeCarpisma = x_Koordinat + Genislik >= digerYuzey.x_Koordinat && digerYuzey.x_Koordinat + digerYuzey.Genislik >= x_Koordinat;
                bool yEksenindeCarpisma = y_Koordinat + Yukseklik >= digerYuzey.y_Koordinat && digerYuzey.y_Koordinat + digerYuzey.Yukseklik >= y_Koordinat;

                // İki yüzey arasında çarpışmanın olup olmadığını kontrol et
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }
            else if (other is Nokta digerNokta)
            {
                // Noktanın yüzeyin içinde veya üzerinde olup olmadığını kontrol et
                bool xEksenindeCarpisma = digerNokta.x_Koordinat >= x_Koordinat && digerNokta.x_Koordinat <= x_Koordinat + Genislik;
                bool yEksenindeCarpisma = digerNokta.y_Koordinat >= y_Koordinat && digerNokta.y_Koordinat <= y_Koordinat + Yukseklik;

                // Yüzey ve nokta arasında çarpışmanın olup olmadığını kontrol et
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }
            else if (other is Kare digerKare)
            {
                // Kare ve yüzey arasında çarpışmanın olup olmadığını kontrol et

                Random random = new Random();

                // Yüzeyin özelliklerini random değerlerle belirle
                int yuzeyX = random.Next(0, 100); // X koordinatını rastgele bir değerle belirle (0 ile 100 arasında)
                int yuzeyY = random.Next(0, 100); // Y koordinatını rastgele bir değerle belirle (0 ile 100 arasında)
                int yuzeyGenislik = random.Next(1, 50); // Genişliği rastgele bir değerle belirle (1 ile 50 arasında)
                int yuzeyYukseklik = random.Next(1, 50); // Yüksekliği rastgele bir değerle belirle (1 ile 50 arasında)

                Yüzey yuzey = new Yüzey(yuzeyX, yuzeyY, yuzeyGenislik, yuzeyYukseklik);

                // Karenin köşe noktalarının koordinatlarını belirle
                int kareX1 = x_Koordinat;
                int kareY1 = y_Koordinat;
                int kareX2 = x_Koordinat + kenar;
                int kareY2 = y_Koordinat + kenar;

                // Yüzeyin köşe noktalarının koordinatlarını belirle
                int yuzeyX1 = yuzey.x_Koordinat;
                int yuzeyY1 = yuzey.y_Koordinat;
                int yuzeyX2 = yuzey.x_Koordinat + yuzey.Genislik;
                int yuzeyY2 = yuzey.y_Koordinat + yuzey.Yukseklik;

                // Çarpışma kontrolü yap
                bool carpisma = !(kareX2 < yuzeyX1 || kareX1 > yuzeyX2 || kareY2 < yuzeyY1 || kareY1 > yuzeyY2);

                return carpisma;
            }
            else if (other is Küp digerKüp)
            {
                // Küp ve yüzey arasında çarpışmanın olup olmadığını kontrol et

                Random random = new Random();

                // Yüzeyin özelliklerini random değerlerle belirle
                int yuzeyX = random.Next(0, 100); // X koordinatını rastgele bir değerle belirle (0 ile 100 arasında)
                int yuzeyY = random.Next(0, 100); // Y koordinatını rastgele bir değerle belirle (0 ile 100 arasında)
                int yuzeyGenislik = random.Next(1, 50); // Genişliği rastgele bir değerle belirle (1 ile 50 arasında)
                int yuzeyYukseklik = random.Next(1, 50); // Yüksekliği rastgele bir değerle belirle (1 ile 50 arasında)

                Yüzey yuzey = new Yüzey(yuzeyX, yuzeyY, yuzeyGenislik, yuzeyYukseklik);

                // Küpün köşe noktalarının koordinatlarını belirle
                int kareX1 = x_Koordinat;
                int kareY1 = y_Koordinat;
                int kareX2 = x_Koordinat + kenar;
                int kareY2 = y_Koordinat + kenar;

                // Yüzeyin köşe noktalarının koordinatlarını belirle
                int yuzeyX1 = yuzey.x_Koordinat;
                int yuzeyY1 = yuzey.y_Koordinat;
                int yuzeyX2 = yuzey.x_Koordinat + yuzey.Genislik;
                int yuzeyY2 = yuzey.y_Koordinat + yuzey.Yukseklik;

                // Çarpışma kontrolü yap
                bool carpisma = !(kareX2 < yuzeyX1 || kareX1 > yuzeyX2 || kareY2 < yuzeyY1 || kareY1 > yuzeyY2);

                return carpisma;
            }

            return false;
        }
    }

    class Dikdortgen : Sekil //paralelkenar ve nokta sıkıtnı
        {
            Random r = new Random();

            public int genislik;
            public int en;
            public int kenar;
            public Dikdortgen()
            {
                this.x_Koordinat = r.Next(200);
                this.y_Koordinat = r.Next(200);
                this.en = 50;
                this.genislik = 100;
                this.kenar = 100;

            }
            public override void Cizdir(Graphics g)
            {
                g.DrawRectangle(Pens.Red, x_Koordinat, y_Koordinat, en, genislik);
            }
            public override bool Carpisma(Sekil other)
            {
                 if (other is Dikdortgen digerDikdortgen)
            {
                // Diğer dikdörtgen ile çarpışma kontrolü yapılır

                // X ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.en / 2 - digerDikdortgen.x_Koordinat - digerDikdortgen.en / 2) <= (this.en / 2 + digerDikdortgen.en / 2);

                // Y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.genislik / 2 - digerDikdortgen.y_Koordinat - digerDikdortgen.genislik / 2) <= (this.genislik / 2 + digerDikdortgen.genislik / 2);

                // X ve Y eksenlerinde çarpışma durumu kontrol edilir
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

                 else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Diğer dikdörtgen prizma ile çarpışma kontrolü yapılır

                // X ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.en / 2 - digerDikdortgenPrizma.x_Koordinat - digerDikdortgenPrizma.en / 2) <= (this.en / 2 + digerDikdortgenPrizma.en / 2);

                // Y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.genislik / 2 - digerDikdortgenPrizma.y_Koordinat - digerDikdortgenPrizma.genislik / 2) <= (this.genislik / 2 + digerDikdortgenPrizma.genislik / 2);

                // X ve Y eksenlerinde çarpışma durumu kontrol edilir
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

                 else if (other is Cember digerCember)
            {
                // Dikdörtgenin merkez koordinatlarını hesapla
                double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                // Çemberin merkez koordinatlarını hesapla
                double cemberMerkezX = digerCember.x_Koordinat + digerCember.yaricap;
                double cemberMerkezY = digerCember.y_Koordinat + digerCember.yaricap;

                // Merkezler arası mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - cemberMerkezX, 2) + Math.Pow(dikdortgenMerkezY - cemberMerkezY, 2));

                // Minimum mesafeyi hesapla
                double minMesafe = (this.kenar / 2) + digerCember.yaricap;

                // Merkezler arası mesafenin, minimum mesafeden küçük veya eşit olup olmadığını döndür
                return merkezlerArasiMesafe <= minMesafe;
            }


                 else if (other is Küre digerKüre)
            {
                // Dikdörtgenin merkez koordinatlarını hesapla
                double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                // Kürenin merkez koordinatlarını hesapla
                double cemberMerkezX = digerKüre.x_Koordinat + digerKüre.yaricap;
                double cemberMerkezY = digerKüre.y_Koordinat + digerKüre.yaricap;

                // Merkezler arası mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - cemberMerkezX, 2) + Math.Pow(dikdortgenMerkezY - cemberMerkezY, 2));

                // Minimum mesafeyi hesapla
                double minMesafe = (this.kenar / 2) + digerKüre.yaricap;

                // Merkezler arası mesafenin, minimum mesafeden küçük veya eşit olup olmadığını döndür
                return merkezlerArasiMesafe <= minMesafe;
            }

                 else if (other is Kare digerKare)
            {
                // Dikdörtgenin ve diğer karenin x-ekseninde çarpışma kontrolünü yap
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.kenar / 2 - digerKare.x_Koordinat - digerKare.kenar / 2) <= (this.kenar / 2 + digerKare.kenar / 2);

                // Dikdörtgenin ve diğer karenin y-ekseninde çarpışma kontrolünü yap
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.kenar / 2 - digerKare.y_Koordinat - digerKare.kenar / 2) <= (this.kenar / 2 + digerKare.kenar / 2);

                // Hem x-ekseninde hem de y-ekseninde çarpışma olup olmadığını döndür
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

                 else if (other is Küp digerKüp)
            {
                // Dikdörtgenin ve diğer küpün x-ekseninde çarpışma kontrolünü yap
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.kenar / 2 - digerKüp.x_Koordinat - digerKüp.kenar / 2) <= (this.kenar / 2 + digerKüp.kenar / 2);

                // Dikdörtgenin ve diğer küpün y-ekseninde çarpışma kontrolünü yap
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.kenar / 2 - digerKüp.y_Koordinat - digerKüp.kenar / 2) <= (this.kenar / 2 + digerKüp.kenar / 2);

                // Hem x-ekseninde hem de y-ekseninde çarpışma olup olmadığını döndür
                return xEksenindeCarpisma && yEksenindeCarpisma;

            }

                 else if (other is Nokta digerNokta)
            {
                //Dikdörtgenin merkez noktasının x ve y koordinatlarını hesapla
                double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                // Noktanın merkez noktasının x ve y koordinatlarını hesapla
                double cemberMerkezX = digerNokta.x_Koordinat + digerNokta.yaricap;
                double cemberMerkezY = digerNokta.y_Koordinat + digerNokta.yaricap;

                // Dikdörtgenin merkez noktasıyla noktanın merkez noktası arasındaki mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - cemberMerkezX, 2) + Math.Pow(dikdortgenMerkezY - cemberMerkezY, 2));

                // Dikdörtgenin yarı kenarı ile noktanın yarıçapını topla ve minimum mesafeyi hesapla
                double minMesafe = (this.kenar / 2) + digerNokta.yaricap;

                // Merkez noktaları arasındaki mesafenin, minimum mesafeden küçük veya eşit olup olmadığını döndür
                return merkezlerArasiMesafe <= minMesafe;
            }

                else if (other is Yüzey yuzey)
            {
                // Dikdörtgenin sağ üst köşesinin x ve y koordinatlarını hesapla
                int dikdortgenX2 = x_Koordinat + genislik;
                int dikdortgenY2 = y_Koordinat + en;

                // Dikdörtgenin sağ üst köşesinin x koordinatının, yüzeyin sol kenarının sağından daha küçük veya
                // dikdörtgenin sol köşesinin x koordinatının, yüzeyin sağ kenarının solundan daha büyük olup olmadığını kontrol et
                bool carpismaX = !(dikdortgenX2 < yuzey.x_Koordinat || x_Koordinat > yuzey.x_Koordinat + yuzey.Genislik);

                // Dikdörtgenin sağ üst köşesinin y koordinatının, yüzeyin üst kenarının altından daha küçük veya
                // dikdörtgenin sol köşesinin y koordinatının, yüzeyin alt kenarının üstünden daha büyük olup olmadığını kontrol et
                bool carpismaY = !(dikdortgenY2 < yuzey.y_Koordinat || y_Koordinat > yuzey.y_Koordinat + yuzey.Yukseklik);

                // Hem x ekseni hem de y ekseni boyunca çarpışma durumunu kontrol et
                return carpismaX && carpismaY;

            }

                return false;
            }
        }

    class Küre : Sekil  
    {
        public int yaricap;
        public Küre()
        {
            Random r = new Random();
            x_Koordinat = r.Next(200);
            y_Koordinat = r.Next(200);
            yaricap = 100;

        }
        public Küre(string x)
        {
        }
        public override void Cizdir(Graphics g)
        {
            g.FillEllipse(Brushes.Red, x_Koordinat, y_Koordinat, yaricap, yaricap);

        }

        public override bool Carpisma(Sekil other)
        {

            if (other is Cember digerCember)
            {
                // İki merkez arasındaki mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerCember.x_Koordinat + digerCember.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerCember.y_Koordinat + digerCember.yaricap / 2), 2));

                // Merkezler arasındaki mesafe, iki dairenin yarıçaplarının toplamının yarısından küçük veya eşitse çarpışma vardır
                return merkezlerArasiMesafe <= (this.yaricap + digerCember.yaricap) / 2;
            }
            else if (other is Kare digerKare)
            {
                // x ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKare.x_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKare.y_Koordinat - digerKare.kenar / 2) <= (this.yaricap / 2 + digerKare.kenar / 2);

                // Hem x ekseninde çarpışma hem de y ekseninde çarpışma durumunu kontrol et
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }


            if (other is Küp digerKüp)
            {
                // x ekseninde çarpışma kontrolü
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.yaricap / 2 - digerKüp.x_Koordinat - digerKüp.x_Koordinat / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // y ekseninde çarpışma kontrolü
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.yaricap / 2 - digerKüp.y_Koordinat - digerKüp.kenar / 2) <= (this.yaricap / 2 + digerKüp.kenar / 2);

                // Hem x ekseninde çarpışma hem de y ekseninde çarpışma durumunu kontrol et
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }
            else if (other is Dikdortgen digerDikdortgen)
            {
                // Dikdörtgenin sınırlarını belirle
                double dikdortgenMinX = digerDikdortgen.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgen.x_Koordinat + digerDikdortgen.kenar;
                double dikdortgenMinY = digerDikdortgen.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgen.y_Koordinat + digerDikdortgen.genislik;

                // En yakın noktayı hesapla
                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                // Nokta ile en yakın nokta arasındaki mesafeyi hesapla
                double distanceX = this.x_Koordinat - closestX;
                double distanceY = this.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Hesaplanan mesafe, dairenin yarıçapının karesinden küçük veya eşitse çarpışma vardır
                return distanceSquared <= (this.yaricap * this.yaricap);
            }


            if (other is Küre digerKüre)
            {
                // İki merkez arasındaki mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow((this.x_Koordinat + this.yaricap / 2) - (digerKüre.x_Koordinat + digerKüre.yaricap / 2), 2) + Math.Pow((this.y_Koordinat + this.yaricap / 2) - (digerKüre.y_Koordinat + digerKüre.yaricap / 2), 2));

                // Merkezler arasındaki mesafe, iki kürenin yarıçaplarının toplamının yarısından küçük veya eşitse çarpışma vardır
                return merkezlerArasiMesafe <= (this.yaricap + digerKüre.yaricap) / 2;
            }
            else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Dikdörtgenin sınırlarını belirle
                double dikdortgenMinX = digerDikdortgenPrizma.x_Koordinat;
                double dikdortgenMaxX = digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.kenar;
                double dikdortgenMinY = digerDikdortgenPrizma.y_Koordinat;
                double dikdortgenMaxY = digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.kenar;

                // En yakın noktayı hesapla
                double closestX = Math.Max(dikdortgenMinX, Math.Min(this.x_Koordinat, dikdortgenMaxX));
                double closestY = Math.Max(dikdortgenMinY, Math.Min(this.y_Koordinat, dikdortgenMaxY));

                // Nokta ile en yakın nokta arasındaki mesafeyi hesapla
                double distanceX = this.x_Koordinat - closestX;
                double distanceY = this.y_Koordinat - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Hesaplanan mesafe, dairenin yarıçapının karesinden küçük veya eşitse çarpışma vardır
                return distanceSquared <= (this.yaricap * this.yaricap);
            }

            else if (other is Nokta nokta)
            {
                // Nokta ile çarpışma kontrolü
                double distanceX = nokta.x_Koordinat - x_Koordinat;
                double distanceY = nokta.y_Koordinat - y_Koordinat;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Hesaplanan mesafe, dairenin yarıçapının karesinden küçük veya eşitse çarpışma vardır
                return distanceSquared <= (yaricap * yaricap);
            }
            else if (other is Yüzey yuzey)
            {
                // Küre ve yüzeyin çarpışma kontrolünü yapmak için:

                // Kürenin merkez koordinatlarını al
                double kureMerkezX = x_Koordinat + yaricap / 2;
                double kureMerkezY = y_Koordinat + yaricap / 2;

                // Yüzeyin sınırlarını al
                double yuzeyMinX = yuzey.x_Koordinat;
                double yuzeyMaxX = yuzey.x_Koordinat + yuzey.Genislik;
                double yuzeyMinY = yuzey.y_Koordinat;
                double yuzeyMaxY = yuzey.y_Koordinat + yuzey.Yukseklik;

                // Kürenin merkez noktasını yüzeyin sınırları içinde tut
                double closestX = Math.Max(yuzeyMinX, Math.Min(kureMerkezX, yuzeyMaxX));
                double closestY = Math.Max(yuzeyMinY, Math.Min(kureMerkezY, yuzeyMaxY));

                // Kürenin merkez noktası ile en yakın nokta arasındaki uzaklığı hesapla
                double distanceX = kureMerkezX - closestX;
                double distanceY = kureMerkezY - closestY;
                double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                // Hesaplanan mesafe, dairenin yarıçapının karesinden küçük veya eşitse çarpışma vardır
                return distanceSquared <= (yaricap * yaricap);
            }


            return false;
        }

        
    }

    class DikdörtgenPrizma : Sekil//paralelkenar ve nokta sıkıntı
        {
            Random r = new Random();

            public int genislik;
            public int en;
            public int kenar;
            public DikdörtgenPrizma()
            {
                this.x_Koordinat = r.Next(200);
                this.y_Koordinat = r.Next(200);
                this.en = 50;
                this.genislik = 100;
                this.kenar = 100;
            }
            public override void Cizdir(Graphics g)
            {
                g.FillRectangle(Brushes.Red, x_Koordinat, y_Koordinat, en, genislik);
            }
            public override bool Carpisma(Sekil other)
            {

                if (other is Dikdortgen digerDikdortgen)
            {
                // İki dikdörtgenin x ve y ekseninde çarpışma kontrolünü yap
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.en / 2 - digerDikdortgen.x_Koordinat - digerDikdortgen.en / 2) <= (this.en / 2 + digerDikdortgen.en / 2);
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.genislik / 2 - digerDikdortgen.y_Koordinat - digerDikdortgen.genislik / 2) <= (this.genislik / 2 + digerDikdortgen.genislik / 2);

                // Hem x ekseninde hem de y ekseninde çarpışma varsa true döndür
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }
                else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
            {
                // Bir dikdörtgen prizma ile çarpışma kontrolünü yap
                bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.en / 2 - digerDikdortgenPrizma.x_Koordinat - digerDikdortgenPrizma.en / 2) <= (this.en / 2 + digerDikdortgenPrizma.en / 2);
                bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.genislik / 2 - digerDikdortgenPrizma.y_Koordinat - digerDikdortgenPrizma.genislik / 2) <= (this.genislik / 2 + digerDikdortgenPrizma.genislik / 2);

                // Hem x ekseninde hem de y ekseninde çarpışma varsa true döndür
                return xEksenindeCarpisma && yEksenindeCarpisma;
            }

                else if (other is Cember digerCember)
            {
                // Dikdörtgen ile çemberin çarpışma kontrolünü yap

                // Dikdörtgenin merkez noktasını al
                double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                // Çemberin merkez noktasını al
                double cemberMerkezX = digerCember.x_Koordinat + digerCember.yaricap;
                double cemberMerkezY = digerCember.y_Koordinat + digerCember.yaricap;

                // Merkez noktaları arasındaki mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - cemberMerkezX, 2) + Math.Pow(dikdortgenMerkezY - cemberMerkezY, 2));

                // Minimum mesafeyi hesapla
                double minMesafe = (this.kenar / 2) + digerCember.yaricap;

                // Çarpışma durumunu kontrol et
                return merkezlerArasiMesafe <= minMesafe;
            }
                 else if (other is Küre digerKüre)
            {
                // Dikdörtgen ile kürenin çarpışma kontrolünü yap

                // Dikdörtgenin merkez noktasını al
                double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                // Kürenin merkez noktasını al
                double cemberMerkezX = digerKüre.x_Koordinat + digerKüre.yaricap;
                double cemberMerkezY = digerKüre.y_Koordinat + digerKüre.yaricap;

                // Merkez noktaları arasındaki mesafeyi hesapla
                double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - cemberMerkezX, 2) + Math.Pow(dikdortgenMerkezY - cemberMerkezY, 2));

                // Minimum mesafeyi hesapla
                double minMesafe = (this.kenar / 2) + digerKüre.yaricap;

                // Çarpışma durumunu kontrol et
                return merkezlerArasiMesafe <= minMesafe;
            }


                else if (other is Kare digerKare)
                {
                    // Dikdörtgen ile karenin çarpışma kontrolünü yap

                    // X ekseninde çarpışma kontrolü
                    bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.kenar / 2 - digerKare.x_Koordinat - digerKare.kenar / 2) <= (this.kenar / 2 + digerKare.kenar / 2);

                    // Y ekseninde çarpışma kontrolü
                    bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.kenar / 2 - digerKare.y_Koordinat - digerKare.kenar / 2) <= (this.kenar / 2 + digerKare.kenar / 2);

                    // Çarpışma durumunu kontrol et
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }
                else if (other is Küp digerKüp)
                {
                    // Dikdörtgen ile küpün çarpışma kontrolünü yap

                    // X ekseninde çarpışma kontrolü
                    bool xEksenindeCarpisma = Math.Abs(this.x_Koordinat + this.kenar / 2 - digerKüp.x_Koordinat - digerKüp.kenar / 2) <= (this.kenar / 2 + digerKüp.kenar / 2);

                    // Y ekseninde çarpışma kontrolü
                    bool yEksenindeCarpisma = Math.Abs(this.y_Koordinat + this.kenar / 2 - digerKüp.y_Koordinat - digerKüp.kenar / 2) <= (this.kenar / 2 + digerKüp.kenar / 2);

                    // Çarpışma durumunu kontrol et
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }


                else if (other is Nokta digerNokta)
                {
                    // Dikdörtgen ile noktanın çarpışma kontrolünü yap

                    // Dikdörtgenin merkez koordinatlarını al
                    double dikdortgenMerkezX = this.x_Koordinat + this.kenar / 2;
                    double dikdortgenMerkezY = this.y_Koordinat + this.en / 2;

                    // Noktanın merkez koordinatlarını al
                    double noktaMerkezX = digerNokta.x_Koordinat + digerNokta.yaricap;
                    double noktaMerkezY = digerNokta.y_Koordinat + digerNokta.yaricap;

                    // Merkez noktaları arasındaki mesafeyi hesapla
                    double merkezlerArasiMesafe = Math.Sqrt(Math.Pow(dikdortgenMerkezX - noktaMerkezX, 2) + Math.Pow(dikdortgenMerkezY - noktaMerkezY, 2));

                    // Minimum mesafeyi hesapla
                    double minMesafe = (this.kenar / 2) + digerNokta.yaricap;

                    // Çarpışma durumunu kontrol et
                    return merkezlerArasiMesafe <= minMesafe;
                }
                else if (other is Yüzey yuzey)
                {
                    // Dikdörtgen ve yüzeyin çarpışma kontrolünü yap

                    int dikdortgenX2 = x_Koordinat + genislik;
                    int dikdortgenY2 = y_Koordinat + en;

                    // Çarpışma durumunu kontrol et
                    return !(dikdortgenX2 < yuzey.x_Koordinat || x_Koordinat > yuzey.x_Koordinat + yuzey.Genislik ||
                             dikdortgenY2 < yuzey.y_Koordinat || y_Koordinat > yuzey.y_Koordinat + yuzey.Yukseklik);
                 }




                return false;
            }


        }

    class Küp : Sekil //nokta ve paralelkenar sıkıntı
        {
            public int kenar { get; set; }
            public override void Cizdir(Graphics g)
            {
                Random rnd = new Random();

                kenar = rnd.Next(20, 200);
                x_Koordinat = rnd.Next(0, kenar);
                y_Koordinat = rnd.Next(0, kenar);

                Point[] points = new Point[4];
                points[0] = new Point(x_Koordinat, y_Koordinat);
                points[1] = new Point(x_Koordinat + kenar, y_Koordinat);
                points[2] = new Point(x_Koordinat + kenar, y_Koordinat + kenar);
                points[3] = new Point(x_Koordinat, y_Koordinat + kenar);

                g.FillPolygon(Brushes.Red, points);
            }

            public override bool Carpisma(Sekil other)
            {
                if (other is Cember digerCember)
                {
                    // Çember ile çarpışma kontrolü için gerekli hesaplamaları yap

                    // Dikdörtgenin sınırlarını belirle
                    double dikdortgenMinX = x_Koordinat;
                    double dikdortgenMaxX = x_Koordinat + kenar;
                    double dikdortgenMinY = y_Koordinat;
                    double dikdortgenMaxY = y_Koordinat + kenar;

                    // En yakın noktayı bul
                    double closestX = Math.Max(digerCember.x_Koordinat, Math.Min(x_Koordinat, digerCember.x_Koordinat + digerCember.yaricap));
                    double closestY = Math.Max(digerCember.y_Koordinat, Math.Min(y_Koordinat, digerCember.y_Koordinat + digerCember.yaricap));

                    // Nokta ve çember arasındaki mesafeyi hesapla
                    double distanceX = x_Koordinat - closestX;
                    double distanceY = y_Koordinat - closestY;
                    double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return distanceSquared <= (digerCember.yaricap * digerCember.yaricap);
                }
                else if (other is Küre digerKüre)
                {
                    // Küre ile çarpışma kontrolü için gerekli hesaplamaları yap

                    // Dikdörtgenin sınırlarını belirle
                    double dikdortgenMinX = x_Koordinat;
                    double dikdortgenMaxX = x_Koordinat + kenar;
                    double dikdortgenMinY = y_Koordinat;
                    double dikdortgenMaxY = y_Koordinat + kenar;

                    // En yakın noktayı bul
                    double closestX = Math.Max(digerKüre.x_Koordinat, Math.Min(x_Koordinat, digerKüre.x_Koordinat + digerKüre.yaricap));
                    double closestY = Math.Max(digerKüre.y_Koordinat, Math.Min(y_Koordinat, digerKüre.y_Koordinat + digerKüre.yaricap));

                    // Nokta ve küre arasındaki mesafeyi hesapla
                    double distanceX = x_Koordinat - closestX;
                    double distanceY = y_Koordinat - closestY;
                    double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return distanceSquared <= (digerKüre.yaricap * digerKüre.yaricap);
                }


                else if (other is Kare digerKare)
                {
                    // Kare ile çarpışma kontrolü için gerekli hesaplamaları yap

                    // X ekseninde çarpışma durumunu kontrol et
                    bool xEksenindeCarpisma = x_Koordinat + kenar >= digerKare.x_Koordinat && digerKare.x_Koordinat + digerKare.kenar >= x_Koordinat;

                    // Y ekseninde çarpışma durumunu kontrol et
                    bool yEksenindeCarpisma = y_Koordinat + kenar >= digerKare.y_Koordinat && digerKare.y_Koordinat + digerKare.kenar >= y_Koordinat;

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }
                else if (other is Küp digerKüp)
                {
                    // Küp ile çarpışma kontrolü için gerekli hesaplamaları yap

                    // X ekseninde çarpışma durumunu kontrol et
                    bool xEksenindeCarpisma = x_Koordinat + kenar >= digerKüp.x_Koordinat && digerKüp.x_Koordinat + digerKüp.kenar >= x_Koordinat;

                    // Y ekseninde çarpışma durumunu kontrol et
                    bool yEksenindeCarpisma = y_Koordinat + kenar >= digerKüp.y_Koordinat && digerKüp.y_Koordinat + digerKüp.kenar >= y_Koordinat;

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }


                else if (other is Dikdortgen digerDikdortgen)
                {
                    // Kare ve dikdörtgen çarpışma denetimi için gerekli hesaplamaları yap

                    // X ekseninde çarpışma durumunu kontrol et
                    bool xEksenindeCarpisma = x_Koordinat + kenar >= digerDikdortgen.x_Koordinat && digerDikdortgen.x_Koordinat + digerDikdortgen.genislik >= x_Koordinat;

                    // Y ekseninde çarpışma durumunu kontrol et
                    bool yEksenindeCarpisma = y_Koordinat + kenar >= digerDikdortgen.y_Koordinat && digerDikdortgen.y_Koordinat + digerDikdortgen.en >= y_Koordinat;

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }
                else if (other is DikdörtgenPrizma digerDikdortgenPrizma)
                {
                    // Kare ve dikdörtgen prizma çarpışma denetimi için gerekli hesaplamaları yap

                    // X ekseninde çarpışma durumunu kontrol et
                    bool xEksenindeCarpisma = x_Koordinat + kenar >= digerDikdortgenPrizma.x_Koordinat && digerDikdortgenPrizma.x_Koordinat + digerDikdortgenPrizma.genislik >= x_Koordinat;

                    // Y ekseninde çarpışma durumunu kontrol et
                    bool yEksenindeCarpisma = y_Koordinat + kenar >= digerDikdortgenPrizma.y_Koordinat && digerDikdortgenPrizma.y_Koordinat + digerDikdortgenPrizma.en >= y_Koordinat;

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return xEksenindeCarpisma && yEksenindeCarpisma;
                }


                else if (other is Nokta digerNokta)
                {
                    // Çember ile nokta çarpışma kontrolü için gerekli hesaplamaları yap

                    // Çemberin sınırlarını belirle
                    double dikdortgenMinX = x_Koordinat;
                    double dikdortgenMaxX = x_Koordinat + kenar;
                    double dikdortgenMinY = y_Koordinat;
                    double dikdortgenMaxY = y_Koordinat + kenar;

                    // Noktanın en yakın noktasını bul
                    double closestX = Math.Max(digerNokta.x_Koordinat, Math.Min(x_Koordinat, digerNokta.x_Koordinat + digerNokta.yaricap));
                    double closestY = Math.Max(digerNokta.y_Koordinat, Math.Min(y_Koordinat, digerNokta.y_Koordinat + digerNokta.yaricap));

                    // Nokta ile çember arasındaki mesafeyi hesapla
                    double distanceX = x_Koordinat - closestX;
                    double distanceY = y_Koordinat - closestY;
                    double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return distanceSquared <= (digerNokta.yaricap * digerNokta.yaricap);
                }
                else if (other is Yüzey yuzey)
                {
                    // Kare ve yüzeyin çarpışma kontrolünü yap

                    // Karenin köşegen noktalarını belirle
                    int kareX2 = x_Koordinat + kenar;
                    int kareY2 = y_Koordinat + kenar;

                    // Kare ve yüzeyin sınırlarını kontrol et
                    bool carpismaX = !(kareX2 < yuzey.x_Koordinat || x_Koordinat > yuzey.x_Koordinat + yuzey.Genislik);
                    bool carpismaY = !(kareY2 < yuzey.y_Koordinat || y_Koordinat > yuzey.y_Koordinat + yuzey.Yukseklik);

                    // Çarpışma durumunu kontrol et ve sonucu döndür
                    return carpismaX && carpismaY;
                }

            return false;
            }

    }

    
}
