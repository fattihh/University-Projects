using Npgsql;
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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace AracKiralama
{

    public partial class Form4 : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
            "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");

        private const string veritabaniBaglantisi = "Server=localhost;Port=5432;Database=AracKiralama;User Id=postgres;Password=tjackx4yak;";


        public Form4()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                baglanti.Open();

                // Müşteri bilgilerini ekleme
                NpgsqlCommand komutPersonelEkle = new NpgsqlCommand("INSERT INTO personel (ad, soyad, pozisyon, subeid) VALUES " +
                    "(@p1, @p2, @p3, @p4) ", baglanti);

                komutPersonelEkle.Parameters.AddWithValue("@p1", textBox1.Text);
                komutPersonelEkle.Parameters.AddWithValue("@p2", textBox5.Text);
                komutPersonelEkle.Parameters.AddWithValue("@p3", textBox4.Text);

                // subeid'yi int'e çevirme işlemi
                if (int.TryParse(textBox2.Text, out int subeID))
                {
                    komutPersonelEkle.Parameters.AddWithValue("@p4", subeID);
                }
                else
                {
                    MessageBox.Show("Geçersiz SubeID. Lütfen geçerli bir sayısal değer girin.");
                    return; // işlemi sonlandır
                }

                int etkilenenSatirSayisi = komutPersonelEkle.ExecuteNonQuery();

                if (etkilenenSatirSayisi > 0)
                {
                    MessageBox.Show("Personel başarıyla eklendi!");
                }
                else
                {
                    MessageBox.Show("Personel eklenemedi.");
                }
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

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                baglanti.Open();

                // Kullanıcının girdiği bilgileri alın
                string ad = textBox1.Text;
                string soyad = textBox5.Text;
                string pozisyon = textBox4.Text;

                // subeid'yi int'e çevirme işlemi
                if (!int.TryParse(textBox2.Text, out int subeID))
                {
                    MessageBox.Show("Geçersiz SubeID.");
                    return; // işlemi sonlandır
                }

                // Personel silme
                NpgsqlCommand komutPersonelSil = new NpgsqlCommand("DELETE FROM personel WHERE ad = @p1 AND soyad = @p2 AND pozisyon = @p3 AND subeid = @p4", baglanti);
                komutPersonelSil.Parameters.AddWithValue("@p1", ad);
                komutPersonelSil.Parameters.AddWithValue("@p2", soyad);
                komutPersonelSil.Parameters.AddWithValue("@p3", pozisyon);
                komutPersonelSil.Parameters.AddWithValue("@p4", subeID);

                int etkilenenSatirSayisi = komutPersonelSil.ExecuteNonQuery();

                if (etkilenenSatirSayisi > 0)
                {
                    MessageBox.Show("Personel başarıyla silindi!");
                }
                else
                {
                    MessageBox.Show("Belirtilen bilgilere sahip personel bulunamadı veya silinemedi.");
                }
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

        private void button4_Click(object sender, EventArgs e)
        {
            string sorgu = "select * from personel";
            NpgsqlDataAdapter da = new NpgsqlDataAdapter(sorgu, baglanti);
            DataSet ds = new DataSet();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }
    }


}

