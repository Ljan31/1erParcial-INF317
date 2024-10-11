using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DeteccionBordes
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "Archivos png|*.png|Archivos jpg|*.jpg";
            openFileDialog1.ShowDialog();
            Bitmap bmp = new Bitmap(openFileDialog1.FileName);
            pictureBox1.Image = bmp;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Bitmap bmp = new Bitmap(pictureBox1.Image);
            Bitmap bmp2 = new Bitmap(bmp.Width, bmp.Height); // Imagen resultante

            // Matrices de los operadores de Sobel
            int[,] gx = {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

                    int[,] gy = {
                { 1, 2, 1 },
                { 0, 0, 0 },
                { -1, -2, -1 }
            };

            // Recorrer cada pixel de la imagen
            for (int i = 1; i < bmp.Width - 1; i++)
            {
                for (int j = 1; j < bmp.Height - 1; j++)
                {
                    // Variables para los gradientes
                    int sumX = 0;
                    int sumY = 0;

                    // Aplicar el operador de Sobel
                    for (int k = -1; k <= 1; k++)
                    {
                        for (int l = -1; l <= 1; l++)
                        {
                            Color c = bmp.GetPixel(i + k, j + l);
                            int gray = (c.R + c.G + c.B) / 3; // Convertir a escala de grises
                            sumX += gray * gx[k + 1, l + 1];
                            sumY += gray * gy[k + 1, l + 1];
                        }
                    }

                    // Calcular la magnitud del gradiente
                    int magnitude = (int)Math.Sqrt(sumX * sumX + sumY * sumY);
                    magnitude = Math.Min(255, magnitude); // Asegurarse de que no supere 255

                    // Asignar el valor al nuevo bitmap
                    bmp2.SetPixel(i, j, Color.FromArgb(magnitude, magnitude, magnitude));
                }
            }

            // Mostrar la imagen resultante
            pictureBox2.Image = bmp2;
        }
    }
}
