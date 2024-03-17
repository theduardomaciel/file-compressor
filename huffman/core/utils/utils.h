#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UTILS_H
#define UTILS_H

#define MAX_SIZE 256
// Para mais informações do porquê podemos usar o número 256, veja o arquivo docs/bytes.md

/**
 * Macro de depuração.
 *
 * Verifica se há um ponteiro NULL e imprime a mensagem de erro, o arquivo de origem e
 * linha via 'stderr' .
 * Se a verificação falhar, o programa será encerrado com o código de erro (-1).
 */
#define NULL_POINTER_CHECK(ptr)                          \
    {                                                    \
        if (NULL == (ptr))                               \
        {                                                \
            fprintf(stderr, "%s:%d PONTEIRO NULO: %s n", \
                    __FILE__, __LINE__, #ptr);           \
            exit(-1);                                    \
        }                                                \
    }

/** Macro de depuração.
 *
 * Imprime uma mensagem de depuração, o arquivo de origem e a linha via 'stderr'.
 */
#define DEBUG(msg) fprintf(stderr, "%s:%d %s", __FILE__, __LINE__, (msg))

/**
 * @brief Concatena duas strings.
 *
 * Esta função concatena duas strings, retornando uma nova string que contém a concatenação das duas.
 *
 * @param s1 A primeira string.
 * @param s2 A segunda string.
 * @return char* Um ponteiro para a nova string resultante da concatenação.
 */
char *concat_strings(const char *s1, const char *s2);

/**
 * @brief Define o valor de um bit em um byte (unsigned char).
 *
 * @param c Um byte (unsigned char) cujo i-ésimo bit será definido.
 * @param i A posição do bit a ser definido. Deve ser um valor entre 0 e 7.
 * @return Retorna um novo byte (unsigned char) em que o i-ésimo bit foi definido (como 1).
 */
unsigned char set_bit(unsigned char c, int i);

/**
 * Verifica se o i-ésimo bit de um caractere está definido.
 *
 * @param c O caractere a ser verificado.
 * @param i A posição do bit a ser verificado.
 * @return Retorna 1 se o bit estiver definido, caso contrário retorna 0.
 */
int is_bit_i_set(unsigned char c, int i);

#endif // UTILS_H