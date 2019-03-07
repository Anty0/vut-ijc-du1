// eratosthenes.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "eratosthenes.h"

#include "bit_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Eratosthenes(bit_array_t *array)
{
    unsigned long size = bit_array_size(array);
    unsigned long end = (unsigned long)sqrtl(size);

    bit_array_setbit(array, 0, 1);
    bit_array_setbit(array, 1, 1);

    for (unsigned long i = 2; i < end; i++)
    {
        if (!bit_array_getbit(array, i))
        {
            for (unsigned long j = i + i; j < size; j += i)
            {
                bit_array_setbit(array, j, 1);
            }
        }
    }
}
