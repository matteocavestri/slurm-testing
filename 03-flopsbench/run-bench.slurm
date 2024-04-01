#!/bin/bash
#SBATCH --job-name=flops-bench
#SBATCH --output=output-bench.out
#SBATCH --ntasks=4
#SBATCH --time=01:00:00
#SBATCH --error=error-bench.err   # File di errori

mpirun ./flopsbench

