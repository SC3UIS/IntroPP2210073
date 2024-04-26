#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> // Se incluye la biblioteca OpenMP

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main()
{
        const int n = 100000;
        int key, i;
        int list[n];
        double start, end;

        srand(time(0));
        for(i = 0; i < n; i++)
        {
            list[i] = rand() % 1000; // Genera números aleatorios entre 0 y 999
        }

        start = omp_get_wtime(); // Se inicia el temporizador con OpenMP
        bubble_sort(list, n); // Se ordena la lista
        end = omp_get_wtime(); // Se detiene el temporizador con OpenMP
        printf("Tiempo tomado para ordenar la lista: %lf seconds\n", end - start);

        printf("Enter key to search: ");
        scanf("%d", &key);

        start = omp_get_wtime(); // Se inicia el temporizador con OpenMP
        binary_search(list, 0, n - 1, key); // Se realiza la búsqueda binaria en la lista ordenada
        end = omp_get_wtime(); // Se detiene el temporizador con OpenMP
        printf("Tiempo tomado para buscar en lista ordenada: %lf seconds\n", end - start);

        return 0;
}

void bubble_sort(int list[], int size)
{
        int temp, i, j;
        #pragma omp parallel for private(temp, j) // Se paraleliza el bucle externo
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

void binary_search(int list[], int lo, int hi, int key)
{
        int mid;

        if (lo > hi)
        {
                printf("Key not found\n");
                return;
        }
        mid = (lo + hi) / 2;
        if (list[mid] == key)
        {
                printf("Key found\n");
        }
        else if (list[mid] > key)
        {
                binary_search(list, lo, mid - 1, key);
        }
        else if (list[mid] < key)
        {
                binary_search(list, mid + 1, hi, key);
        }
}
