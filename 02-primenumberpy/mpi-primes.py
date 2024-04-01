from mpi4py import MPI
import concurrent.futures
import math
import time
import os
import resource


def is_prime(n):
    """Check if a number is prime."""
    if n <= 1:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def find_primes(start, end):
    """Find prime numbers in a given range using multithreading."""
    primes = []
    for n in range(start, end):
        if is_prime(n):
            primes.append(n)
    return primes


def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    max_number = 1000000000

    interval = (max_number // size) + 1
    start = rank * interval + 1
    end = min((rank + 1) * interval, max_number + 1)

    start_time = time.time()  # Avvio del timer

    primes = find_primes(start, end)

    all_primes = comm.gather(primes, root=0)

    if rank == 0:
        end_time = time.time()  # Fine del timer
        all_primes_flat = [prime for sublist in all_primes for prime in sublist]
        print(f"Found {len(all_primes_flat)} numbers until {max_number}.")
        print(f"Time: {end_time - start_time:.2f} seconds.")
        print(f"MPI Processors: {size}")
        print(f"MPI Version: {MPI.get_vendor()}, MPI {MPI.Get_version()}")


if __name__ == "__main__":
    main()
