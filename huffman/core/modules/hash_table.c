#include "hash_table.h"

hash_table *hash_table_init()
{
    hash_table *table = malloc(sizeof(hash_table));
    NULL_POINTER_CHECK(table);

    memset(table->entries, 0, sizeof(hash_entry) * MAX_SIZE);
    return table;
}

void hash_table_insert(hash_table *table, uint8_t original_byte, uint8_t compressed_byte)
{
    table->entries[original_byte].original_byte = original_byte;
    table->entries[original_byte].compressed_byte = compressed_byte;
}

uint8_t hash_table_get(hash_table *table, uint8_t original_byte)
{
    return table->entries[original_byte].compressed_byte;
}