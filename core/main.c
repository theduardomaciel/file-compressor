#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"

int main(int argc, char *argv[])
{
    // Damos possibilidade ao usuário escolher se deseja comprimir ou descomprimir por meio de argumentos
    // Caso o usuário não escolha nenhuma das opções, o programa irá encerrar

    if (argc < 2)
    {
        printf("Usage: %s [-c | -d] <file>\n", argv[0]);
        return 1;
    }

    // Caso o usuário insira "-c" o programa irá comprimir o arquivo
    if (strcmp(argv[1], "-c") == 0)
    {
        compress(argv[2]);
    }
    // Caso o usuário insira "-d" o programa irá descomprimir o arquivo
    else if (strcmp(argv[1], "-d") == 0)
    {
        decompress(argv[2]);
    }
    else
    {
        printf("Usage: %s [-c | -d] <file>\n", argv[0]);
        return 1;
    }

    return 0;
}