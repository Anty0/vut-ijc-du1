// bit_array.h
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#ifndef DU1_BIT_ARRAY_H
#define DU1_BIT_ARRAY_H

#include "error.h"

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Typ bitového pole (pro předávání parametru do funkce odkazem)
 */
typedef unsigned long bit_array_t;

#define _round_to_multiply(num, multiple) ((num) % (multiple) ? (num) + (multiple) - ((num) % (multiple)) : (num))

#define _long_one ((unsigned long)1)

#define _bit_array_len(size) (_round_to_multiply((size) / CHAR_BIT + ((size) % CHAR_BIT ? 1 : 0) + sizeof(unsigned long), sizeof(unsigned long)))

#define _bit_array_num_bits (CHAR_BIT * sizeof(unsigned long))

#define _bit_array_index(index) ((index) / _bit_array_num_bits + 1)

#define _bit_array_bit_index(index) ((index) % _bit_array_num_bits)

#define _bit_array_check_index(index) (                                                                          \
    (index) >= (_bit_array_size(array))                                                                          \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", (index), _bit_array_size(array) - 1), 1) \
        : 0)

/**
 * Definuje a _nuluje_ proměnnou jmeno_pole
 * (POZOR: opravdu musí _INICIALIZOVAT_ pole bez ohledu na
 * to, zda je pole statické nebo automatické/lokální!  Vyzkoušejte si obě
 * varianty, v programu použijte lokální pole.)
 * Př: static bit_array_create(p,100); // p = pole 100 bitů, nulováno
 *     bit_array_create(q,100000L); // q = pole 100000 bitů, nulováno
 * Použijte static_assert pro kontrolu maximální možné velikosti pole.
 */
//TODO: static_assert
#define _bit_array_create(array, size)                                                                                   \
    do                                                                                                                   \
    {                                                                                                                    \
        assert(size < (SIZE_MAX - 1) * CHAR_BIT /*bit_array_create: Bit array cannot be bigger then size_t max value*/); \
        unsigned long len = _bit_array_len(size);                                                                        \
                                                                                                                         \
        memset((array), 0, len);                                                                                         \
        (array)[0] = size;                                                                                               \
    } while (0)

/**
 * Definuje proměnnou jmeno_pole tak, aby byla kompatibilní s polem
 * vytvořeným pomocí bit_array_create, ale pole bude alokováno dynamicky.
 * Př: bit_array_alloc(q,100000L); // q = pole 100000 bitů, nulováno
 * Použijte assert pro kontrolu maximální možné velikosti pole.
 * Pokud alokace selže, ukončete program s chybovým hlášením:
 * "bit_array_alloc: Chyba alokace paměti"
 */
#define _bit_array_alloc(array, size)                                                                                   \
    do                                                                                                                  \
    {                                                                                                                   \
        assert(size < (SIZE_MAX - 1) * CHAR_BIT /*bit_array_alloc: Bit array cannot be bigger then size_t max value*/); \
        unsigned long len = _bit_array_len(size);                                                                       \
                                                                                                                        \
        (*(array)) = malloc(len);                                                                                       \
        if ((*(array)) == NULL)                                                                                         \
        {                                                                                                               \
            error_exit("bit_array_alloc: Chyba alokace paměti");                                                        \
        }                                                                                                               \
                                                                                                                        \
        memset((*(array)), 0, len);                                                                                     \
        (*(array))[0] = size;                                                                                           \
    } while (0)

/**
 * Uvolní paměť dynamicky alokovaného pole
 */
#define _bit_array_free(array) \
    do                         \
    {                          \
        free(array);           \
    } while (0)

/**
 * vrátí deklarovanou velikost pole v bitech (uloženou v poli)
 */
#define _bit_array_size(array) ((array)[0])

/**
 * nastaví zadaný bit v poli na hodnotu zadanou výrazem
 * (nulový výraz == bit 0, nenulový výraz == bit 1)
 * Př: bit_array_setbit(p,20,1);
 */
#define _bit_array_setbit(array, index, newBit)                                              \
    do                                                                                       \
    {                                                                                        \
        _bit_array_check_index(index);                                                       \
        if (newBit)                                                                          \
        {                                                                                    \
            (array)[_bit_array_index(index)] |= _long_one << _bit_array_bit_index(index);    \
        }                                                                                    \
        else                                                                                 \
        {                                                                                    \
            (array)[_bit_array_index(index)] &= ~(_long_one << _bit_array_bit_index(index)); \
        }                                                                                    \
    } while (0)

/**
 * získá hodnotu zadaného bitu, vrací hodnotu 0 nebo 1
 * Př: if(bit_array_getbit(p,i)==1) printf("1");
 *     if(!bit_array_getbit(p,i))   printf("0");
 */
#define _bit_array_getbit(array, index) (                                            \
    _bit_array_check_index(index),                                                   \
    (((array)[_bit_array_index(index)] & (_long_one << _bit_array_bit_index(index))) \
         ? 1                                                                         \
         : 0))

/* #define _bit_array_switchbit(array, index)                                            \
//     do                                                                                \
//     {                                                                                 \
//         _bit_array_check_index(index);                                                \
//         (array)[_bit_array_index(index)] ^= _long_one << _bit_array_bit_index(index); \
//     } while (0)*/

#ifdef USE_INLINE

inline void bit_array_create(bit_array_t *array, unsigned long size)
{
    _bit_array_create(array, size);
}

inline void bit_array_alloc(bit_array_t **array, unsigned long size)
{
    _bit_array_alloc(array, size);
}

inline void bit_array_free(bit_array_t *array)
{
    _bit_array_free(array);
}

inline unsigned long bit_array_size(bit_array_t *array)
{
    return _bit_array_size(array);
}

inline void bit_array_setbit(bit_array_t *array, unsigned long index, int newBit)
{
    _bit_array_setbit(array, index, newBit);
}

inline int bit_array_getbit(bit_array_t *array, unsigned long index)
{
    return _bit_array_getbit(array, index);
}

// inline void bit_array_switchbit(bit_array_t *array, unsigned long index)
// {
//     _bit_array_switchbit(array, index);
// }

#else // USE_INLINE

#define bit_array_create(array, size) _bit_array_create(array, size)
#define bit_array_alloc(array, size) _bit_array_alloc(array, size)
#define bit_array_free(array) _bit_array_free(array)
#define bit_array_size(array) _bit_array_size(array)
#define bit_array_setbit(array, index, newBit) _bit_array_setbit(array, index, newBit)
#define bit_array_getbit(array, index) _bit_array_getbit(array, index)
//#define bit_array_switchbit(array, index) _bit_array_switchbit(array, index)

#endif // USE_INLINE

#endif // DU1_BIT_ARRAY_H
