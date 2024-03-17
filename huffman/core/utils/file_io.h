#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FILE_IO_H
#define FILE_IO_H

/**
 * @brief Abre um arquivo no modo especificado.
 *
 * Esta função recebe o nome do arquivo e o modo de abertura como parâmetros e retorna um ponteiro para o arquivo aberto.
 *
 * @param filename O nome do arquivo a ser aberto.
 * @param mode O modo de abertura do arquivo.
 * @return FILE* Um ponteiro para o arquivo aberto, ou NULL em caso de erro.
 */
FILE *open_file(const char *filename, const char *mode);

/**
 * @brief Fecha um arquivo previamente aberto com open_file.
 *
 * @param file O ponteiro para o arquivo a ser fechado.
 */
void close_file(FILE *file);

/**
 * @brief Extrai o nome de um arquivo a partir do caminho completo.
 *
 * @param filename O caminho completo do arquivo.
 * @return char* O nome do arquivo extraído.
 */
char *extract_filename(const char *filename);

/**
 * @brief Extrai a extensão de um arquivo a partir do nome do arquivo.
 *
 * @param filename O nome do arquivo.
 * @return char* A extensão do arquivo extraída.
 */
char *extract_extension(const char *filename);

/**
 * @brief Cria um diretório, e todos os diretórios necessários para que ele exista, caso não exista.
 *
 * @param path O caminho do diretório a ser criado.
 */
void create_directory(const char *path);

#endif // FILE_IO_H