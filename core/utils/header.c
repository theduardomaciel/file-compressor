#include "header.h"

void header_init(FILE *file)
{
    /*
        De acordo com as especificações do projeto:

        Os 3 primeiros bits são reservados para o tamanho do lixo
        -   O tamanho do lixo é um valor entre 0 e 7, que indica quantos bits do último byte do arquivo compactado são lixo

        Os 13 bits restantes são reservados para o armazenamento da árvore de Huffman
        -   A árvore de Huffman é armazenada em pré-ordem

        Os n bits seguintes são reservados para o armazenamento dos bytes comprimidos pelo algoritmo de Huffman
        -   Esses bytes são descobertos por meio da iteração do dicionário formado a partir da árvore de Huffman
    */
    uint16_t header = 0;
    fwrite(&header, sizeof(uint16_t), 1, file);
}

void write_tree_callback(void *data, void *arg)
{
    FILE *output_file = (FILE *)arg;
    fwrite(data, sizeof(uint8_t), 1, output_file);
}

void header_write(FILE *file, header_data *data)
{
    // 1. Juntamos o tamanho do lixo e o tamanho da árvore de Huffman em um único número de 16 bits
    // Ao usar o operador OR, o resultado é um valor onde cada bit é 1 se pelo menos um dos bits correspondentes nos operandos é 1
    // ⭢ Exemplo: 1010 | 1000 = 1010

    // 2. Escrevemos o primeiro byte do header (8 bits), que contém:
    // ⭢ o tamanho do lixo (3 bits) e
    // ⭢ o tamanho da árvore de Huffman (13 bits)

    // 👋 O operador >> desloca os bits para a direita, preenchendo os bits mais significativos com 0
    // ⭢ Exemplo: 1010 >> 1 = 0101

    // 3. Escrevemos o segundo byte do header (8 bits), que contém:
    // ⭢ os 8 bits restantes do tamanho da árvore de Huffman

    // 👋 O operador & é usado para fazer uma operação AND bit a bit entre os operandos
    // ⭢ Exemplo: 1010 & 1000 = 1000

    uint16_t header = data->trash_size | data->tree_size;

    uint8_t first_byte = header >> 8;
    uint8_t second_byte = header & 0xFF; // equivalente a 255 em decimal (11111111 em binário)

    rewind(file);

    fwrite(&first_byte, sizeof(uint8_t), 1, file);
    fwrite(&second_byte, sizeof(uint8_t), 1, file);

    free(data);
}