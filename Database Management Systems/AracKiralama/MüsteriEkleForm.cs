using Npgsql;
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
    public partial class MüsteriEkleForm : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
           "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");



        public MüsteriEkleForm()
        {
            InitializeComponent();
        }


        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                // TextBox kontrollerinden müşteri bilgilerini al
                string ad = textBox1.Text;
                string soyad = textBox5.Text;
                string eposta = textBox4.Text;
                string telefon = textBox3.Text;
                string adres = textBox2.Text;

                // PostgreSQL bağlantısını aç
                baglanti.Open();

                // PostgreSQL komutunu oluştur
                using (NpgsqlCommand cmd = new NpgsqlCommand())
                {
                    cmd.Connection = baglanti;
                    cmd.CommandType = CommandType.Text;

                    // MusteriEkle fonksiyonunu çağır
                    cmd.CommandText = $"SELECT MusteriEkle('{ad}', '{soyad}', '{eposta}', '{telefon}', '{adres}')";

                    // Komutu çalıştır
                    cmd.ExecuteNonQuery();
                }

                baglanti.Close();

                MessageBox.Show("Müşteri başarıyla eklendi.", "Başarı", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Hata: " + ex.Message, "Hata", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

    }

}
