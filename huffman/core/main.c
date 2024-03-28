#include "file_io.h"
#include "utils.h"

#include "main.h"

void print_usage()
{
    printf("Uso: make run FILE=<nome do arquivo com extensão>\n");
}

/**
 * Função principal do programa.
 *
 * Esta função é responsável por iniciar a execução do programa.
 * Ela recebe os argumentos da linha de comando e retorna um valor inteiro.
 *
 * @param argc O número de argumentos da linha de comando.
 * @param argv Um array de strings contendo os argumentos da linha de comando.
 * @return Um valor inteiro representando o status de saída do programa.
 */
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

    // argv[0] contém o nome do programa
    // argv[1] contém o nome do arquivo que o usuário deseja comprimir
    // printf("%s\n", concat_strings("./input/", argv[1]));

    // Como de acordo com as especificações do projeto o arquivo comprimido deve ter um header fixo,
    // não podemos armazenar o tipo de arquivo original nele para posterior descompressão
    // Assim sendo, precisamos verificar se a última extensão do arquivo é .huff

    FILE *input_file = open_file(concat_strings("./input/", argv[1]), "rb");

    char *input_filename = extract_filename(argv[1]);
    // printf("Nome do arquivo: %s\n", input_filename);

    char *extension = extract_extension(argv[1]);
    // printf("Extensão: %s\n", extension);

    create_directory("./output"); // Criamos a pasta outputs caso ela não exista

    if (strcmp(extension, ".huff") == 0)
    {
        char *output_path = concat_strings("./output/", input_filename);

        printf("🫸   🫷 Descomprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, extension), output_path);
        decompress(input_file, output_path);
        printf("✅ Arquivo descompactado com sucesso!\n");
    }
    else
    {
        char *output_path = concat_strings(concat_strings("./output/", argv[1]), ".huff");
        printf("🤏 Comprimindo arquivo `%s` para `%s`...\n\n", concat_strings(input_filename, extension), output_path);
        compress(input_file, output_path);
        printf("✅ Arquivo compactado com sucesso!\n");
    }

    close_file(input_file); // O arquivo de output é fechado dentro das funções de compressão e descompressão

    return 0;
}