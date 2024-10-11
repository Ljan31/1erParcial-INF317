#include <stdio.h>
#include <mpi.h>

void main(int argc, char **argv) {
    int i;
    MPI_Init(&argc, &argv);
    int maximo = 10;
    int procesador, cantidad;
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);
    int vector1[maximo], vector2[maximo], vector3[maximo];

    if (procesador == 0) {
        for (i = 0; i < maximo; i++) {
            vector1[i] = i * 2 + 1; 
            vector2[i] = i * 2; 
        }

        // Enviar vectores a los otros procesadores
        MPI_Send(vector1, maximo, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, maximo, MPI_INT, 1, 0, MPI_COMM_WORLD);
        
        MPI_Send(vector1, maximo, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(vector2, maximo, MPI_INT, 2, 0, MPI_COMM_WORLD);
    } 
    // Procesador 1: suma posiciones impares
    else if (procesador == 1) {
        MPI_Recv(vector1, maximo, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, maximo, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for (i = 1; i < maximo; i += 2) {
            vector3[i] = vector1[i] + vector2[i];
        }

        // Enviar resultados de vuelta al maestro
        MPI_Send(vector3, maximo, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    // Procesador 2: suma posiciones pares
    else if (procesador == 2) {
        MPI_Recv(vector1, maximo, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector2, maximo, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        for (i = 0; i < maximo; i += 2) {
            vector3[i] = vector1[i] + vector2[i];
        }

        // Enviar resultados de vuelta al maestro
        MPI_Send(vector3, maximo, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    // Procesador 0: recibe y muestra los resultados
    if (procesador == 0) {
        printf("Resultados de la suma:\n");
        // Recibir resultados de procesador 1
        MPI_Recv(vector3, maximo, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Suma de posiciones impares:\n");
        for (i = 0; i < maximo; i++) {
            if (i % 2 != 0) {
                printf("%d ", vector3[i]);
            }
        }
        printf("\n");

        // Recibir resultados de procesador 2
        MPI_Recv(vector3, maximo, MPI_INT, 2, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Suma de posiciones pares:\n");
        for (i = 0; i < maximo; i++) {
            if (i % 2 == 0) {
                printf("%d ", vector3[i]);
            }
        }
        printf("\n");
    }

    MPI_Finalize();
}

// mpicc 11MPI.c -o mpi
// mpirun -n 3 ./mpi