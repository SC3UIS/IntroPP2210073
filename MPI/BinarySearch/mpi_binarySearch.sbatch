#!/bin/bash

#SBATCH -p normal
#SBATCH --ntasks=4
#SBATCH --output=output_binarySearch_MPI.txt
#SBATCH --error=error_%j.txt
#SBATCH --cpus-per-task=1
#SBATCH -w guane10

module load devtools/mpi/openmpi/4.1.2

make clean
make all

mpirun -np 4  ./mpi_binarySearch
