namespace LookingGlass
{
    partial class LookingGlassForm
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
            this.viewBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.viewBox)).BeginInit();
            this.SuspendLayout();
            // 
            // viewBox
            // 
            this.viewBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.viewBox.Enabled = false;
            this.viewBox.Location = new System.Drawing.Point(0, 0);
            this.viewBox.Name = "viewBox";
            this.viewBox.Size = new System.Drawing.Size(1904, 1041);
            this.viewBox.TabIndex = 0;
            this.viewBox.TabStop = false;
            // 
            // LookingGlassForm
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(1904, 1041);
            this.Controls.Add(this.viewBox);
            this.Name = "LookingGlassForm";
            this.Opacity = 0.5D;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "LookingGlass";
            this.TopMost = true;
            this.TransparencyKey = System.Drawing.Color.Transparent;
            ((System.ComponentModel.ISupportInitialize)(this.viewBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox viewBox;
    }
}

