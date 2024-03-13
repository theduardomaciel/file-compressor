#include <stdio.h>

#ifndef FILE_IO_H
#define FILE_IO_H

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

char *read_file(FILE *file);

char *extract_filename(const char *filename);

void write_string_to_file(FILE *file, char *string);

#endif // FILE_IO_H