#include <stdio.h>
#include <string.h>

char *concat_strings(const char *s1, const char *s2)
{
    char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1); // +1 para o terminador nulo (null terminator - '\0')

    strcpy(result, s1); // copia s1 para result
    strcat(result, s2); // concatena s2 para result

    return result;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}