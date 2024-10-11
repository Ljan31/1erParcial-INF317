#include <stdio.h>
#include <mpi.h>

void main(int argc, char **argv) {
    int maximo = 10, strlen = 20;
    int procesador, cantidad;
    char strings[maximo][strlen];  // Vector de cadenas
    char evenStrings[maximo][strlen];  // Cadenas en posiciones pares
    char oddStrings[maximo][strlen];   // Cadenas en posiciones impares

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &cantidad);

    if (procesador == 0) {
        // Inicializar el vector de cadenas
        for (int i = 0; i < maximo; i++) {
            snprintf(strings[i], strlen, "String %d", i);
        }

        // Enviar el vector de cadenas a los otros procesadores
        MPI_Send(strings, maximo * strlen, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Send(strings, maximo * strlen, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    } 
    // Procesador 1: despliega posiciones pares
    else if (procesador == 1) {
        MPI_Recv(strings, maximo * strlen, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        printf("Cadenas en posiciones pares:\n");
        for (int i = 0; i < maximo; i += 2) {
            printf("[procesador 1] %s\n", strings[i]);
        }
    }
    // Procesador 2: despliega posiciones impares
    else if (procesador == 2) {
        MPI_Recv(strings, maximo * strlen, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        printf("Cadenas en posiciones impares:\n");
        for (int i = 1; i < maximo; i += 2) {
            printf("[procesador 2] %s\n", strings[i]);
        }
    }

    MPI_Finalize();
}
// mpicc vecMPI.c -o vecMPI 
// mpirun -n 3 ./vecMPI