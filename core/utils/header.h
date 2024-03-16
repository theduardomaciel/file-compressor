#include <stdio.h>
#include <stdint.h>

#ifndef HEADER_H
#define HEADER_H

typedef struct header_data
{
    uint16_t trash_size;
    uint16_t tree_size;
} header_data;

void header_init(FILE *file);

void write_tree_callback(void *data, void *arg);

void header_write(FILE *file, header_data *header);

#endif // HEADER_H