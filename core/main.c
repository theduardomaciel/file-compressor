#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"

void print_usage()
{
    printf("Uso: [compress | decompress] <nome do arquivo com extensão>\n");
}

int main(int argc, char *argv[])
{
    /* printf("%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    } */

    // Verificamos se o usuário passou os argumentos corretamente
    // Caso não, exibimos a mensagem de uso e encerramos o programa

    if (argc < 3)
    {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "compress") == 0)
    {
        compress(argv[2]);
    }
    else if (strcmp(argv[1], "-decompress") == 0)
    {
        decompress(argv[2]);
    }
    else
    {
        print_usage();
        return 1;
    }

    return 0;
}