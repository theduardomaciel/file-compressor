#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "compression.h"

#include "utils.h"
#include "file_io.h"

#include "frequency_table.h"
#include "priority_queue.h"
#include "huffman_tree.h"

void compress(FILE *input, char *output_path)
{
    // Construímos a tabela de frequências com base no arquivo de entrada
    uint64_t *frequency_table = build_frequency_table(input);

    // Construímos a fila de prioridade com base na tabela de frequências
    priority_queue *pq = build_priority_queue(frequency_table);

    // Construímos a árvore de Huffman com base na fila de prioridade
    huffman_node *tree = build_huffman_tree(pq);

    print_pre_order(tree);
    print_tree_visually(tree, 0, '-');

    /*
        FILE *output_file = open_file(output_path, "wb");
        // Somente criamos o arquivo de saída agora, para não gastar recursos caso nos deparemos com algum erro durante a compressão

        // Realizamos a escrita do arquivo

        close_file(output_file);
    */
}