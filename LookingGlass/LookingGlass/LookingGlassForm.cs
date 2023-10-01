using System.Drawing;
using System.Windows.Forms;

namespace LookingGlass
{
    public partial class LookingGlassForm : Form
    {
        private const int DEFAULT_WIDTH = 1920;
        private const int DEFAULT_HEIGHT = 1080;

        private bool IsTransparent = true;

        public LookingGlassForm()
        {
            InitializeComponent();

            // Add the window borders to the overall size of the app
            // The viewBox is set to fill the space.
            int widthDelta = DEFAULT_WIDTH - this.viewBox.Width;
            int heightDelta = DEFAULT_HEIGHT - this.viewBox.Height;
            this.Width += widthDelta;
            this.Height += heightDelta;

            SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            this.BackColor = Color.Transparent;
            this.TransparencyKey = Color.Transparent;
            this.viewBox.Visible = false;
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            if (!IsTransparent)
            {
                base.OnPaintBackground(e);
            }
        }
    }
}
