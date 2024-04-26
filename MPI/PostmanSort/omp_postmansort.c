#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
void arrange(int, int);
int array[100000], array1[100000];
int i, j, temp, max, count = 100000, maxdigits = 0, c = 0;
int generateRandom();
double start, end;
int main()
{
    start = omp_get_wtime();
    int t1, t2, k, t, n = 1;
    // printf("Enter size of array :");
    // scanf("%d", &count);
    // printf("Enter elements into array :");
    // for (i = 0; i < count; i++)
    // {
    // scanf("%d", &array[i]);
    // array1[i] = array[i];
    // }

    srand(time(NULL));
    for (int i = 0; i < 100000; i++)
    {
        array1[i] = generateRandom();
        array[i] = array1[i];
    }

#pragma omp parallel for private(i) shared(count, maxdigits, array, array1, c)
    for (i = 0; i < count; i++)
    {
        t = array[i];
        while (t > 0)
        {
            c++;
            t = t / 10;
        }
#pragma omp critical
        {
            if (maxdigits < c)
                maxdigits = c;
            c = 0;
        }
    }
    while (--maxdigits)
        n = n * 10;
    for (i = 0; i < count; i++)
    {
        max = array[i] / n;
        t = i;
        for (j = i + 1; j < count; j++)
        {
            if (max > (array[j] / n))
            {
                max = array[j] / n;
                t = j;
            }
        }
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }
#pragma omp parallel shared(count, array, array1) private(i, j, t1)
    {
        while (n >= 1)
        {
#pragma omp for
            for (i = 0; i < count;i++)
            {
                t1 = array[i] / n;
                for (j = i + 1; t1 == (array[j] / n); j++)
                    ;
#pragma omp critical
                arrange(i, j);
                i = j;
            }
#pragma omp single
            n = n / 10;
        }
    }
    end = omp_get_wtime();
    printf("Work took %f seconds\n", end - start);
//printf("\nSorted Array (Postman sort) :");    
//for (i = 0; i < count; i++)
//printf("%d ", array1[i]);
//printf("\n");
}
/* Function to arrange the of sequence having same base */
void arrange(int k, int n)
{
    for (i = k; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (array1[i] > array1[j])
            {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = (array[i] % 10);
                array[i] = (array[j] % 10);
                array[j] = temp;
            }
        }
    }
}

int generateRandom()
{
    int number = rand() % 10000;
    return number;
}
