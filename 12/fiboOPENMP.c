#include <stdio.h>
#include <omp.h>

void main() {
    int n;
    printf("Ingrese n: ");
    scanf("%d", &n);
    int a = -1;
    int b = 1;
    #pragma omp parallel for shared(a,b) private(n)
      for(int i=0;i<n;i++){
        int aux = a + b;
        a = b;
        b = aux;
        printf("%d ", aux);
      }
    
      printf("\n");
}
//gcc fiboOPENMP.c -o fibo