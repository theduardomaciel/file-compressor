#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSSIBLE_BYTE_VALUE 256

int *new_frequency_table(const char *data)
{
    // Utilizamos o calloc para garantir que todos os valores da tabela sejam inicializados com 0
    int *freq = calloc(sizeof(int), MAX_POSSIBLE_BYTE_VALUE);

    for (int i = 0; i < strlen((char *)data); i++)
    {
        freq[(unsigned char)data[i]]++;
    }

    return freq;
}