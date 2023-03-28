namespace lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridViewAutori = new System.Windows.Forms.DataGridView();
            this.dataGridViewCarti = new System.Windows.Forms.DataGridView();
            this.labelAutori = new System.Windows.Forms.Label();
            this.labelCarti = new System.Windows.Forms.Label();
            this.labelMessageToUser = new System.Windows.Forms.Label();
            this.buttonAdaugaCarte = new System.Windows.Forms.Button();
            this.buttonStergeCarte = new System.Windows.Forms.Button();
            this.buttonActualizeazaCarte = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAutori)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCarti)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewAutori
            // 
            this.dataGridViewAutori.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewAutori.Location = new System.Drawing.Point(26, 61);
            this.dataGridViewAutori.Name = "dataGridViewAutori";
            this.dataGridViewAutori.RowHeadersWidth = 51;
            this.dataGridViewAutori.Size = new System.Drawing.Size(862, 190);
            this.dataGridViewAutori.TabIndex = 0;
            this.dataGridViewAutori.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewAutoriCellClicked);
            // 
            // dataGridViewCarti
            // 
            this.dataGridViewCarti.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewCarti.Location = new System.Drawing.Point(26, 336);
            this.dataGridViewCarti.Name = "dataGridViewCarti";
            this.dataGridViewCarti.RowHeadersWidth = 51;
            this.dataGridViewCarti.Size = new System.Drawing.Size(1150, 190);
            this.dataGridViewCarti.TabIndex = 1;
            this.dataGridViewCarti.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewCellCartiClicked);
            // 
            // labelAutori
            // 
            this.labelAutori.AutoSize = true;
            this.labelAutori.Location = new System.Drawing.Point(24, 30);
            this.labelAutori.Name = "labelAutori";
            this.labelAutori.Size = new System.Drawing.Size(34, 13);
            this.labelAutori.TabIndex = 2;
            this.labelAutori.Text = "Autori";
            // 
            // labelCarti
            // 
            this.labelCarti.AutoSize = true;
            this.labelCarti.Location = new System.Drawing.Point(24, 310);
            this.labelCarti.Name = "labelCarti";
            this.labelCarti.Size = new System.Drawing.Size(28, 13);
            this.labelCarti.TabIndex = 3;
            this.labelCarti.Text = "Carti";
            // 
            // labelMessageToUser
            // 
            this.labelMessageToUser.AutoSize = true;
            this.labelMessageToUser.Location = new System.Drawing.Point(24, 425);
            this.labelMessageToUser.Name = "labelMessageToUser";
            this.labelMessageToUser.Size = new System.Drawing.Size(0, 13);
            this.labelMessageToUser.TabIndex = 4;
            // 
            // buttonAdaugaCarte
            // 
            this.buttonAdaugaCarte.Location = new System.Drawing.Point(985, 141);
            this.buttonAdaugaCarte.Name = "buttonAdaugaCarte";
            this.buttonAdaugaCarte.Size = new System.Drawing.Size(192, 23);
            this.buttonAdaugaCarte.TabIndex = 5;
            this.buttonAdaugaCarte.Text = "Adauga carte cu autorul selectat";
            this.buttonAdaugaCarte.UseVisualStyleBackColor = true;
            this.buttonAdaugaCarte.Click += new System.EventHandler(this.ButtonAdaugaCarte_Click);
            // 
            // buttonStergeCarte
            // 
            this.buttonStergeCarte.Location = new System.Drawing.Point(356, 542);
            this.buttonStergeCarte.Name = "buttonStergeCarte";
            this.buttonStergeCarte.Size = new System.Drawing.Size(182, 23);
            this.buttonStergeCarte.TabIndex = 6;
            this.buttonStergeCarte.Text = "Sterge carte selectata";
            this.buttonStergeCarte.UseVisualStyleBackColor = true;
            this.buttonStergeCarte.Click += new System.EventHandler(this.ButtonStergeCarte_Click);
            // 
            // buttonActualizeazaCarte
            // 
            this.buttonActualizeazaCarte.Location = new System.Drawing.Point(722, 542);
            this.buttonActualizeazaCarte.Name = "buttonActualizeazaCarte";
            this.buttonActualizeazaCarte.Size = new System.Drawing.Size(190, 23);
            this.buttonActualizeazaCarte.TabIndex = 7;
            this.buttonActualizeazaCarte.Text = "Actualizeaza linie(carte) selectata";
            this.buttonActualizeazaCarte.UseVisualStyleBackColor = true;
            this.buttonActualizeazaCarte.Click += new System.EventHandler(this.ButtonActualizeazaCarte_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1206, 596);
            this.Controls.Add(this.buttonActualizeazaCarte);
            this.Controls.Add(this.buttonStergeCarte);
            this.Controls.Add(this.buttonAdaugaCarte);
            this.Controls.Add(this.labelMessageToUser);
            this.Controls.Add(this.labelCarti);
            this.Controls.Add(this.labelAutori);
            this.Controls.Add(this.dataGridViewCarti);
            this.Controls.Add(this.dataGridViewAutori);
            this.Name = "Form1";
            this.Text = "Biblioteca: autori si cartile lor";
            this.Load += new System.EventHandler(this.BibliotecaFormLoad);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewAutori)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewCarti)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewAutori;
        private System.Windows.Forms.DataGridView dataGridViewCarti;
        private System.Windows.Forms.Label labelAutori;
        private System.Windows.Forms.Label labelCarti;
        private System.Windows.Forms.Label labelMessageToUser;
        private System.Windows.Forms.Button buttonAdaugaCarte;
        private System.Windows.Forms.Button buttonStergeCarte;
        private System.Windows.Forms.Button buttonActualizeazaCarte;
    }
}

