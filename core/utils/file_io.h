#include <stdio.h>
#include <string.h>

#ifndef FILE_IO_H
#define FILE_IO_H

FILE *open_file(const char *filename, const char *mode);

void close_file(FILE *file);

char *read_file(FILE *file);

char *extract_filename(const char *filename);

void write_string_to_file(FILE *file, char *string);

char *merge_strings(const char *s1, const char *s2);

#endif // FILE_IO_H