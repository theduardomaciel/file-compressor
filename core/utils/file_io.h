#include <stdio.h>

// #include "header.h"
#include "huffman_tree.h"

#ifndef FILE_IO_H
#define FILE_IO_H

// Operações de leitura de arquivos

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

char *read_file(FILE *file);

char *extract_filename(const char *filename);

char *extract_extension(const char *filename);

// Operações de escrita de arquivos

// void write_header(header *header, FILE *output_file);

void write_file(huffman_node *tree, char *file_data, FILE *output_file);

#endif // FILE_IO_H