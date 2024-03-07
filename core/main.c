#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"

int main()
{
    // Damos possibilidade ao usuário escolher se deseja comprimir ou descomprimir
    printf("Digite 'c' para comprimir ou 'd' para descomprimir: ");

    char option;
    scanf("%c", &option);

    switch (option)
    {
    case 'c':
        compress("input.txt", "output.txt");
        break;

    case 'd':
        decompress("output.txt", "decompressed.txt");
        break;

    case 'e':
        printf("Saindo...\n");
        break;

    default:
        printf("Opção inválida\n");
        scanf("%c", &option);
        break;
    }

    return 0;
}