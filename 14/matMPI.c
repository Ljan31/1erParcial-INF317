#include <stdio.h>
#include <mpi.h>

#define MAX 3 // Tamaño de las matrices (4x4)

void main(int argc, char **argv) {
    int procesador, cantidad;
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};
    int i, j, k;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    if (procesador == 0) {
        // Inicializar matrices A y B
        for (i = 0; i < MAX; i++) {
            for (j = 0; j < MAX; j++) {
                A[i][j] = (i * MAX + j) * 2 + 1; // Para A: números impares
                B[i][j] = (i * MAX + j) * 2;       // Para B: números pares
            }
        }

        // Enviar filas de la matriz A a los otros procesos
        for (i = 1; i < cantidad && i < MAX; i++) {
            MPI_Send(A[i], MAX, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else if (procesador < MAX) {
        // Recibir filas de la matriz A
        MPI_Recv(A[procesador], MAX, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Enviar matriz B a todos los procesos
    MPI_Bcast(B, MAX * MAX, MPI_INT, 0, MPI_COMM_WORLD);

    // Multiplicar matriz A (fila recibida) por matriz B
    int temp[MAX] = {0}; // Almacena el resultado temporal
    if (procesador < MAX) {
        for (j = 0; j < MAX; j++) {
            for (k = 0; k < MAX; k++) {
                temp[j] += A[procesador][k] * B[k][j];
            }
        }

        // Enviar resultado de vuelta al proceso 0
        MPI_Send(temp, MAX, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Recoger los resultados en el proceso 0
    if (procesador == 0) {
        // Almacenar resultados de la primera fila
        for (j = 0; j < MAX; j++) {
            C[0][j] = temp[j]; // Resultados de la primera fila
        }

        // Recibir resultados de otros procesos
        for (i = 1; i < cantidad && i < MAX; i++) {
            MPI_Recv(C[i], MAX, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        // Imprimir la matriz resultante
        printf("Resultado de la multiplicación de matrices:\n");
        for (i = 0; i < MAX; i++) {
            for (j = 0; j < MAX; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
}
