using Npgsql;
using Npgsql.Util;
using NpgsqlTypes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AracKiralama
{
    public partial class Form3 : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
            "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");
        public Form3()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                baglanti.Open();

                // Müşteri bilgilerini ekleme
                NpgsqlCommand komutMusteri = new NpgsqlCommand("INSERT INTO musteri (ad, soyad, eposta, telefon, adres) VALUES " +
                    "(@p1, @p2, @p3, @p4, @p5) RETURNING musteriid", baglanti);

                komutMusteri.Parameters.AddWithValue("@p1", textBox1.Text);
                komutMusteri.Parameters.AddWithValue("@p2", textBox5.Text);
                komutMusteri.Parameters.AddWithValue("@p3", textBox6.Text);
                komutMusteri.Parameters.AddWithValue("@p4", textBox7.Text);
                komutMusteri.Parameters.AddWithValue("@p5", textBox2.Text);

                // Yeni eklenen müşterinin ID'sini al
                int musteriId = Convert.ToInt32(komutMusteri.ExecuteScalar());

                // Rezervasyon bilgilerini ekleme
                NpgsqlCommand komutRezervasyon = new NpgsqlCommand("INSERT INTO rezervasyonlar (musteriid, rezervasyontarih, baslangicsaat, bitissaat) VALUES " +
                   "(@p1, @p2, @p3, @p4)", baglanti);

                // @p1 için DateTime türüne dönüştürme
                if (DateTime.TryParse(textBox4.Text, out DateTime parsedDateTime))
                {
                    komutRezervasyon.Parameters.AddWithValue("@p1", musteriId);
                    komutRezervasyon.Parameters.AddWithValue("@p2", NpgsqlDbType.Timestamp).Value = parsedDateTime;
                    // Diğer parametre eklemeleri buraya gelir
                    komutRezervasyon.Parameters.AddWithValue("@p3", NpgsqlDbType.Integer).Value = int.Parse(textBox3.Text);
                    komutRezervasyon.Parameters.AddWithValue("@p4", NpgsqlDbType.Integer).Value = int.Parse(textBox8.Text);

                    komutRezervasyon.ExecuteNonQuery();
                }
                else
                {
                    Console.WriteLine("Geçersiz tarih formatı!");
                }

                MessageBox.Show("Müşteri müşteri tablosuna eklendi ve rezervasyon yapıldı.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Hata: " + ex.Message);
            }
            finally
            {
                baglanti.Close();
            }
        }


    }
}
