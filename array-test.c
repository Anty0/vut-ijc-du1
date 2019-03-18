// array-test.c
// Řešení IJC-DU1, příklad navíc (není součásí řešení zadání), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "bit_array.h"

#include <stdio.h>
#include <stdlib.h>

#define TEST_ARRAY_SIZE 150

void printArrayContents(bit_array_t *array)
{
    unsigned long size = bit_array_size(array);

    printf("Contents: ");
    for (unsigned long i = 0; i < size; i++)
    {
        printf(bit_array_getbit(array, i) ? "1" : "0");
    }
    printf("\n");
}

void testArray(bit_array_t *array)
{
    printArrayContents(array);

    unsigned long size = bit_array_size(array);
    for (unsigned long i = 0; i < size; i++)
    {
        if (bit_array_getbit(array, i))
        {
            printf("!Get %lu -> %d\n", i, 1);
        }

        bit_array_setbit(array, i, 1);

        if (!bit_array_getbit(array, i))
        {
            printf("!Get %lu -> %d\n", i, 0);
        }

        printf("+");
        printArrayContents(array);

        bit_array_setbit(array, i, 0);

        if (bit_array_getbit(array, i))
        {
            printf("!Get (end) %lu -> %d\n", i, 1);
        }

        printf("-");
        printArrayContents(array);
    }
}

int main(/*const int argc, const char **argv*/)
{
#ifdef USE_ALLOC

    bit_array_alloc(array, TEST_ARRAY_SIZE);

#else // USE_ALLOC

    bit_array_create(array, TEST_ARRAY_SIZE);

#endif // USE_ALLOC

    testArray(array);

#ifdef USE_ALLOC

    bit_array_free(array);

#endif // USE_ALLOC

    return EXIT_SUCCESS;
}
