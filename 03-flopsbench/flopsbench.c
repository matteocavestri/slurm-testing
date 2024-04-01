#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N                                                                      \
  10000000000 // Riduci questo valore se l'esecuzione è troppo lunga su sistemi
              // più piccoli
#define OPS_PER_ITERATION 2

int main(int argc, char **argv) {
  int rank, size;
  double a = 1.0, b = 2.0, result;
  long int i, iterations_per_process;
  double start, end, local_time, total_time, flops, gflops, tflops;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  iterations_per_process = N / size;

  start = MPI_Wtime();
  for (i = 0; i < iterations_per_process; i++) {
    result = a * b + b;
    a += result; // Impedisce l'ottimizzazione del compilatore
  }
  end = MPI_Wtime();

  local_time = end - start;

  // Raccogli e calcola il tempo totale impiegato da tutti i processi
  MPI_Reduce(&local_time, &total_time, 1, MPI_DOUBLE, MPI_MAX, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    flops = (OPS_PER_ITERATION * N) / total_time;
    gflops = flops / 1e9;
    tflops = flops / 1e12;

    printf("Time spent: %f seconds\n", total_time);
    //	    printf("Calcoli eseguiti in singola precizione (32bit)\n");
    printf("FLOPS: %f\n", flops);
    printf("GFLOPS: %f\n", gflops);
    printf("TFLOPS: %f\n", tflops);
  }

  MPI_Finalize();
  return 0;
}
