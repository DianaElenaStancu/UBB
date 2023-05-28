using System;
using System.Data.SqlClient;
using System.Threading;

namespace ConsoleApplication1
{
    internal class Program
    {
        
        public static void Main(string[] args)
        {
            Thread t = new Thread (T2);          
            t.Start();
            
            SqlConnection connection;
            SqlDataAdapter adapterChild = new SqlDataAdapter();

            string connectionString =
                "Server=DESKTOP-AQ7EMHF;Database=library_database_sem4;Integrated Security=true;TrustServerCertificate=true;";
            
            connection = new SqlConnection(connectionString);
            connection.Open();

            int i = 3;
            while (i > 0)
            {
                i--;
                try
                {
                    Console.WriteLine("L1: trying to execute transaction "+(3-i)+"th time...");
                    
                    SqlTransaction transaction = connection.BeginTransaction(System.Data.IsolationLevel.Serializable);
                    adapterChild.UpdateCommand = new SqlCommand("update BookDepartments set name = 'Geografie' where id = 2", connection, transaction);
                    adapterChild.UpdateCommand.ExecuteNonQuery();
                    
                    Thread.Sleep(6000);
                    
                    adapterChild.UpdateCommand = new SqlCommand("update BookSubdepartments set name = 'Geografia Romaniei' where id = 2", connection, transaction);
                    adapterChild.UpdateCommand.ExecuteNonQuery();
                    transaction.Commit();
                    
                    Console.WriteLine("L1: transaction succeeded.");
                    i = 0;
                }
                catch (SqlException e)
                {
                    Console.WriteLine("L1. Didn't succeed because of: " + e.Message);
                }
            }
        }

        public static void T2()
        {
            Thread.Sleep(3000);
            SqlConnection connection;
            SqlDataAdapter adapterChild = new SqlDataAdapter();

            string connectionString =
                "Server=DESKTOP-AQ7EMHF;Database=library_database_sem4;Integrated Security=true;TrustServerCertificate=true;";
            
            connection = new SqlConnection(connectionString);
            connection.Open();

            int i = 3;
            while (i > 0)
            {
                i--;
                try
                {
                    Console.WriteLine("L2: trying to execute transaction "+(3-i)+"th time...");
                    
                    SqlTransaction transaction = connection.BeginTransaction(System.Data.IsolationLevel.Serializable);
                    adapterChild.UpdateCommand = new SqlCommand("update BookDepartments set name = 'Geografie' where id = 2", connection, transaction);
                    adapterChild.UpdateCommand.ExecuteNonQuery();
                    
                    Thread.Sleep(6000);
                    
                    adapterChild.UpdateCommand = new SqlCommand("update BookDepartments set name = 'Geografie' where id = 2", connection, transaction);
                    adapterChild.UpdateCommand.ExecuteNonQuery();
                    transaction.Commit();
                    
                    Console.WriteLine("L2: transaction succeeded.");
                    i = 0;
                }
                catch (SqlException e)
                {
                    Console.WriteLine("L2. Didn't succeed because of: " + e.Message);
                }
            }
        }
    }
}