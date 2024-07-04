using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient; // SqlConnection ve SqlCommand için
using Npgsql;
using NpgsqlTypes;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace AracKiralama
{
    public partial class Form7 : Form
    {

        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
            "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");

        private const string veritabaniBaglantisi = "Server=localhost;Port=5432;Database=AracKiralama;User Id=postgres;Password=tjackx4yak;";

        public Form7()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string sorgu = "select * from musteriinceleme";
            NpgsqlDataAdapter da = new NpgsqlDataAdapter(sorgu, baglanti);
            DataSet ds = new DataSet();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // TextBox'lardan verileri al
            int aracID = Convert.ToInt32(textBox1.Text);
            string incelemeMetni = textBox5.Text;

            // SQL sorgusu
            string sqlSorgusu = "INSERT INTO MusteriInceleme (AracID, IncelemeMetni) VALUES (@AracID, @IncelemeMetni)";

            using (NpgsqlConnection baglanti = new NpgsqlConnection(veritabaniBaglantisi))
            {
                using (NpgsqlCommand komut = new NpgsqlCommand(sqlSorgusu, baglanti))
                {
                    // Parametreleri ekle
                    komut.Parameters.AddWithValue("@AracID", aracID);
                    komut.Parameters.AddWithValue("@IncelemeMetni", incelemeMetni);

                    // Bağlantıyı aç
                    baglanti.Open();

                    // Komutu çalıştır
                    komut.ExecuteNonQuery();

                    // Bağlantıyı kapat
                    baglanti.Close();
                }
            }

            MessageBox.Show("Veri başarıyla eklendi.");
        }
    }
}

