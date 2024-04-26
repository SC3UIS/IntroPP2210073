#!/bin/bash
#SBATCH --job-name=PostmanSort
#SBATCH --ntasks=128
#SBATCH --nodes=1
#SBATCH --cpus-per-task=1
#SBATCH --output=output_mpi_postmansort.txt
#SBATCH -w ExaDELL

module load openmpi/5.0.1

make clean
make all

mpirun -n 128 mpi_postmansort
