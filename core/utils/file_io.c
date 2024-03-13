#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

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

char *read_file(FILE *file)
{
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    return buffer;
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

/* char *extract_string_from_file(FILE *file)
{
    char *string = read_file(file);
    close_file(file);

    return string;
} */

void write_string_to_file(FILE *file, char *string)
{
    fwrite(string, 1, strlen(string), file);
    close_file(file);
}