#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FILE_IO_H
#define FILE_IO_H

/**
 * Abre um arquivo no modo especificado.
 *
 * Esta função recebe o nome do arquivo e o modo de abertura como parâmetros e retorna um ponteiro para o arquivo aberto.
 *
 * @param filename O nome do arquivo a ser aberto.
 * @param mode O modo de abertura do arquivo.
 * @return Um ponteiro para o arquivo aberto, ou NULL em caso de erro.
 */
FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

char *read_file(FILE *file);

char *extract_filename(const char *filename);

char *extract_extension(const char *filename);

void create_directory(const char *path);

#endif // FILE_IO_H