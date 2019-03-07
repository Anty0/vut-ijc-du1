// ppm.h
// Řešení IJC-DU1, příklad b), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#ifndef DU1_PPM_H
#define DU1_PPM_H

struct ppm
{
    unsigned xsize;
    unsigned ysize;
    char data[]; // RGB bajty, celkem 3*xsize*ysize
};

/**
 * Načte obsah PPM souboru do touto funkcí dynamicky
 * alokované struktury. Při chybě formátu použije funkci warning_msg
 * a vrátí NULL.
 * 
 * @param filename Cesta k PPM souboru k načtení
 * @return V případě chyby NULL, jinak pointer na obsah načteného PPM souboru
 */
struct ppm *ppm_read(const char *filename);

/**
 * Uvolní paměť dynamicky alokovanou v ppm_read
 * 
 * @param ppm struktura vrácená z ppm_read k dealokaci
 */
void ppm_free(struct ppm *p);

#endif // DU1_PPM_H
