#!/bin/bash

#SBATCH -p normal
#SBATCH --ntasks=4
#SBATCH --output=output_binarySearch_MPI.txt
#SBATCH --error=error_%j.txt
#SBATCH --cpus-per-task=1
#SBATCH -w guane10

module load devtools/mpi/openmpi/4.1.2

mpicc mpi_binarySearch.c -o mpi_binarySearch
mpirun ./mpi_binarySearch
