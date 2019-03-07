// error.h
// Řešení IJC-DU1, příklad b), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#ifndef DU1_ERROR_H
#define DU1_ERROR_H

#include <stdnoreturn.h>

/**
 * Tisknou text "CHYBA: " a potom
 * chybové hlášení podle formátu fmt. Vše se tiskne do stderr
 * (funkcí vfprintf).
 * 
 * @param fmt Text k vytištění na stderr
 * @param ... Parametry k textu k vytíštění
 */
void warning_msg(const char *fmt, ...);

/**
 * Tiskne text "CHYBA: " a potom
 * chybové hlášení podle formátu fmt. Vše se tiskne do stderr
 * (funkcí vfprintf) a potom ukončí program voláním
 * funkce exit(1).
 * 
 * @param fmt Text k vytištění na stderr
 * @param ... Parametry k textu k vytíštění
 */
noreturn void error_exit(const char *fmt, ...);

#endif // DU1_ERROR_H
