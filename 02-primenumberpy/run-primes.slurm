#!/bin/bash
#SBATCH --job-name=prime-numbers-py
#SBATCH --output=output-primes.out
#SBATCH --ntasks=2
#SBATCH --time=15:00:00
#SBATCH --error=error-mpi.err   # File di errori

# Carica il virtual environment
source venv/bin/activate

# Avvia il programma MPI
mpirun python3 mpi-primes.py

