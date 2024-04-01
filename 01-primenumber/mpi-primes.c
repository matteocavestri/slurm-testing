#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    int world_rank, world_size, n = 1000000000;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Get_processor_name(processor_name, &name_len);

    double start_time = MPI_Wtime();

    int local_count = 0, global_count;
    int range = n / world_size;
    int start = world_rank * range + 1;
    int end = (world_rank + 1) * range;

    if (world_rank == world_size - 1) {
        end = n;
    }

    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            local_count++;
        }
    }

    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (world_rank == 0) {
        printf("Total prime numbers up to %d: %d\n", n, global_count);
        printf("Computation time: %f seconds\n", end_time - start_time);
    } else {
        printf("Process %d on processor %s finished in %f seconds.\n", world_rank, processor_name, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}

