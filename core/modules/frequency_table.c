#include <stdio.h>
#include <stdlib.h>

#define MAX_POSSIBLE_BYTE_VALUE 256

static unsigned *frequency_table(const unsigned char *string)
{
    // Utilizamos o calloc para garantir que todos os valores da tabela sejam inicializados com 0
    unsigned *freq = calloc(sizeof(unsigned), MAX_POSSIBLE_BYTE_VALUE);

    for (int i = 0; string[i] != '\0'; i++)
    {
        freq[string[i]]++;
    }

    return freq;
}