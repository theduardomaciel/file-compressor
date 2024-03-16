#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SIZE 256

uint64_t *build_frequency_table(FILE *input)
{
    // Utilizamos o calloc para garantir que todos os valores da tabela sejam inicializados com 0
    // uma alternativa seria criar um array de 256 posições da seguinte forma: uint64_t frequency_table[256] = {0};
    uint64_t *frequency_table = calloc(MAX_SIZE, sizeof(uint64_t));

    if (frequency_table == NULL)
    {
        printf("Erro ao alocar memória para a tabela de frequências\n");
        exit(1);
    }

    uint8_t current_byte;

    // Percorremos o arquivo byte a byte e incrementamos a frequência do byte atual
    // A função fread retorna a quantidade de elementos lidos com sucesso
    // Como nosso terceiro argumento (nmemb) é 1, a função retorna 1 se um byte foi lido com sucesso e 0 se não houver mais bytes para ler
    while (fread(&current_byte, sizeof(uint8_t), 1, input) == 1)
    {
        // printf("Byte lido: %d (freq. atual: %ld)\n", current_byte, frequency_table[current_byte]);
        frequency_table[current_byte]++;
    }

    // Voltamos o ponteiro do arquivo para o início
    fseek(input, 0, SEEK_SET);
    /*
        Poderíamos utilizar a função rewind(input), mas optamos por utilizar fseek para fins de aprendizado
        A função fseek recebe 3 argumentos:
            1. o ponteiro para o arquivo,
            2. o número de bytes a serem deslocados a partir da origem (offset),
            3. a partir de onde o deslocamento será adicionado (origem). Pode ser uma constante SEEK_SET, SEEK_CUR ou SEEK_END.
        -> SEEK_SET: indica o início do arquivo (0), SEEK_CUR: indica a posição atual do arquivo, SEEK_END: indica o final do arquivo
        Quando chamamos fseek com SEEK_SET como origem, nós movemos o ponteiro do arquivo para o início (posição 0).
        Como o offset (argumento 2) é 0, nenhum outro movimento é realizado.
    */

    return frequency_table;
}