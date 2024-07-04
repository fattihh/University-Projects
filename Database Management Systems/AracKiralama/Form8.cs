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

namespace AracKiralama
{
    public partial class Form8 : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
              "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");

        private const string veritabaniBaglantisi = "Server=localhost;Port=5432;Database=AracKiralama;User Id=postgres;Password=tjackx4yak;";

        public Form8()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // TextBox'lardan verileri alın
            int aracID = Convert.ToInt32(textBox1.Text);
            DateTime kazaTarihi = DateTime.Parse(textBox5.Text);
            string hasarAciklama = textBox3.Text;
            decimal hasarTutar = Convert.ToDecimal(textBox2.Text);

            // PostgreSQL Connection String'i
            string connectionString = "Host=localhost;Port=5432;Username=postgres;Password=tjackx4yak;Database=AracKiralama;";

            // NpgsqlConnection oluşturun
            using (NpgsqlConnection baglanti = new NpgsqlConnection(connectionString))
            {
                // SQL sorgusu
                string sorgu = "INSERT INTO KazaHasarBilgileri (AracID, Kaza_Tarihi, HasarAciklama, HasarTutar) VALUES (@AracID, @Kaza_Tarihi, @HasarAciklama, @HasarTutar)";

                // NpgsqlCommand oluşturun
                using (NpgsqlCommand komut = new NpgsqlCommand(sorgu, baglanti))
                {
                    // Parametreleri ekleyin
                    komut.Parameters.AddWithValue("@AracID", aracID);
                    komut.Parameters.AddWithValue("@Kaza_Tarihi", kazaTarihi);
                    komut.Parameters.AddWithValue("@HasarAciklama", hasarAciklama);
                    komut.Parameters.AddWithValue("@HasarTutar", hasarTutar);

                    try
                    {
                        // Bağlantıyı açın
                        baglanti.Open();

                        // Sorguyu çalıştırın
                        komut.ExecuteNonQuery();

                        MessageBox.Show("Kaza eklendi.");
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Hata oluştu: " + ex.Message);
                    }
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string sorgu = "select * from kazahasarbilgileri";
            NpgsqlDataAdapter da = new NpgsqlDataAdapter(sorgu, baglanti);
            DataSet ds = new DataSet();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }
    }
}
