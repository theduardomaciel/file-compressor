#include <stdlib.h>

#ifndef COMPRESSION_HT
#define COMPRESSION_HT

void compress(FILE *input, char *output_path);
void decompress(FILE *input, char *output_path);

#endif // COMPRESSION_HT