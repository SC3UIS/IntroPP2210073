/*  
Purpose:

   Postman Sort is a d(n+k) complexity  sorting algorithm where d is number of digits, n number of keys and k size of the bucket.
   This algorithm is used by letter-sorting machines in post offices: mail is sorted first between domestic and international;
   then by state, province or territory. Using OpenMP Libraries is possible reduce execution-time but not always paralyze is the
   solution.  

  Example:

    18 March  2024 19:00:00 PM

  Licensing:

    This code is distributed under the GNU LGPL license.


  Author:
  Sanfoundry Global Education & Learning Series – 1000 C Programs.
  MPI Modification:
  24 April 2024 by Gian Mier, Universidad Industrial de Santander gian2210073@correo.uis.edu.co                   
  This MPI Modification makes a parallelization of the original Code...  
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

void arrange(int, int);
int array[100000], array1[100000];
int globalArraySize = 100000, localArraySize;
int *localArray, *localArray1, *globalArray, *resultArray;
int i, j, temp, chunk_size, max, count = 100000, maxdigits = 0, c = 0;
int generateRandom();

int main(int argc, char *argv[])
{
    double startTime, localTime, totalTime;
    int myid, numprocs;
    /**
     * Parallel initialization with MPI
    */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    int t1, t, n = 1;
    startTime = MPI_Wtime();
    /**
     * Root worker fills the global array with random numbers and allocates memory
    */
    if (myid == 0)
    {
        srand(time(NULL));
        /** 
         * It allocates global array and result array memory
        */
        globalArray = (int *)malloc(globalArraySize * sizeof(int));
        resultArray = (int *)malloc(globalArraySize * sizeof(int));
        for (int i = 0; i < 100000; i++)
        {

            array1[i] = generateRandom();
            array[i] = array1[i];
            globalArray[i] = array1[i];
        }

        for (i = 0; i < count; i++)
        {
            t = array[i];
            while (t > 0)
            {
                c++;
                t = t / 10;
            }
            if (maxdigits < c)
                maxdigits = c;
            c = 0;
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

            temp = globalArray[t];
            globalArray[t] = globalArray[i];
            globalArray[i] = temp;
        }
    }

    /**
     * Get worker's local array size splitting the global array size by the number of workers
    */
    localArraySize = globalArraySize / numprocs;
    localArray = (int *)malloc(localArraySize * sizeof(int));
    localArray1 = (int *)malloc(localArraySize * sizeof(int));

    /**
     * Share n to all workers from root worker
    */
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    /**
     * Assign equal chunks of the global array to each worker
    */
    MPI_Scatter(globalArray, localArraySize, MPI_INT, localArray,
                localArraySize, MPI_INT, 0, MPI_COMM_WORLD);

    /**
     * Aux local array
    */
    MPI_Scatter(globalArray, localArraySize, MPI_INT, localArray1,
                localArraySize, MPI_INT, 0, MPI_COMM_WORLD);

    while (n >= 1)
    {
        for (i = 0; i < localArraySize;)
        {
            t1 = localArray[i] / n;
            for (j = i + 1; t1 == (localArray[j] / n); j++)
                ;
            arrange(i, j);
            i = j;
        }
        n = n / 10;
    }




    /**
     * Once evety worker has sorted its part of the array, the results are gathered in the result array
    */
    MPI_Gather(localArray1, localArraySize, MPI_INT, resultArray, localArraySize, MPI_INT, 0, MPI_COMM_WORLD);


    /**
     * Free local array memory for every worker
    */
    MPI_Barrier(MPI_COMM_WORLD);
    free(localArray1);
    free(localArray);


    /**
     * Get the maximum time of all workers that is the total time of execution
    */
    localTime = MPI_Wtime() - startTime;
    MPI_Reduce(&localTime, &totalTime, 1, MPI_DOUBLE,
               MPI_MAX, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    if (myid == 0)
    {

        /**
         * Finally print taken time to sort the array and free the global and result array memory
        */
        //printf("Work took %f seconds\n", totalTime);
        //printf("\nSorted Array (Postman sort) :");
        //for (i = 0; i < count; i++)
        //printf("%d ", resultArray[i]);
        //printf("\n");
        free(globalArray);
        free(resultArray);
    }
    return 0;
}
/* Function to arrange the of sequence having same base */
void arrange(int k, int n)
{
    for (i = k; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (localArray1[i] > localArray1[j])
            {
                temp = localArray1[i];
                localArray1[i] = localArray1[j];
                localArray1[j] = temp;
                temp = (localArray[i] % 10);
                localArray[i] = (localArray[j] % 10);
                localArray[j] = temp;
            }
        }
    }
}

int generateRandom()
{
    int number = rand() % 10000;
    return number;
}
