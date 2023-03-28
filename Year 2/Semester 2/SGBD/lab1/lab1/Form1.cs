using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace lab1
{
    public partial class Form1 : Form
    {
        SqlConnection connection = new SqlConnection(@"Server=DESKTOP-AQ7EMHF;Database=library_database_sem4;
        Integrated Security=true;TrustServerCertificate=true;");
        SqlDataAdapter adapterDataAutori = new SqlDataAdapter();
        DataSet dsAutori = new DataSet();
        SqlDataAdapter adapterDataCarti = new SqlDataAdapter();
        DataSet dsCarti = new DataSet();
        DataSet dataSet = new DataSet();
        BindingSource bindingSourceCarti = new BindingSource();
        BindingSource bindingSourceAutori = new BindingSource();
        public Form1()
        {
            InitializeComponent();
        }

        private void BibliotecaFormLoad(object sender, EventArgs e)
        {
            try
            {
                /*
                adapterDataAutori.SelectCommand = new SqlCommand("select * from Authors", connection);
                dsAutori.Clear();
                adapterDataAutori.Fill(dsAutori);
                dataGridViewAutori.DataSource = dsAutori.Tables[0];*/
                connection.Open();
                adapterDataAutori.SelectCommand = new SqlCommand("select * from Authors", connection);
                adapterDataCarti.SelectCommand = new SqlCommand("select * from Books", connection);
                adapterDataAutori.Fill(dataSet, "Authors");
                adapterDataCarti.Fill(dataSet, "Books");
                bindingSourceAutori.DataSource = dataSet.Tables["Authors"];
                dataGridViewAutori.DataSource = bindingSourceAutori;
                DataColumn columnAutori = dataSet.Tables["Authors"].Columns["id"];
                DataColumn columnCarti = dataSet.Tables["Books"].Columns["author"];
                DataRelation relation = new DataRelation("FK_Authors_Books", columnAutori, columnCarti);
                dataSet.Relations.Add(relation);
                bindingSourceCarti.DataSource = bindingSourceAutori;
                bindingSourceCarti.DataMember = "FK_Authors_Books";
                dataGridViewCarti.DataSource = bindingSourceCarti;
                
                buttonStergeCarte.Enabled = false;
                buttonActualizeazaCarte.Enabled = false;
            } catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void DataGridViewAutoriCellClicked(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (dataGridViewAutori.Rows[e.RowIndex] != null)
                {
                    adapterDataCarti.SelectCommand = new SqlCommand("select * from Books where author=@authorId", connection);
                    adapterDataCarti.SelectCommand.Parameters.AddWithValue("@authorId", dataGridViewAutori.Rows[e.RowIndex].Cells["id"].FormattedValue);
                    dsCarti.Clear();
                    adapterDataCarti.Fill(dsCarti);
                    dataGridViewCarti.DataSource = dsCarti.Tables[0];

                    buttonAdaugaCarte.Enabled = true;
                    buttonActualizeazaCarte.Enabled = false;
                    buttonStergeCarte.Enabled = false;
                }
            } catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }


        private void DataGridViewCellCartiClicked(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (dataGridViewCarti.Rows[e.RowIndex] != null)
                {
                    buttonActualizeazaCarte.Enabled = true;
                    buttonStergeCarte.Enabled = true;
                    buttonAdaugaCarte.Enabled = false;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void ButtonAdaugaCarte_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewAutori.CurrentCell != null)
                {
                    int index = dataGridViewAutori.CurrentCell.RowIndex;
                    string idCarte = dataGridViewAutori.Rows[index].Cells["id"].FormattedValue.ToString();
                    Form formAdaugareCarte = new FormAdaugareCarte(idCarte);
                    formAdaugareCarte.ShowDialog();
                    dsCarti.Clear();
                    adapterDataCarti.Fill(dsCarti);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }

        }

        private void ButtonStergeCarte_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewCarti.CurrentCell.RowIndex;
                string carteId = dataGridViewCarti.Rows[index].Cells["id"].FormattedValue.ToString();
                DialogResult dialogResult = MessageBox.Show("Sigur doriti sa stergeti inregistrarea cu id " + carteId + "?", "Confirmare stergere", MessageBoxButtons.OKCancel);
                if (dialogResult == DialogResult.OK)
                {
                    adapterDataCarti.DeleteCommand = new SqlCommand("delete from Books where id = @id", connection);
                    adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@id", carteId);

                    connection.Open();
                    adapterDataCarti.DeleteCommand.ExecuteNonQuery();
                    connection.Close();

                    MessageBox.Show("Carte stearsa cu succes", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    dsCarti.Clear();
                    adapterDataCarti.Fill(dsCarti);
                }
            } catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonActualizeazaCarte_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewCarti.CurrentCell != null)
                {
                    int index = dataGridViewCarti.CurrentCell.RowIndex;

                    int id = (int)dataGridViewCarti.Rows[index].Cells["id"].Value;
                    string ISBN = dataGridViewCarti.Rows[index].Cells["ISBN"].FormattedValue.ToString().ToUpper();
                    string titlu = dataGridViewCarti.Rows[index].Cells["title"].FormattedValue.ToString();
                    int autor = (int)dataGridViewCarti.Rows[index].Cells["author"].Value;
                    int limbaId = (int)dataGridViewCarti.Rows[index].Cells["language_id"].Value;
                    int subdepartmentId = (int)dataGridViewCarti.Rows[index].Cells["subdepartment_id"].Value;
                    int edituraId = (int)dataGridViewCarti.Rows[index].Cells["subdepartment_id"].Value;
                    bool activ = (bool)dataGridViewCarti.Rows[index].Cells["active"].Value;
                    string conditii = dataGridViewCarti.Rows[index].Cells["conditions"].FormattedValue.ToString();
                    DateTime dataPublicarii = (DateTime)dataGridViewCarti.Rows[index].Cells["publication_date"].Value;
                    string mentiuni = dataGridViewCarti.Rows[index].Cells["mentions"].FormattedValue.ToString();

                    string confirmare = "Doriti sa schimbati linia selectata (cartea cu id: " + id +  ") in:\n" +
                        "ISBN: " + ISBN + "\n" +
                        "Titlu: " + titlu + "\n" +
                        "Autor: " + autor + "\n" +
                        "limbaId: " + limbaId + "\n" +
                        "subdepartamentId: " + subdepartmentId + "\n" +
                        "edituraId: " + edituraId + "\n" +
                        "active: " + activ + "\n" +
                        "conditii: " + conditii + "\n" +
                        "data publicarii: " + dataPublicarii + "\n" +
                        "mentiuni: " + mentiuni + "?\n";
                    DialogResult dialogResult = MessageBox.Show(confirmare, "Confirmare actualizare", MessageBoxButtons.OKCancel);
                    if (dialogResult == DialogResult.OK)
                    {
                        adapterDataCarti.DeleteCommand = new SqlCommand("update Books " +
                            "set ISBN = @ISBN, title = @titlu, author = @autor, language_id = @limbaId," +
                            "subdepartment_id = @subdepartamentId, publisher = @edituraId, active = @activ," +
                            "conditions = @conditii, publication_date = @dataPublicarii, mentions = @mentiuni " +
                            "where id = @id", connection);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@ISBN", ISBN);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@titlu", titlu);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@autor", autor);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@limbaId", limbaId);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@subdepartamentId", subdepartmentId);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@edituraId", edituraId);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@activ", activ);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@conditii", conditii);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@dataPublicarii", dataPublicarii);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@mentiuni", mentiuni);
                        adapterDataCarti.DeleteCommand.Parameters.AddWithValue("@id", id);

                        connection.Open();
                        adapterDataCarti.DeleteCommand.ExecuteNonQuery();
                        connection.Close();

                        MessageBox.Show("Carte actualizata cu succes", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        dsCarti.Clear();
                        adapterDataCarti.Fill(dsCarti);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }
    }
}
