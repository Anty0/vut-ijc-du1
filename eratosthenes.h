// eratosthenes.h
// Řešení IJC-DU1, příklad a), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#ifndef DU1_ERATOSTHENES_H
#define DU1_ERATOSTHENES_H

#include "bit_array.h"

/**
 * Používá algoritmus známý jako Eratostenovo síto k nalezení prvočísel
 * 
 * @param array Array do kterého budou zaznamenána prvočísla
 */
void Eratosthenes(bit_array_t *array);

#endif // DU1_ERATOSTHENES_H
