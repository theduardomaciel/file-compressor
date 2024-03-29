#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "utils.h"

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct hash_entry
{
    uint8_t original_byte;   // Byte original como chave
    uint8_t compressed_byte; // Byte comprimido como valor
} hash_entry;

typedef struct hash_table
{
    hash_entry entries[MAX_SIZE];
} hash_table;

/**
 * @brief Inicializa uma tabela de hash vazia.
 *
 * @return hash_table* Ponteiro para a tabela de hash inicializada.
 */
hash_table *hash_table_init();

/**
 * @brief Insere um byte comprimido e seu respectivo byte original na tabela de hash.
 *
 * @param table Tabela de hash onde o par de bytes será inserido.
 * @param original_byte Byte original a ser inserido.
 * @param compressed_byte Byte comprimido a ser inserido.
 */
void hash_table_insert(hash_table *table, uint8_t original_byte, uint8_t compressed_byte);

/**
 * @brief Obtém o byte comprimido a partir de um byte original.
 *
 * @param table Tabela de hash onde o byte comprimido será buscado.
 * @param original_byte Byte original a ser buscado.
 * @return uint8_t Byte comprimido correspondente ao byte original.
 */
uint8_t hash_table_get(hash_table *table, uint8_t original_byte);

#endif // HASH_TABLE_H