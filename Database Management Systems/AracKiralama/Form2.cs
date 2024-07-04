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
    public partial class Form2 : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
            "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");

        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string aracTuru = textBox1.Text;
            string marka = textBox5.Text;
            string model = textBox4.Text;

            try
            {
                baglanti.Open();

                // PostgreSQL fonksiyonunu çağırmak için kullanılan SQL sorgusu
                string query = "SELECT * FROM GetAracListesi(@aracTuru, @marka, @model, null)";

                using (NpgsqlCommand cmd = new NpgsqlCommand(query, baglanti))
                {
                    // Parametreleri ekleyerek SQL Injection saldırılarına karşı korunma
                    cmd.Parameters.AddWithValue("@aracTuru", aracTuru);
                    cmd.Parameters.AddWithValue("@marka", marka);

                    // Null değeri için özel bir işlem yapmamıza gerek yok
                    // PostgreSQL, null değerini uygun bir şekilde işleyecektir.
                    cmd.Parameters.AddWithValue("@model", model);

                    using (NpgsqlDataReader reader = cmd.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            // Araç bulundu, aracın ID'sini al
                            int aracID = reader.GetInt32(reader.GetOrdinal("AracID"));

                            // Gerekli işlemleri yapabilirsiniz
                            MessageBox.Show("Araç bulundu! AracID: " + aracID.ToString());
                        }
                        else
                        {
                            // Araç bulunamadı
                            MessageBox.Show("Araç bulunamadı!");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Hata oluştu: " + ex.Message);
            }
            finally
            {
                baglanti.Close(); // Bağlantıyı kapat
            }
        }


        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                string connectionStr = "Server=localhost;Port=5432;Database=AracKiralama;User Id=postgres;Password=tjackx4yak;";

                using (NpgsqlConnection baglanti = new NpgsqlConnection(connectionStr))
                {
                    baglanti.Open();

                    // Müşteri bilgilerini ekleme
                    using (NpgsqlCommand komutAracKiralama = new NpgsqlCommand("INSERT INTO AracKiralamaGecmisi (aracid, telefon, kiralamatarihi, iadetarihi, odeme) VALUES " +
                         "(@p1, @p2, @p3, @p4, @p5)", baglanti))
                    {
                        komutAracKiralama.Parameters.AddWithValue("@p1", int.Parse(textBox7.Text));
                        komutAracKiralama.Parameters.AddWithValue("@p2", textBox2.Text);
                        komutAracKiralama.Parameters.AddWithValue("@p3", DateTime.Parse(textBox9.Text)); // Tarih formatına uygun şekilde dönüştür
                        komutAracKiralama.Parameters.AddWithValue("@p4", DateTime.Parse(textBox6.Text)); // Tarih formatına uygun şekilde dönüştür
                        komutAracKiralama.Parameters.AddWithValue("@p5", Convert.ToDecimal(textBox8.Text));

                        komutAracKiralama.ExecuteNonQuery();

                        // Display success message if the execution is successful
                        MessageBox.Show("Araç kiralandı!", "Başarılı", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Hata: " + ex.Message, "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


    }
}



