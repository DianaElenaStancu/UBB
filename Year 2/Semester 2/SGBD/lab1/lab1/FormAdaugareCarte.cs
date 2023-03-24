using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class FormAdaugareCarte : Form
    {
        private readonly string idAutor;
        SqlConnection connection = new SqlConnection(@"Server=DESKTOP-AQ7EMHF;Database=library_database_sem4;
        Integrated Security=true;TrustServerCertificate=true;");
        SqlDataAdapter adapterDataLimbi = new SqlDataAdapter();
        DataSet dsLimbi = new DataSet();
        SqlDataAdapter adapterDataSubdepartamente = new SqlDataAdapter();
        DataSet dsSubdepartamente = new DataSet();
        SqlDataAdapter adapterDataEdituri = new SqlDataAdapter();
        DataSet dsEdituri = new DataSet();
        SqlDataAdapter adapterDataCarti = new SqlDataAdapter();
        public FormAdaugareCarte(string idAutor)
        {
            this.idAutor = idAutor;
            InitializeComponent();
        }

        private void FillComboBoxLimbi()
        {
            adapterDataLimbi.SelectCommand = new SqlCommand("select * from Languages", connection);
            dsLimbi.Clear();
            adapterDataLimbi.Fill(dsLimbi);
            comboBoxLanguage.DataSource = dsLimbi.Tables[0];
            comboBoxLanguage.DisplayMember = "name";
        }

        private void FillComboBoxSubdepartamente()
        {
            adapterDataSubdepartamente.SelectCommand = new SqlCommand("select * from BookSubdepartments", connection);
            dsSubdepartamente.Clear();
            adapterDataSubdepartamente.Fill(dsSubdepartamente);
            comboBoxSubdepartamente.DataSource = dsSubdepartamente.Tables[0];
            comboBoxSubdepartamente.DisplayMember = "name";
        }

        private void FillComboBoxEdituri()
        {
            adapterDataEdituri.SelectCommand = new SqlCommand("select * from Publishers", connection);
            dsEdituri.Clear();
            adapterDataEdituri.Fill(dsEdituri);
            comboBoxEdituri.DataSource = dsEdituri.Tables[0];
            comboBoxEdituri.DisplayMember = "name";
        }

        private void FormAdaugareCarte_Load(object sender, EventArgs e)
        {
            FillComboBoxLimbi();
            FillComboBoxSubdepartamente();
            FillComboBoxEdituri();
            labelId.Text += this.idAutor;
        }

        private void ButtonAdaugaCarte_Click(object sender, EventArgs e)
        {
            try
            {
                string ISBN = textBoxISBN.Text.ToUpper();
                string titlu = textBoxTitlu.Text;
                int limbaId = (int)dsLimbi.Tables[0].Rows[comboBoxLanguage.SelectedIndex]["id"];
                int subdepartmentId = (int)dsSubdepartamente.Tables[0].Rows[comboBoxSubdepartamente.SelectedIndex]["id"];
                int edituraId = (int)dsEdituri.Tables[0].Rows[comboBoxEdituri.SelectedIndex]["id"];
                bool activ = (bool)checkBoxActive.Checked;
                string conditii = textBoxStare.Text;
                DateTime dataPublicarii = (DateTime)dateTimePicker.Value;
                string mentiuni = textBoxMentiuni.Text;

                string confirmare = "Doriti sa adaugati urmatoarea carte cu id-ul autorului: " + idAutor + ") in:\n" +
                    "ISBN: " + ISBN + "\n" +
                    "Titlu: " + titlu + "\n" +
                    "limbaId: " + limbaId + "\n" +
                    "subdepartamentId: " + subdepartmentId + "\n" +
                    "edituraId: " + edituraId + "\n" +
                    "active: " + activ + "\n" +
                    "conditii: " + conditii + "\n" +
                    "data publicarii: " + dataPublicarii + "\n" +
                    "mentiuni: " + mentiuni + "?\n";

                DialogResult dialogResult = MessageBox.Show(confirmare, "Confirmare adaugare", MessageBoxButtons.OKCancel);
                if (dialogResult == DialogResult.OK)
                {
                    adapterDataCarti.DeleteCommand = new SqlCommand("insert into Books(ISBN, title, author, language_id, subdepartment_id," +
                        "publisher, active, conditions, publication_date, mentions) values " +
                        "(@ISBN, @titlu, @autor, @limbaId, @subdepartamentId, @edituraId, @activ, @conditii, @dataPublicarii, @mentiuni)", connection);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@ISBN", ISBN);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@titlu", titlu);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@autor", idAutor);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@limbaId", limbaId);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@subdepartamentId", subdepartmentId);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@edituraId", edituraId);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@activ", activ);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@conditii", conditii);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@dataPublicarii", dataPublicarii);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@mentiuni", mentiuni);

                    connection.Open();
                    adapterDataCarti.DeleteCommand.ExecuteNonQuery();
                    connection.Close();

                    MessageBox.Show("Carte adaugata cu succes", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            } catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }
    }
}
