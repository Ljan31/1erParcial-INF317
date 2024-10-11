#include <stdio.h>
void suma(float a, float b, float *c) {
    *c = a + b;
}

void resta(float a, float b, float *c) {
    *c = a - b;
}

void multiplicacion(float a, float b, float *c) {
    *c =  a * b;
}

void division(float a, float b, float *c) {
    *c =  a / b;
}

void main()
{
  float a,b, c;
  printf("Introduzca a: \n");
  scanf("%f", &a); //*%f float
  printf("Introduzca b: \n");
  scanf("%f", &b);

  suma(a, b, &c);
  printf("Suma: %.2f\n", c);
 
  resta(a, b, &c);
  printf("Resta: %.2f\n", c);
 
  multiplicacion(a, b, &c);
  printf("Multiplicacion: %.2f\n", c);
 
  division(a, b, &c);
  printf("Division: %.2f\n", c);

}
//* gcc tres.c -o tres