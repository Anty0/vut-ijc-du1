// ppm.c
// Řešení IJC-DU1, příklad b), 9.3.2019
// Autor: Jiří Kuchyňka, xkuchy02, FIT
// Přeloženo: gcc (GCC) 8.2.1 20181127

#include "ppm.h"

#include "error.h"

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFO_LINE_LEN_LIMIT 100

FILE *openFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        warning_msg("Failed to open file '%s'", filename);
        return NULL;
    }
    return file;
}

bool readLine(const char *filename, FILE *file, char *line)
{
    if (fgets(line, INFO_LINE_LEN_LIMIT, file) == NULL)
    {
        if (ferror(file))
        {
            warning_msg("Unexpected IO error while reading file '%s'", filename);
        }
        else
        {
            warning_msg("Unexpected EOF while reading file '%s'", filename);
        }

        return false;
    }

    size_t len = strlen(line);

    // remove new line character
    if (line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
        //len--;
    }
    else
    {
        int ch;
        while ((ch = getc(file) != EOF && ch != '\n'))
            ; // find new line character, ignore everything else
    }
    // else
    // {
    //     // no newline == last line => missing data
    //     warning_msg("Unexpected EOF while reading file '%s'", filename);
    //     fclose(file);
    //     return false;
    // }
    return true;
}

char *trimLine(char *line)
{
    char *end;

    while (isspace(*line))
        line++;

    if (*line == '\0') // Spaces only
        return line;

    end = line + strlen(line) - 1;
    while (end > line && isspace(*end))
        end--;

    end[1] = '\0';

    return line;
}

bool strToUI(char *str, unsigned *ret)
{
    char *tmpPtr;
    for (tmpPtr = str; *tmpPtr != '\0'; tmpPtr++) {
        if (!isdigit(*tmpPtr))
        {
            return false;
        }
    }

    unsigned long n = strtoul(str, &tmpPtr, 10);

    if (*tmpPtr != '\0' || n > UINT_MAX)
    {
        return false;
    }

    *ret = (unsigned) n;
    return true;
}

bool strEq(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0;
}

bool nextLine(const char *filename, FILE *file, char *line, char **lineTrimmed)
{
    if (!readLine(filename, file, line))
    {
        fclose(file);
        return false;
    }

    *lineTrimmed = trimLine(line);
    return true;
}

struct ppm *ppm_read(const char *filename)
{
    FILE *file = openFile(filename);
    if (file == NULL)
        return NULL;

    char line[INFO_LINE_LEN_LIMIT] = {'\0'};
    char *lineTrimmed = NULL;

    // Format:
    //
    // "P6" <ws>+
    // <xsizetxt> <ws>+ <ysizetxt> <ws>+
    // "255" <ws>
    // <binární data, 3*xsize*ysize bajtů RGB>
    // <EOF>

    { // Check header
        if (!nextLine(filename, file, line, &lineTrimmed))
            return NULL;

        if (!strEq(lineTrimmed, "P6"))
        {
            warning_msg("Unsupporetd file format '%s'", filename);

            fclose(file);
            return NULL;
        }
    }

    unsigned sizeX, sizeY;
    { // Read size
        if (!nextLine(filename, file, line, &lineTrimmed))
            return NULL;

        char *sizeXStr, *sizeYStr;
        { // Load size
            sizeXStr = strtok(lineTrimmed, " ");

            sizeYStr = strtok(NULL, " ");
            while (sizeYStr != NULL && sizeYStr[0] == '\0') // Skip tailing white spaces
            {
                sizeYStr = strtok(NULL, " ");
            }

            if (sizeXStr == NULL || sizeYStr == NULL)
            {
                warning_msg("Failed to read file info '%s': Invalid size description", filename);

                fclose(file);
                return NULL;
            }
        }

        { // Search for tailing content after size description
            char *tmp = strtok(NULL, " ");
            while (tmp != NULL && tmp[0] == '\0')
            {
                tmp = strtok(NULL, " ");
            }

            if (tmp != NULL)
            {
                warning_msg("Failed to read file info '%s': Tailing content after size description", filename);

                fclose(file);
                return NULL;
            }
        }

        { // Parse size
            if (!strToUI(sizeXStr, &sizeX))
            {
                warning_msg("Failed to read file info '%s': Invalid character in sizeX description", filename);

                fclose(file);
                return NULL;
            }

            if (!strToUI(sizeYStr, &sizeY))
            {
                warning_msg("Failed to read file info '%s': Invalid character in sizeY description", filename);

                fclose(file);
                return NULL;
            }
        }
    } // End read size

    { // Check pixel size
        if (!nextLine(filename, file, line, &lineTrimmed))
            return NULL;

        if (!strEq(lineTrimmed, "255"))
        {
            warning_msg("Unsupporetd pixel size '%s'", filename);

            fclose(file);
            return NULL;
        }
    }

    unsigned long dataLen = sizeX * sizeY * 3;
    struct ppm *result = malloc(sizeof(struct ppm) + sizeof(char) * dataLen);
    if (result == NULL)
    {
        warning_msg("Failed to allocate memory for data of '%s'", filename);

        fclose(file);
        return NULL;
    }

    result->xsize = sizeX;
    result->ysize = sizeY;

    { // Read data
        unsigned long dataDone = 0;
        int ch;
        while ((ch = getc(file)) != EOF)
        {
            if (dataDone >= dataLen)
            {
                warning_msg("Failed to read file data '%s': More data then specified in header", filename);

                fclose(file);
                free(result);
                return NULL;
            }
            result->data[dataDone] = ch;
            dataDone++;
        }

        if (dataDone != dataLen)
        {
            warning_msg("Failed to read file data '%s': Less data then specified in header", filename);

            fclose(file);
            free(result);
            return NULL;
        }
    }

    return result;
} // End ppm_read

void ppm_free(struct ppm *p)
{
    free(p);
}
