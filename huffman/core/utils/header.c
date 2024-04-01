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

    uint8_t second_byte = header & 0b11111111;
    /*
        Exemplo:    10100000 00001011
                    00000000 11111111 &
                    -------------------
                    00000000 00001011

        Obtemos somente os 8 últimos do valor, que é o segundo byte do cabeçalho
        Para mais informações sobre máscaras de bits, leia `docs/masks.md`
    */

    fwrite(&first_byte, sizeof(uint8_t), 1, file);
    fwrite(&second_byte, sizeof(uint8_t), 1, file);

    free(data);
}

/**
 * @brief Lê a extensão do arquivo armazenada no cabeçalho.
 *
 * @param file O arquivo de onde a extensão será lida.
 * @return A extensão do arquivo lida.
 */
char *header_read_extension(FILE *file)
{
    // 1. Lemos o byte que contém o tamanho do nome da extensão do arquivo original
    uint8_t extension_size;
    fread(&extension_size, sizeof(uint8_t), 1, file);

    // 2. Extraímos o tamanho da extensão do arquivo original
    extension_size = extension_size >> 5;
    /*
        Desfazemos o shift de 5 bits para a esquerda que foi feito na compressão por requisito
        para obter o tamanho do nome da extensão do arquivo original

        Exemplo:    01100000 >> 5
                    00000011
    */

    // 3. Escrevemos os bytes que contêm a extensão do arquivo original
    char *extension = malloc(extension_size + 1); // +1 para o terminador de string/caractere nulo (\0)
    fread(extension, sizeof(char), extension_size, file);
    extension[extension_size] = '\0';

    return extension;
}

header_data *header_read(FILE *file)
{
    // 1. Inicializamos a struct que armazenará os dados do cabeçalho
    header_data *data = header_init();

    // 2. Lemos os 2 primeiros bytes do arquivo
    uint8_t first_byte;
    uint8_t second_byte;

    fread(&first_byte, sizeof(uint8_t), 1, file);
    fread(&second_byte, sizeof(uint8_t), 1, file);

    // 2. Extraímos o tamanho do lixo e o tamanho da árvore de Huffman
    data->trash_size = first_byte >> 5;
    /*
        Como sabemos que o tamanho do lixo ocupa os 3 primeiros bits do primeiro byte do cabeçalho,
        podemos realizar um shift de 5 bits para a direita para obter somente esses 3 bits

        Exemplo:    10100000 >> 5
                    00000101

        Obtemos o valor 101 = 5 (em decimal), que é o tamanho do lixo
    */

    data->tree_size = (first_byte & 0b00011111) << 8 | second_byte;
    /*
        Como o tamanho da árvore em pré-ordem ocupa os 5 bits restantes do primeiro byte do cabeçalho
        e todos os 8 bits do segundo byte, precisamos combinar esses bits em um único valor

        Exemplo:    Byte 1: 10100010 (tamanho do lixo = 101 = 5)
                    Byte 2: 00001011 (tamanho da árvore em pré-ordem = 1000001011 = 523)

        Para isso, realizamos um AND bit a bit com o primeiro byte e 00011111,
        a fim de obter somente os 5 bits que possam ter ficado no primeiro byte

        Exemplo:    10100010
                    00011111 &
                    ----------
                    00000010

        Em seguida, realizamos um shift de 8 bits para a esquerda com o valor obtido,
        a fim de obter os 8 bits do segundo byte no lugar correto

        Exemplo:    00000000 00000010 << 8  (como tree_size é um uint16_t, o shift bit não é truncado)

                    00000000 00000010
                    00000000 00000100 (1)
                    00000000 00001000 (2)
                    00000000 00010000 (3)
                    00000000 00100000 (4)
                    00000000 01000000 (5)
                    00000000 10000000 (6)
                    00000001 00000000 (7)
                    00000010 00000000 (8)

                    00000010 00000000

        Por fim, realizamos um OR bit a bit entre o valor obtido e o segundo byte,
        a fim de obter o tamanho da árvore em pré-ordem

        Exemplo:    00000010 00000000
                             00001011 |
                    -------------------
                    00000010 00001011

        Obtemos o valor 1000001011 = 523 (em decimal), que é o tamanho da árvore em pré-ordem
    */

    // 3. Extraímos a árvore de Huffman em pré-ordem
    data->preorder_tree = malloc(data->tree_size);
    fread(data->preorder_tree, sizeof(uint8_t), data->tree_size, file);
    /*
        Como já lemos os 2 bytes iniciais do arquivo, o cursor de leitura
        já está na posição correta para ler a árvore de Huffman em pré-ordem
    */

    // 3. Extraímos a extensão do arquivo
    data->extension = header_read_extension(file);

    // 4. Obtemos o tamanho do header
    size_t header_size = sizeof(uint16_t) + data->tree_size + sizeof(uint8_t) + sizeof(char) * strlen(data->extension);
    /*
        O tamanho do cabeçalho corresponde à:
            - 2 bytes = 16 bits (tamanho do lixo e tamanho da árvore em pré-ordem)
            - tree_size bytes (árvore de Huffman em pré-ordem)
            - 1 byte = 8 bits (tamanho do nome da extensão do arquivo original)
            - strlen(extension) bytes (extensão do arquivo original)
    */

    // 5. Obtemos o tamanho ocupado pelos bytes compactados

    // 5.1 Para isso, movemos o cursor para o final do arquivo
    fseek(file, 0, SEEK_END);

    // 5.2 E obtemos a posição atual do cursor, que é o tamanho do arquivo em bytes
    data->file_size = ftell(file) - header_size;

    // 6. Movemos o cursor de leitura para a posição correta (após o cabeçalho)
    fseek(file, header_size, SEEK_SET);
    /*
        Avançamos o cursor de leitura para a posição após o cabeçalho, a fim de que possamos ler os dados compactados
        Fazemos isso para que a leitura dos dados compactados seja feita corretamente posteriormente.
    */

    return data;
}