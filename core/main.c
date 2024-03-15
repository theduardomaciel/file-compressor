#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "file_io.h"
#include "compression.h"

void print_usage()
{
    printf("Uso: make run INPUT=<nome do arquivo com extensão na pasta 'inputs'>\n");
}

int main(int argc, char *argv[])
{
    /* printf("%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("[%d] %s\n", i, argv[i]);
    } */

    // Verificamos se o usuário passou os argumentos corretamente
    // Caso não, exibimos a mensagem de uso e encerramos o programa

    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    // argv[0] contém o nome do programa
    // argv[1] contém o nome do arquivo que o usuário deseja comprimir
    // printf("%s\n", concat_strings("./inputs/", argv[1]));

    FILE *input_file = open_file(concat_strings("./inputs/", argv[1]), "rb");
    char *extension = strrchr(argv[1], '.');
    // printf("Extensão: %s\n", extension);

    char *input_filename = extract_filename(argv[1]);
    char *output_path = concat_strings(input_filename, ".huff");
    printf("🤏 Comprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, extension), output_path);

    if (strcmp(extension, ".huff") == 0)
    {
        //
    }
    else
    {
        compress(input_file, output_path);
    }

    close_file(input_file);
    // O arquivo de output é fechado dentro das funções de compressão e descompressão

    return 0;
}