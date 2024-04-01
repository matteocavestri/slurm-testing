#!/bin/bash
#SBATCH --job-name=prime-numbers
#SBATCH --output=primes-output.txt
#SBATCH --ntasks=4
#SBATCH --time=10:00

mpirun ./mpi-primes

