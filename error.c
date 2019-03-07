// error.c
// Řešení IJC-DU1, příklad b), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "error.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

void print_warning(const char *fmt, va_list args)
{
    static const char *prepend = "CHYBA: ";
    fprintf(stderr, prepend);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
}

void warning_msg(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    print_warning(fmt, args);
    va_end(args);
}

noreturn void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    print_warning(fmt, args);
    va_end(args);

    exit(1);
}
