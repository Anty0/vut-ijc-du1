// bit_array.c
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "bit_array.h"

#ifdef USE_INLINE

extern void bit_array_free(bit_array_t *array);
extern unsigned long bit_array_size(bit_array_t *array);
extern void bit_array_setbit(bit_array_t *array, unsigned long index, int newBit);
extern int bit_array_getbit(bit_array_t *array, unsigned long index);
// extern void bit_array_switchbit(bit_array_t *array, unsigned long index);

#endif // USE_INLINE