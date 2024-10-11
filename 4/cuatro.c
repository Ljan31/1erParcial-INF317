#include <stdio.h>

void piIterativo(int n, float *pi) {
    *pi = 0.0;
    for (int i = 0; i < n; i++) {
        *pi += (4.0 * ((i % 2 == 0) ? 1 : -1)) / (2 * i + 1);
    }
}

void piRecursivo(int n, float *pi, int i) {
    if (i < n) {
        *pi += (4.0 * ((i % 2 == 0) ? 1 : -1)) / (2 * i + 1);
        piRecursivo(n, pi, i + 1);
    }
}

void main() {
    int n;
    float pi;
    float piR;

    printf("Introduzca n para calcular π: ");
    scanf("%d", &n);

    piIterativo(n, &pi);
    printf("π (iterativo): %.10f\n", pi);

    piRecursivo(n, &piR, 0);
    printf("π (recursivo): %.10f\n", piR);

}