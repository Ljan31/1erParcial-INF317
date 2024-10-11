using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;
namespace Calculadora
{
    class ClassEvaluar
    {
        public double EvaluarExpresion(string expresion)
        {
            if (!EsValida(expresion))
                throw new ArgumentException("La expresión no es válida.");

            return Evaluar(expresion);
        }

        private bool EsValida(string expresion)
        {
            // Expresión regular para validar la cadena
            string patron = @"^\d+(\s*[\+\-\*\/]\s*\d+)*$";
            // Comprueba si la expresión contiene operadores consecutivos o está mal formada
            return Regex.IsMatch(expresion, patron);
        }

        private double Evaluar(string expresion)
        {
            Stack<double> operandos = new Stack<double>();
            Stack<char> operadores = new Stack<char>();

            for (int i = 0; i < expresion.Length; i++)
            {
                char c = expresion[i];

                if (char.IsDigit(c))
                {
                    // Leer el número completo
                    StringBuilder sb = new StringBuilder();
                    while (i < expresion.Length && char.IsDigit(expresion[i]))
                    {
                        sb.Append(expresion[i]);
                        i++;
                    }
                    i--; // Ajustar el índice después de salir del bucle
                    operandos.Push(double.Parse(sb.ToString()));
                }
                else if (c == '+' || c == '-' || c == '*' || c == '/')
                {
                    while (operadores.Count > 0 && Prioridad(c) <= Prioridad(operadores.Peek()))
                    {
                        double b = operandos.Pop();
                        double a = operandos.Pop();
                        char op = operadores.Pop();
                        operandos.Push(EjecutarOperacion(a, b, op));
                    }
                    operadores.Push(c);
                }
            }

            while (operadores.Count > 0)
            {
                double b = operandos.Pop();
                double a = operandos.Pop();
                char op = operadores.Pop();
                operandos.Push(EjecutarOperacion(a, b, op));
            }

            return operandos.Pop();
        }

        private int Prioridad(char op)
        {
            switch (op)
            {
                case '+':
                case '-':
                    return 1;
                case '*':
                case '/':
                    return 2;
                default:
                    return 0;
            }
        }

        private double EjecutarOperacion(double a, double b, char op)
        {
            switch (op)
            {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return a / b;
                default: throw new InvalidOperationException("Operador no válido.");
            }
        }
    }
}
