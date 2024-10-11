#include <stdio.h>
float suma(float a, float b) {
    return a + b;
}

float resta(float a, float b) {
    return a - b;
}

float multiplicacion(float a, float b) {
    return a * b;
}

float division(float a, float b) {
    return a / b;
}

void main()
{
  float a,b;
  printf("Introduzca a: \n");
  scanf("%f", &a); //*%f float
  printf("Introduzca b: \n");
  scanf("%f", &b);

  printf("Suma: %.2f\n", suma(a, b));
  printf("Resta: %.2f\n", resta(a, b));
  printf("Multiplicacion: %.2f\n", multiplicacion(a, b));
  printf("Division: %.2f\n", division(a, b));

}
//* gcc dos.c -o dos