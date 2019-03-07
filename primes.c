// primes.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "bit_array.h"
#include "eratosthenes.h"

#include <stdio.h>
#include <stdlib.h>

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
    static const unsigned long size = 123000001; // 0 - 123000000

#ifdef USE_ALLOC

    bit_array_t *array;
    bit_array_alloc(&array, size);

#else // USE_ALLOC

    bit_array_t array[size / CHAR_BIT + (size % CHAR_BIT ? 1 : 0) + 1];
    bit_array_create(array, size);

#endif // USE_ALLOC

    Eratosthenes(array);
    printPrimes(array);

#ifdef USE_ALLOC

    bit_array_free(array);

#endif // USE_ALLOC

    return EXIT_SUCCESS;
}
