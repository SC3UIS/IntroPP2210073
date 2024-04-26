#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main(int argc, char *argv[])
{
    setenv("OMPI_MCA_btl", "^openib", 1); // Desactivar OpenIB
    setenv("OMPI_MCA_orte_base_help_aggregate", "0", 1); // Desactivar la agregación de ayuda
    // Inicialización de MPI
    MPI_Init(&argc, &argv);

    int rank, size, key, i;
    const int n = 100000;
    int list[n];
    clock_t start, end;
    double cpu_time_used;

    // Obtener el rango (identificador) del proceso y el tamaño del comunicador
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Cambiando la semilla de generación de números aleatorios para cada proceso
    srand(time(0) + rank);

    // Dividir la lista entre los procesos MPI
    int sublist_size = n / size;
    int sublist[sublist_size];

    // Distribuir la lista entre los procesos MPI
    MPI_Scatter(list, sublist_size, MPI_INT, sublist, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

    start = clock();
    bubble_sort(sublist, sublist_size);

    // Reunir las sublistas ordenadas en el proceso raíz
    int *merged_list = NULL;
    if (rank == 0)
    {
        merged_list = (int *)malloc(n * sizeof(int));
    }
    MPI_Gather(sublist, sublist_size, MPI_INT, merged_list, sublist_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Sincronizar todos los procesos antes de calcular el tiempo total
    MPI_Barrier(MPI_COMM_WORLD);

    // Solo el proceso raíz imprime el tiempo de ordenación
    if (rank == 0)
    {
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tiempo tomado para ordenar la lista: %lf seconds\n", cpu_time_used);
        
        // Proceso raíz solicita la clave de búsqueda
        //printf("Enter key to search: ");
        //scanf("%d", &key);
    }
    printf("Enter key to search: ");
    scanf("%d", &key);

    // Transmitir la clave de búsqueda a todos los procesos
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada proceso MPI realiza la búsqueda binaria en su sublista
    start = clock(); // Iniciar el temporizador
    binary_search(sublist, 0, sublist_size - 1, key);
    end = clock(); // Detener el temporizador

    // Sincronizar todos los procesos antes de calcular el tiempo total
    MPI_Barrier(MPI_COMM_WORLD);

    // Solo el proceso raíz imprime el tiempo de búsqueda
    if (rank == 0)
    {
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Tiempo tomado para buscar en lista ordenada: %lf seconds\n", cpu_time_used);
    }

    
    // Finalizar MPI
    MPI_Finalize();

    return 0;
}

// Función para ordenar una lista utilizando el algoritmo de ordenamiento de burbuja
void bubble_sort(int list[], int size)
{
    int temp, i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1 - i; j++)
        {
            if (list[j] > list[j + 1])
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

// Función para realizar la búsqueda binaria en una lista ordenada
void binary_search(int list[], int lo, int hi, int key)
{
    int mid;

    // Si lo es mayor que hi, la clave no se encuentra en la lista
    if (lo > hi)
    {
        printf("Key not found\n");
        return;
    }
    // Calcular el punto medio
    mid = (lo + hi) / 2;
    // Si la clave está en el punto medio
    if (list[mid] == key)
    {
        printf("Key found\n");
    }
    // Si la clave está en la mitad izquierda
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
    }
    // Si la clave está en la mitad derecha
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
    }
}
