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

namespace AracKiralama
{
    public partial class Form6 : Form
    {
        NpgsqlConnection baglanti = new NpgsqlConnection("server=localhost; " +
           "port=5432;" + "Database=AracKiralama;" + "user Id=postgres;" + "password=tjackx4yak");


        private string connectionString = "Host=localhost;Username=postgres;Password=tjackx4yak;Database=AracKiralama";

        public Form6()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int subeID = Convert.ToInt32(textBox1.Text);

            try
            {
                using (NpgsqlConnection connection = new NpgsqlConnection(connectionString))
                {
                    connection.Open();

                    using (NpgsqlCommand cmd = new NpgsqlCommand("SELECT GetPersonelSayisi(@p_SubeID)", connection))
                    {
                        cmd.Parameters.AddWithValue("@p_SubeID", subeID);

                        // Fonksiyondan dönen değeri almak için ExecuteScalar kullanılır.
                        int personelSayisi = Convert.ToInt32(cmd.ExecuteScalar());

                        MessageBox.Show($"SubeID {subeID} için personel sayısı: {personelSayisi}");
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Hata oluştu: " + ex.Message);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string sorgu = "select * from subeler";
            NpgsqlDataAdapter da = new NpgsqlDataAdapter(sorgu, baglanti);
            DataSet ds = new DataSet();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }
    }

}
