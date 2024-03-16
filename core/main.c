#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "file_io.h"
#include "compression.h"

void print_usage()
{
    printf("Uso: make run INPUT=<nome do arquivo com extensão>\n");
}

int main(int argc, char *argv[])
{
    printf("%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("[%d] %s\n", i, argv[i]);
    }

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

    // Como de acordo com as especificações do projeto o arquivo comprimido deve ter um header fixo,
    // não podemos armazenar o tipo de arquivo original para posterior descompressão
    // Assim sendo, precisamos verificar se a última extensão do arquivo é .huff

    FILE *input_file = open_file(concat_strings("./inputs/", argv[1]), "rb");

    char *input_filename = extract_filename(argv[1]);
    printf("Nome do arquivo: %s\n", input_filename);

    char *extension = extract_extension(argv[1]);
    printf("Extensão: %s\n", extension);

    if (strcmp(extension, ".huff") == 0)
    {
        char *output_path = concat_strings("./inputs/", input_filename);
        printf("🫸   🫷 Descomprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, extension), output_path);
        decompress(input_file, output_path);
    }
    else
    {
        char *output_path = concat_strings(concat_strings("./inputs/", argv[1]), ".huff");
        printf("🤏 Comprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, extension), output_path);
        compress(input_file, output_path);
    }

    close_file(input_file); // O arquivo de output é fechado dentro das funções de compressão e descompressão

    return 0;
}