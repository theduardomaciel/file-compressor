#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Concatena duas strings.
 *
 * Esta função concatena duas strings, retornando uma nova string que contém a concatenação das duas.
 *
 * @param s1 A primeira string.
 * @param s2 A segunda string.
 * @return Um ponteiro para a nova string resultante da concatenação.
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