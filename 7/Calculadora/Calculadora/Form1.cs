using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Calculadora
{
    public partial class Form1 : Form
    {
        String n;
        public Form1()
        {
            InitializeComponent();
        }

    
        private void composicion(object sender, EventArgs e)
        {
            //n = n * 10 + Convert.ToInt32( ((Button)sender).Text );

            n = n + (((Button)sender).Text);
            textBox1.Text = n;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            n = "";
            textBox1.Text = n;
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }

        private void button15_Click(object sender, EventArgs e)
        {
            ClassEvaluar ev = new ClassEvaluar();
            try
            {
                double resultado = ev.EvaluarExpresion(textBox1.Text);
                label1.Text = "Resultado: " + resultado.ToString();
            }
            catch (Exception ex)
            {
                label1.Text = "Error: " + ex.Message;
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            label1.Text = "";
            //n = "";
        }

        private void button17_Click(object sender, EventArgs e)
        {
            if (n.Length > 0) // Asegúrate de que la cadena no esté vacía
            {
                n = n.Substring(0, n.Length - 1); // Elimina el último carácter
                textBox1.Text = n; // Actualiza el TextBox con la nueva cadena
            }
        }
    }
}
