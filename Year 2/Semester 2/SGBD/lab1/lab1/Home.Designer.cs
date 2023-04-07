namespace lab1
{
    partial class Home
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
            this.dataGridViewParent = new System.Windows.Forms.DataGridView();
            this.dataGridViewChild = new System.Windows.Forms.DataGridView();
            this.labelParent = new System.Windows.Forms.Label();
            this.labelChild = new System.Windows.Forms.Label();
            this.labelMessageToUser = new System.Windows.Forms.Label();
            this.buttonAdauga = new System.Windows.Forms.Button();
            this.buttonSterge = new System.Windows.Forms.Button();
            this.buttonActualizeaza = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridViewParent
            // 
            this.dataGridViewParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewParent.Location = new System.Drawing.Point(35, 75);
            this.dataGridViewParent.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridViewParent.Name = "dataGridViewParent";
            this.dataGridViewParent.RowHeadersWidth = 51;
            this.dataGridViewParent.Size = new System.Drawing.Size(1149, 234);
            this.dataGridViewParent.TabIndex = 0;
            this.dataGridViewParent.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewCellClickedParent);
            // 
            // dataGridViewChild
            // 
            this.dataGridViewChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewChild.Location = new System.Drawing.Point(35, 414);
            this.dataGridViewChild.Margin = new System.Windows.Forms.Padding(4);
            this.dataGridViewChild.Name = "dataGridViewChild";
            this.dataGridViewChild.RowHeadersWidth = 51;
            this.dataGridViewChild.Size = new System.Drawing.Size(1533, 234);
            this.dataGridViewChild.TabIndex = 1;
            this.dataGridViewChild.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataGridViewCellChildrenClicked);
            // 
            // labelParent
            // 
            this.labelParent.AutoSize = true;
            this.labelParent.Location = new System.Drawing.Point(32, 37);
            this.labelParent.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelParent.Name = "labelParent";
            this.labelParent.Size = new System.Drawing.Size(0, 16);
            this.labelParent.TabIndex = 2;
            // 
            // labelChild
            // 
            this.labelChild.AutoSize = true;
            this.labelChild.Location = new System.Drawing.Point(32, 382);
            this.labelChild.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelChild.Name = "labelChild";
            this.labelChild.Size = new System.Drawing.Size(0, 16);
            this.labelChild.TabIndex = 3;
            // 
            // labelMessageToUser
            // 
            this.labelMessageToUser.AutoSize = true;
            this.labelMessageToUser.Location = new System.Drawing.Point(32, 523);
            this.labelMessageToUser.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelMessageToUser.Name = "labelMessageToUser";
            this.labelMessageToUser.Size = new System.Drawing.Size(0, 16);
            this.labelMessageToUser.TabIndex = 4;
            // 
            // buttonAdauga
            // 
            this.buttonAdauga.Location = new System.Drawing.Point(1313, 174);
            this.buttonAdauga.Margin = new System.Windows.Forms.Padding(4);
            this.buttonAdauga.Name = "buttonAdauga";
            this.buttonAdauga.Size = new System.Drawing.Size(256, 28);
            this.buttonAdauga.TabIndex = 5;
            this.buttonAdauga.Text = "Adauga element cu parintele selectat";
            this.buttonAdauga.UseVisualStyleBackColor = true;
            this.buttonAdauga.Click += new System.EventHandler(this.ButtonAdauga_Click);
            // 
            // buttonSterge
            // 
            this.buttonSterge.Location = new System.Drawing.Point(475, 667);
            this.buttonSterge.Margin = new System.Windows.Forms.Padding(4);
            this.buttonSterge.Name = "buttonSterge";
            this.buttonSterge.Size = new System.Drawing.Size(243, 28);
            this.buttonSterge.TabIndex = 6;
            this.buttonSterge.Text = "Sterge element selectat";
            this.buttonSterge.UseVisualStyleBackColor = true;
            this.buttonSterge.Click += new System.EventHandler(this.ButtonSterge_Click);
            // 
            // buttonActualizeaza
            // 
            this.buttonActualizeaza.Location = new System.Drawing.Point(963, 667);
            this.buttonActualizeaza.Margin = new System.Windows.Forms.Padding(4);
            this.buttonActualizeaza.Name = "buttonActualizeaza";
            this.buttonActualizeaza.Size = new System.Drawing.Size(253, 28);
            this.buttonActualizeaza.TabIndex = 7;
            this.buttonActualizeaza.Text = "Actualizeaza linie selectata";
            this.buttonActualizeaza.UseVisualStyleBackColor = true;
            this.buttonActualizeaza.Click += new System.EventHandler(this.ButtonActualizeaza_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1608, 734);
            this.Controls.Add(this.buttonActualizeaza);
            this.Controls.Add(this.buttonSterge);
            this.Controls.Add(this.buttonAdauga);
            this.Controls.Add(this.labelMessageToUser);
            this.Controls.Add(this.labelChild);
            this.Controls.Add(this.labelParent);
            this.Controls.Add(this.dataGridViewChild);
            this.Controls.Add(this.dataGridViewParent);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Biblioteca: autori si cartile lor";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridViewParent;
        private System.Windows.Forms.DataGridView dataGridViewChild;
        private System.Windows.Forms.Label labelParent;
        private System.Windows.Forms.Label labelChild;
        private System.Windows.Forms.Label labelMessageToUser;
        private System.Windows.Forms.Button buttonAdauga;
        private System.Windows.Forms.Button buttonSterge;
        private System.Windows.Forms.Button buttonActualizeaza;
    }
}

