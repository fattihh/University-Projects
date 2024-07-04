using System;
using System.Drawing;
using System.Reflection;
using System.Reflection.Emit;
using System.Security.Policy;
using System.Threading;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Xml.Linq;
using Microsoft.VisualBasic.Devices;
/****************************************************************************
** SAKARYA ÜNİVERSİTESİ
** BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
** BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
** PROGRAMLAMAYA GİRİŞİ DERSİ
**
** ÖDEV NUMARASI…...:  PROJE 1 
** ÖĞRENCİ ADI...............: FATİH UÇAR
** ÖĞRENCİ NUMARASI.: G211210038
** DERS GRUBU…………: 2C
YOUTUBE LİNKİ… …: https://www.youtube.com/watch?v=gEzIFQ4JdgA&feature=youtu.be
****************************************************************************/
namespace carpismaodevi
{
    public partial class Form1 : Form
    {
        private string selectedShape1;//Comboboxtan nesne seçmek için string tanımladık iki tane
        private string selectedShape2;
        private List<string> shapeList;//Comboboxtaki nesneleri eklemek için bir tane List türünden bir string olusturdum.

        private Sekil shape1;//Sekilleri cizdirmek için Sekil türünden 2 tane nesne tanımladım
        private Sekil shape2;

        public Form1()
        {
            InitializeComponent();
            groupBox1.Enter += groupBox1_Enter;
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            comboBox2.SelectedIndexChanged += comboBox2_SelectedIndexChanged;
            panel1.Paint += panel1_Paint;

            selectedShape1 = "";
            selectedShape2 = "";
            //Comboboxlara eklenecek liste
            shapeList = new List<string> { "Yüzey", "Cember", "Dikdortgen", "Kare", "Nokta", "Küre", "Dikdörtgen Prizma", "Küp" };
            //Comboboxlara ekleme
            comboBox1.Items.AddRange(shapeList.ToArray());
            comboBox2.Items.AddRange(shapeList.ToArray());
           

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();//hem groupbox'a hem combobox ekledigimiz icin bir tane clear yaptık
            comboBox1.Items.AddRange(shapeList.ToArray());
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Comboboxtaki secilen seçenek boş değilse nesne cizdirir.
            if (comboBox1.SelectedItem == null || comboBox1.SelectedItem.ToString() == "")
            {
                return;
            }
            selectedShape1 = comboBox1.SelectedItem.ToString();
            shape1 = CreateShape(selectedShape1);//sekile createshape metodu ile nesne atama
            panel1.Invalidate();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Comboboxtaki secilen seçenek boş değilse nesne cizdirir.
            if (comboBox2.SelectedItem == null || comboBox2.SelectedItem.ToString() == "")
            {
                return;
            }
            selectedShape2 = comboBox2.SelectedItem.ToString();
            shape2 = CreateShape(selectedShape2);//sekile createshape metodu ile nesne atama
            panel1.Invalidate();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {
            //combobox seçerken boş değilse şekli oluştur
            if (comboBox2.SelectedItem != null)
            {
                selectedShape2 = comboBox2.SelectedItem.ToString();
                shape2 = CreateShape(selectedShape2);
                panel1.Invalidate();
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            //eğer sekil ve sekil 2 boş değilse sekilleri cizdir
            Graphics g = e.Graphics;
            if (shape1 != null)
            {
                shape1.Cizdir(g);
            }
            if (shape2 != null)
            {
                shape2.Cizdir(g);
            }
        }

        private Sekil CreateShape(string shape)
        {
            //secilen stringe göre switch case ile nesne döndürme.
            switch (shape)
            {
                case "Kare":
                    return new Kare();
                case "Cember":
                    return new Cember();
                case "Dikdortgen":
                    return new Dikdortgen();
                case "Yüzey":
                    return new Yüzey();
                case "Dikdörtgen Prizma":
                    return new DikdörtgenPrizma();
                case "Nokta":
                    return new Nokta();
                case "Küre":
                    return new Küre();
                case "Küp":
                    return new Küp();
                default:
                    return null;
            }
        }

        private void Kontrol_Click(object sender, EventArgs e)
        {
            //sekiller boş değilse çarpışma denetimi yaptırma.
            if (shape1 != null && shape2 != null && !string.IsNullOrEmpty(selectedShape1) && !string.IsNullOrEmpty(selectedShape2))
            {
                if (shape1.Carpisma(shape2))
                {
                    MessageBox.Show("Şekiller Çarpıştı!");
                }
                else
                {
                    MessageBox.Show("Şekiller Çarpışmadı.");
                }
            }
            else
            {
                MessageBox.Show("Lütfen iki şekil seçin.");
            }
        }
    }
}