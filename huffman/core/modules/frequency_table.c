#include "frequency_table.h"
#include "utils.h"

uint64_t *build_frequency_table(FILE *input)
{
    // Utilizamos o calloc para garantir que todos os valores da tabela sejam inicializados com 0
    // Uma alternativa seria criar um array de 256 posições da seguinte forma: uint64_t frequency_table[256] = {0};
    uint64_t *frequency_table = calloc(MAX_SIZE, sizeof(uint64_t));
    NULL_POINTER_CHECK(frequency_table);

    // Percorremos o arquivo byte a byte e incrementamos a frequência do byte atual
    // A função fread retorna a quantidade de elementos lidos com sucesso
    // Como nosso terceiro argumento (nmemb) é 1, a função retorna 1 se um byte foi lido com sucesso e 0 se não houver mais bytes para ler
    uint8_t current_byte;
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

int compare(const void *d1, const void *d2)
{
    huffman_node *n1 = (huffman_node *)d1;
    huffman_node *n2 = (huffman_node *)d2;

    if (n1->frequency == n2->frequency)
    {
        return 1; // não pode ser 0 pois causa ambiguidade
    }
    else if (n1->frequency > n2->frequency) // cuidado com esse sinal! não inverta!
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

priority_queue *build_frequency_queue(uint64_t *frequency_table)
{
    NULL_POINTER_CHECK(frequency_table);

    priority_queue *queue = init_priority_queue(MAX_SIZE, compare);

    // Adiciona todos os bytes que aparecem no arquivo (têm frequência maior que 0) na fila de prioridade
    for (uint64_t i = 0; i < MAX_SIZE; i++)
    {
        uint64_t current_frequency = frequency_table[i];

        if (current_frequency > 0)
        {
            uint8_t *data = malloc(sizeof(uint8_t));
            NULL_POINTER_CHECK(data);

            *data = i;

            // printf("Enfileirando %d (%ul)\n", i, current_frequency);
            pq_enqueue(queue, ht_create_node(data, current_frequency, NULL, NULL));
        }
    }
    // pq_print(queue);

    return queue;
}