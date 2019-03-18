// steg-decode.c
// Řešení IJC-DU1, příklad b), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "eratosthenes.h"
#include "bit_array.h"
#include "ppm.h"
#include "error.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv)
{
    if (argc != 2)
    {
        error_exit("Invalid argument count");
    }

    struct ppm *image = ppm_read(argv[1]);
    if (image == NULL)
    {
        error_exit("Failed to read image");
    }

    const unsigned long size = (unsigned long)image->xsize * (unsigned long)image->ysize * (unsigned long)3;

#ifdef USE_ALLOC

    bit_array_alloc(array, size);

#else // USE_ALLOC

    bit_array_dynamic_create(array, size);

#endif // USE_ALLOC

    Eratosthenes(array);

    const char charOne = 1;
    const int charLen = sizeof(char) * CHAR_BIT;

    char tmp = 0;
    uint8_t tmpPtr = 0;
    bool successfulExit = false;
    for (unsigned long i = 19; i < size; i++)
    {
        if (!bit_array_getbit(array, i))
        {
            // if (image->data[i] & 1)
            // {
            //     tmp |= charOne << tmpPtr;
            // }
            // else
            // {
            //     tmp &= ~(charOne << tmpPtr);
            // }

            if (image->data[i] & 1)
            {
                tmp ^= charOne << tmpPtr; // Switch bit -> Set it to 1
            }

            if (++tmpPtr >= charLen)
            {
                if (tmp == 0)
                {
                    successfulExit = true;
                    break;
                }

                printf("%c", tmp);
                tmpPtr = 0;
                tmp = 0;
            }
        }
    }
    printf("\n");

#ifdef USE_ALLOC

    bit_array_free(array);

#endif // USE_ALLOC

    ppm_free(image);
    image = NULL;

    if (!successfulExit)
    {
        error_exit("Image does not contain string terminator ('\\0')");
    }

    return EXIT_SUCCESS;
}
