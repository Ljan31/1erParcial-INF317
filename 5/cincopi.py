import multiprocessing as mp

def calcular_pi_parcial(inicio, fin):
    suma = 0.0
    for i in range(inicio, fin):
        suma += (-1) ** i / (2 * i + 1)
    return suma

if __name__ == "__main__":
    n = 1000000  # Número de términos
    num_procesos = 3  # Número de procesos
    rango = n // num_procesos  # Rango de términos por proceso

    print("Iniciando el cálculo de π...")
    print(f"Número de términos: {n}")
    print(f"Número de procesos: {num_procesos}")

    # Usar un Pool para manejar los procesos
    with mp.Pool(processes=num_procesos) as pool:
        # Crear tareas para cada proceso
        tareas = [pool.apply_async(calcular_pi_parcial, (i * rango, (i + 1) * rango)) for i in range(num_procesos)]
        
        # Obtener los resultados
        resultados = [tarea.get() for tarea in tareas]

    # Calcular el valor final de π
    pi = sum(resultados) * 4

    # Mostrar el resultado
    print(f"Valor aproximado de π: {pi:.15f}")