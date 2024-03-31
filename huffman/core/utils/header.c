#include "header.h"

/*
    De acordo com as especificações do projeto:

    2 BYTES (16 bits):
    -   tamanho do lixo (3 bits)
            Obs.: é um valor entre 0 e 7, que indica quantos bits do último byte do arquivo compactado não são relevantes
    -   tamanho da árvore em pré-ordem (13 bits)

    N BYTES: árvore de Huffman em pré-ordem
        Obs.: O tamanho da árvore de Huffman é variável, então o número de bytes necessários para armazená-la também é variável

    1 BYTE (após a árvore em pré-ordem):
    -   tamanho do nome da extensão do arquivo original (3 bits)
            Obs.:   O maior valor possível para esse tamanho é 6, isto é, 110 em binário.
                    Ou seja, arquivos de extensões com nomes com mais de 6 caracteres não são aceitos no programa.
    -   lixo (5 bits)

    N BYTES (máximo de 6): extensão do arquivo original

    N BYTES (a partir do byte após a extensão): dados compactados
        Obs.: Esses bytes são escritos por meio da loop pelo arquivo, a partir do qual vamos escrevendo os bytes comprimidos correspondentes no arquivo comprimido.
*/

header_data *header_init()
{
    // Retornamos a struct que criamos para armazenar os dados do header com sua memória alocada
    header_data *header = malloc(sizeof(header_data));
    return header;
}

void header_reserve_space(FILE *file)
{
    // Reservamos os 2 bytes iniciais para o tamanho do lixo e o tamanho da árvore em pré-ordem
    uint16_t reserved_bytes = 0;
    fwrite(&reserved_bytes, sizeof(uint16_t), 1, file);
    // alternativa: fwrite("\0\0", sizeof(uint8_t), 2, file);
}

void header_write_to_file(FILE *file, header_data *data)
{
    /*
        Como o tamanho do lixo e o tamanho da árvore em pré-ordem são
        armazenados em 2 bytes, precisamos combiná-los em um único valor

        Para isso, utilizamos um operador OR bit a bit
        Exemplo:    10100000 00000000   (tamanho do lixo = 5)
                    00000000 00001011 | (tamanho da árvore em pré-ordem = 11)
                    -------------------
                    10100000 00001011

        Como o tamanho do lixo ocupa somente 3 primeiros bits, podemos
        realizar o OR bit a bit com o tamanho da árvore em pré-ordem,
        que ocupa os 13 bits restantes do primeiro byte do cabeçalho
    */
    uint16_t header = data->trash_size | data->tree_size;

    uint8_t first_byte = header >> 8;
    /*
        Exemplo:    10100000 00001011 >> 8
                    00000000 10100000

        Obtemos o byte 10100000, que é o primeiro byte do cabeçalho
    */

    uint8_t second_byte = header & 11111111;
    /*
        Exemplo:    10100000 00001011
                    00000000 11111111 &
                    -------------------
                    00000000 00001011

        Obtemos somente os 8 últimos do valor, que é o segundo byte do cabeçalho
    */

    // Movemos o cursor para o início do arquivo
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
    header_data *data = header_init();

    data->trash_size = first_byte >> 5;
    /*
        Como sabemos que o tamanho do lixo ocupa os 3 primeiros bits do primeiro byte do cabeçalho,
        podemos realizar um shift de 5 bits para a direita para obter somente esses 3 bits

        Exemplo:    10100000 >> 5
                    00000101

        Obtemos o valor 101 = 5 (em decimal), que é o tamanho do lixo
    */

    data->tree_size = (first_byte & 00011111) << 8 | second_byte;
    /*
        Como o tamanho da árvore em pré-ordem ocupa os 5 bits restantes do primeiro byte do cabeçalho
        e todos os 8 bits do segundo byte, precisamos combinar esses bits em um único valor

        Para isso, realizamos um AND bit a bit com o primeiro byte e 00011111,
        a fim de obter somente os 5 bits que possam ter ficado no primeiro byte

        Exemplo:    10100000
                    00011111 &
                    ----------
                    00000000

        Em seguida, realizamos um shift de 8 bits para a esquerda com o valor obtido,
        a fim de obter os 8 bits do segundo byte no lugar correto

        Exemplo:    00000000 << 8
                    00000000

        Por fim, realizamos um OR bit a bit entre o valor obtido e o segundo byte,
        a fim de obter o tamanho da árvore em pré-ordem

        Exemplo:    00000000
                    00001011 |
                    ----------
                    00001011

        Obtemos o valor 1011 = 11 (em decimal), que é o tamanho da árvore de Huffman
    */

    data->preorder_tree = malloc(data->tree_size);
    fread(data->preorder_tree, sizeof(uint8_t), data->tree_size, file);

    // 3. Obtemos o tamanho do arquivo compactado

    // Para isso, movemos o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);

    // E obtemos a posição atual do cursor, que é o tamanho do arquivo em bytes
    data->file_size = ftell(file);

    // 4. Movemos o cursor de leitura para a posição correta (após o cabeçalho e a árvore de Huffman)
    fseek(file, sizeof(uint16_t) + data->tree_size, SEEK_SET);

    return data;
}