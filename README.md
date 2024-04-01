# Slurm Testing

### Dependencies

- Slurm
- gcc/g++
- MPI (Openmpi or mpich)
- python3

### General compiling

Example for 01-primesnumber/mpi-primes.c

```bash
mpicc -o mpi-primes mpi-primes.c
```

### Run in Slurm

Example for 01-primesnumber
```bash
sbatch run-primes.slurm
```

### Run using MPI

Example for 01-primesnumber

```bash
mpirun -np 4 ./mpi-primes
```

