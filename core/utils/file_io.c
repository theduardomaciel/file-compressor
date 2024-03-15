#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "file_io.h"

#define MAX_FILE_SIZE 100000000 // 100MB

// Operações de leitura de arquivos

FILE *open_file(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    return file;
}

void close_file(FILE *file)
{
    fclose(file);
}

char *extract_filename(const char *filename)
{
    char *extracted = malloc(strlen(filename) + 1);
    strcpy(extracted, filename);

    char *dot = strrchr(extracted, '.');

    if (dot != NULL)
    {
        *dot = '\0';
    }

    return extracted;
}

// Operações de escrita de arquivos

/* void write_header(header *header, FILE *output_file)
{
    // Seguindo as especificações do projeto (https://drive.google.com/file/d/1dWWsri5L5bp99hNSOl7smnYkdgPd9wSe/view?usp=sharing),
    // o header do arquivo compactado deve seguir a seguinte estrutura:
    // - Os primeiros 3 bits são destinados ao tamanho do lixo
    // - Os próximos 13 bits são destinados ao tamanho da árvore de Huffman
    // - Os próximos N bytes são destinados à árvore de Huffman

    printf("\n4️⃣. Escrevendo header do arquivo compactado...\n");

    printf("Tamanho do lixo: %d\n", header->trash_size);
    printf("Tamanho da árvore: %d\n", header->tree_size);
    printf("Árvore de Huffman: %s\n", header->tree_bytes);

    // Escrevendo o tamanho do lixo e o tamanho da árvore
    unsigned char trash_tree = (header->trash_size << 5) | (header->tree_size >> 8);
    fwrite(&trash_tree, sizeof(unsigned char), 1, output_file);

    unsigned char tree_size = header->tree_size;
    fwrite(&tree_size, sizeof(unsigned char), 1, output_file);

    // Escrevendo a árvore de Huffman
    fwrite(header->tree_bytes, sizeof(unsigned char), header->tree_size, output_file);

    printf("✅ Header do arquivo compactado escrito com sucesso!\n");
} */