using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;
using System.Collections.Generic;

namespace lab1
{
    public partial class Home : Form
    {
/*        <add key = "ParentTableName" value="Authors"/>
		<add key = "ChildTableName" value="Books"/>
		<add key = "ChildNumberOfColumns" value="10"/>
		<add key = "ChildLabelNames" value="ISBN,title,author,language_id,subdepartment_id,publisher,active,conditions,publication_date,mentions"/>
		<add key = "ColumnNamesInsertParameters" value="@ISBN,@title,@author,@language_id,@subdepartment_id,@publisher,@active,@conditions,@publication_date,@mentions"/>
		<add key = "UpdateQuery" value="update Books set ISBN = @ISBN, title = @title, author = @author, language_id = @language_id,subdepartment_id = @subdepartment_id, publisher = @publisher, active = @active, conditions = @conditions, publication_date = @publication_date, mentions = @mentions where id = @id"/>
		<add key = "SelectQuery" value="select * from Books"/>
		<add key = "SelectParent" value="select * from Authors"/>
		<add key = "SelectChild" value="select * from Books where author=@id"/>
		<add key = "DeleteChild" value="delete from Books where id=@id"/>*/
        SqlConnection connection = new SqlConnection(@"Server=DESKTOP-AQ7EMHF;Database=library_database_sem4;
        Integrated Security=true;TrustServerCertificate=true;");
        private string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
        private string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
        private SqlDataAdapter sqlDataAdapter = new SqlDataAdapter();
        private List<string> paramsNames = new List<string>(ConfigurationManager.AppSettings["ColumnNamesInsertParameters"].Split(','));
        private int nr = Convert.ToInt32(ConfigurationManager.AppSettings["ChildNumberOfColumns"]);

        public Home()
        {
            InitializeComponent();
            InitializeGridViews();
            labelChild.Text = childTableName;
            labelParent.Text = parentTableName;
        }

        private void InitializeGridViews()
        {
            dataGridViewParent.SelectionChanged += new EventHandler(LoadChildren);
            string select = ConfigurationManager.AppSettings["SelectParent"];
            sqlDataAdapter.SelectCommand = new SqlCommand(select, connection);
            DataSet dataSet = new DataSet();
            sqlDataAdapter.Fill(dataSet);
            dataGridViewParent.DataSource = dataSet.Tables[0];

            buttonSterge.Enabled = false;
            buttonActualizeaza.Enabled = false;
        }

        private void LoadChildren(object sender, EventArgs e)
        {
            try
            {
                int parentId = (int)dataGridViewParent.CurrentRow.Cells[0].Value;
                string select = ConfigurationManager.AppSettings["SelectChild"];
                SqlCommand cmd = new SqlCommand(select, connection);
                cmd.Parameters.AddWithValue("@id", parentId);
                SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                DataSet dataSet = new DataSet();
                daChild.Fill(dataSet);
                dataGridViewChild.DataSource = dataSet.Tables[0];
            }catch (Exception ex) {
                DataSet dataSet = new DataSet();
                dataGridViewChild.DataSource = dataSet;
            }
        }

        private void DataGridViewCellChildrenClicked(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (dataGridViewChild.Rows[e.RowIndex] != null)
                {
                    buttonActualizeaza.Enabled = true;
                    buttonSterge.Enabled = true;
                    buttonAdauga.Enabled = false;
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void ButtonAdauga_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewParent.CurrentCell != null)
                {
                    int index = dataGridViewParent.CurrentCell.RowIndex;
                    string idSelectedParent = dataGridViewParent.Rows[index].Cells["id"].FormattedValue.ToString();
                    Form formAdaugare= new FormAdaugare(idSelectedParent);
                    formAdaugare.ShowDialog();
                    LoadChildren(null, null);
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }

        }

        private void ButtonSterge_Click(object sender, EventArgs e)
        {
            try
            {
                int index = dataGridViewChild.CurrentCell.RowIndex;
                string childId = dataGridViewChild.Rows[index].Cells["id"].FormattedValue.ToString();
                DialogResult dialogResult = MessageBox.Show("Sigur doriti sa stergeti inregistrarea cu id " + childId + "?", "Confirmare stergere", MessageBoxButtons.OKCancel);
                if (dialogResult == DialogResult.OK)
                {
                    string delete = ConfigurationManager.AppSettings["DeleteChild"];
                    SqlCommand cmd = new SqlCommand(delete, connection);
                    cmd.Parameters.AddWithValue("@id", childId);
                    SqlDataAdapter daChild = new SqlDataAdapter(cmd);
                    DataSet dataSet = new DataSet();
                    connection.Open();
                    cmd.ExecuteNonQuery();
                    LoadChildren(null, null);
                    connection.Close();
                    MessageBox.Show("Succes!", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            } catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ButtonActualizeaza_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataGridViewChild.CurrentCell != null)
                {
                    int childIndex = dataGridViewChild.CurrentCell.RowIndex;
                    string confirmare = "Doriti sa schimbati linia selectata in:\n";
                    for (int i = 0; i < nr; i++)
                    {
                        confirmare = confirmare + paramsNames[i] + ": " + dataGridViewChild.Rows[childIndex].Cells[i + 1].Value + "\n";
                    }
                    DialogResult dialogResult = MessageBox.Show(confirmare, "Confirmare actualizare", MessageBoxButtons.OKCancel);
                    if (dialogResult == DialogResult.OK)
                    {
                        string update = ConfigurationManager.AppSettings["UpdateQuery"];
                        SqlCommand cmd = new SqlCommand(update, connection);
                        for (int i = 0; i < nr; i++)
                        {
                            cmd.Parameters.AddWithValue(paramsNames[i], dataGridViewChild.Rows[childIndex].Cells[i + 1].Value);
                        }
                        cmd.Parameters.AddWithValue("@id", (int)dataGridViewChild.Rows[childIndex].Cells[0].Value);
                        connection.Open();
                        cmd.ExecuteNonQuery();
                        connection.Close();

                        MessageBox.Show("Succes!", "Notificare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        LoadChildren(null, null);
                    }
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message, "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Error);
                connection.Close();
            }
        }

        private void DataGridViewCellClickedParent(object sender, DataGridViewCellEventArgs e)
        {
            buttonAdauga.Enabled = true;
            buttonActualizeaza.Enabled = false;
            buttonSterge.Enabled = false;
        }
    }
}
