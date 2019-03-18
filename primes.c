// primes.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "bit_array.h"
#include "eratosthenes.h"

#include <stdio.h>
#include <stdlib.h>

#define PRIMES_SIZE 123000001 // 0 - 123000000

void printPrimes(bit_array_t *array)
{
    unsigned long size = bit_array_size(array);

    unsigned count = 0;
    unsigned long start;
    for (start = size - 1; start >= 2; start--)
    {
        if (!bit_array_getbit(array, start) && ++count >= 10)
        {
            break;
        }
    }

    for (unsigned long i = start; i < size; i++)
    {
        if (!bit_array_getbit(array, i))
        {
            printf("%lu\n", i);
        }
    }
}

int main(/*const int argc, const char **argv*/)
{
#ifdef USE_ALLOC

    bit_array_alloc(array, PRIMES_SIZE);

#else // USE_ALLOC

    bit_array_create(array, PRIMES_SIZE);

#endif // USE_ALLOC

    Eratosthenes(array);
    printPrimes(array);

#ifdef USE_ALLOC

    bit_array_free(array);

#endif // USE_ALLOC

    return EXIT_SUCCESS;
}
