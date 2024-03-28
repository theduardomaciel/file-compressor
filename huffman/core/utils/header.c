#include "header.h"

/*
    De acordo com as especificações do projeto:

    BYTE 1 e 2:
    Os 3 primeiros bits são reservados para o tamanho do lixo
    -   O tamanho do lixo é um valor entre 0 e 7, que indica quantos bits do último byte do arquivo compactado não são relevantes

    Os 13 bits restantes são reservados para o armazenamento da árvore de Huffman
    -   A árvore de Huffman é armazenada em pré-ordem

    BYTE 3 (após a árvore em pré-ordem):
    Os 3 primeiros bits são reservados para o tamanho do nome da extensão do arquivo original
    -   O maior valor possível para o tamanho do nome da extensão é 6, isto é, 110 em binário
    -   Caso o tamanho seja maior que 6, avisamos ao usuário que não é possível comprimir o arquivo

    Os outros 5 bits são lixo.

    BYTES SEGUINTES (máximo de 6 bytes):
    -   Devem ser usados para armazenar a extensão do arquivo original

    BYTES SEGUINTES (a partir do byte após a extensão):
    Os n bits seguintes são reservados para o armazenamento dos bytes comprimidos pelo algoritmo de Huffman
    -   Esses bytes são descobertos por meio da iteração do dicionário formado a partir da árvore de Huffman
*/

void header_init(FILE *file)
{
    uint16_t header = 0;
    fwrite(&header, sizeof(uint16_t), 1, file);
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

header_data *header_read(FILE *file)
{
    // 1. Lemos os 2 primeiros bytes do arquivo
    uint8_t first_byte;
    uint8_t second_byte;

    fread(&first_byte, sizeof(uint8_t), 1, file);
    fread(&second_byte, sizeof(uint8_t), 1, file);

    // 2. Extraímos o tamanho do lixo e o tamanho da árvore de Huffman
    header_data *data = malloc(sizeof(header_data));

    // Obtemos o tamanho do lixo deslocando os bits do primeiro byte para a direita (8 - 5 = 3)
    // Fazemos isso para que os 3 bits mais significativos sejam os 3 primeiros bits do byte
    data->trash_size = first_byte >> 5;

    // Para calcular o tamanho da árvore, aplicamos uma máscara ao primeiro byte
    // A máscara é 00011111 em binário, ou 0x1F em hexadecimal
    // Isso nos dá os 5 bits menos significativos do primeiro byte, ou seja, os 5 últimos bits
    // Em seguida, deslocamos esses bits para a esquerda, para que eles sejam os 5 bits mais significativos do número
    // E adicionamos os 8 bits do segundo byte, que são os 8 bits menos significativos do número, ou seja, os 8 últimos bits
    data->tree_size = (first_byte & 0x1F) << 8 | second_byte; // 0x1F = 11111

    data->tree = malloc(data->tree_size);
    fread(data->tree, sizeof(uint8_t), data->tree_size, file);

    // 3. Obtemos o tamanho do arquivo compactado
    // Para isso, movemos o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);

    // E obtemos a posição atual do cursor, que é o tamanho do arquivo em bytes
    data->file_size = ftell(file);

    // 4. Movemos o cursor de leitura para a posição correta (após o cabeçalho e a árvore de Huffman)
    fseek(file, sizeof(uint16_t) + data->tree_size, SEEK_SET);

    return data;
}