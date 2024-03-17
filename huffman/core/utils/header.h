#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef HEADER_H
#define HEADER_H

typedef struct header_data
{
    uint16_t trash_size;
    uint16_t tree_size;
    uint64_t file_size;
    uint8_t *tree;
} header_data;

void header_init(FILE *file);

void write_tree_callback(void *data, void *arg);

void header_write(FILE *file, header_data *header);

header_data *header_read(FILE *file);

#endif // HEADER_H