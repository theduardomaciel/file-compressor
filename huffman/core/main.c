#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "file_io.h"

#include "compress.h"
#include "decompress.h"

void print_usage()
{
    printf("Uso: make run FILE=<nome do arquivo com extensão>\n");
}

int main(int argc, char *argv[])
{
    printf("%d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("[%d] %s\n", i, argv[i]);
    }

    // Verificamos se o usuário passou os argumentos corretamente
    // Caso não, exibimos a mensagem de modo de uso e encerramos o programa

    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    // Ao executar o programa pelo makefile
    // argv[0] contém o nome do programa (por exemplo, ././build/huffman, portanto, pode ser ignorado)
    // argv[1] contém o nome do arquivo que o usuário deseja comprimir ou descomprimir (por exemplo, teste.txt)

    FILE *input_file = open_file(concat_strings("./input/", argv[1]), "rb");

    char *input_filename = extract_filename(argv[1]);
    // printf("Nome do arquivo: %s\n", input_filename);

    char *extension = extract_extension(argv[1]);
    // printf("Extensão: %s\n", extension);

    // Verificamos se o arquivo fornecido possui uma extensão válida
    if (strlen(extension) > 6)
    {
        printf("❌ Não é possível compactar arquivos do tipo fornecido!\n");
        exit(1);
    }

    create_directory("./output"); // Criamos a pasta outputs caso ela não exista

    if (strcmp(extension, "huff") == 0)
    {
        header_data *header = header_read(input_file);
        printf("Extensão original: %s\n", header->extension);

        char *output_path = concat_strings("./output/", concat_strings(input_filename, concat_strings(".", header->extension)));

        printf("🫸   🫷 Descomprimindo arquivo `%s` para `%s`...\n\n", argv[1], output_path);
        decompress(input_file, header, output_path);

        printf("✅ Arquivo descompactado com sucesso!\n");
    }
    else
    {
        char *output_path = concat_strings("./output/", concat_strings(input_filename, ".huff"));

        printf("🤏 Comprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, concat_strings(".", extension)), output_path);
        compress(input_file, extension, output_path);

        printf("✅ Arquivo compactado com sucesso!\n");
    }

    close_file(input_file); // O arquivo de output é fechado dentro das funções de compressão e descompressão

    return 0;
}